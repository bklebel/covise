/* This file is part of COVISE.

   You can use it under the terms of the GNU Lesser General Public License
   version 2.1 or later, see lgpl-2.1.txt.

 * License: LGPL 2+ */
#include "VrbServerRegistry.h"

#include <util/unixcompat.h>
#include <net/dataHandle.h>
#include <net/tokenbuffer.h>
#include <net/tokenbuffer_serializer.h>

#include <VrbClientList.h>

#include <iostream>

#include <assert.h>


using namespace covise;
namespace vrb
{
VrbServerRegistry::VrbServerRegistry(const SessionID &session)
    :m_session(session)
{
}

const SessionID& VrbServerRegistry::sessionID() const {
    return m_session;
}

/// set a Value or create new Entry
void VrbServerRegistry::setVar(int ID, const std::string &className, const std::string &name, const DataHandle &value, bool s)
{

    auto rc = getClass(className);
    if (!rc)
    {
        rc = dynamic_cast<serverRegClass*>(m_classes.emplace(end(), std::make_shared<serverRegClass>(className, ID))->get());
    }
    rc->setID(ID);
    regVar *rv = rc->getVar(name);
    if (rv)
    {
        rv->setValue(value);
    }
    else
    {
        rv = new serverRegVar(rc, name, value);
        rc->append(rv);
    }
	serverRegVar* srv = dynamic_cast<serverRegVar*>(rv);
    //call observers
    std::set<int> collectiveObservers = dynamic_cast<serverRegClass*>(rc)->getOList();
    collectiveObservers.insert(srv->getOList().begin(), srv->getOList().end());
    sendVariableChange(srv, collectiveObservers);
    updateUI(srv);


}

/// create new Entry
void VrbServerRegistry::create(int ID, const std::string &className, const std::string &name, const DataHandle &value, bool s)
{
    regClass *rc = getClass(className);
    if (rc)
    {
        serverRegVar *rv = dynamic_cast<serverRegVar*>(rc->getVar(name));
        if (rv)
        {
            return;
        }
    }
    setVar(ID, className, name, value, s);
}
/// get a boolean Variable
int VrbServerRegistry::isTrue(int ID, const std::string &className, const std::string &name, int def)
{
    regClass *rc = getClass(className);
    if (rc)
    {
        serverRegVar *rv = dynamic_cast<serverRegVar*>(rc->getVar(name));
        if (rv)
        {
            bool b;
			covise::TokenBuffer tb(rv->value());
            tb >> b;
            return b;
        }
        return def;
    }
    return def;
}

void VrbServerRegistry::deleteEntry(const std::string &className, const std::string &name)
{
    auto cl = findClass(className);
    if (cl != end())
    {
        cl->get()->deleteVar(name);
    }
}

void VrbServerRegistry::deleteEntry()
{
    for (const auto cl : m_classes)
    {
        cl->deleteAllNonStaticVars();
    }
}

void VrbServerRegistry::sendVariableChange(serverRegVar * rv, std::set<int> observers)
{
    for (const auto client : observers)
    {
        rv->update(client);
    }
}

void VrbServerRegistry::updateUI(serverRegVar* rv)
{
}

void VrbServerRegistry::observe(int sender)
{
    for (auto cl : m_classes)
    {
		dynamic_cast<vrb::serverRegClass*>(cl.get())->observeAllVars(sender);
    }
}

void VrbServerRegistry::observeVar(int ID, const std::string &className, const std::string &variableName, const DataHandle &value)
{
    auto classIt = findClass(className);
    //std::map<const std::string, std::shared_ptr< serverRegClass>>::iterator classIt = myClasses.find(className);
    if (classIt == end()) //if class does not exists create it
    {
        classIt = m_classes.emplace(end(), std::make_shared<serverRegClass>(className, ID));
    }
	dynamic_cast<vrb::serverRegClass*>(classIt->get())->observeVar(ID, variableName, value);
}

void VrbServerRegistry::observeClass(int ID, const std::string &className)
{
    auto classIt = findClass(className);
    if (classIt == end()) //if class does not exists create it
    {
        classIt = m_classes.emplace(end(), std::make_shared<serverRegClass>(className, ID));

    }
	dynamic_cast<vrb::serverRegClass*>(classIt->get())->observe(ID);
}
///unobserve a single variable
void VrbServerRegistry::unObserveVar(int ID, const std::string &className, const std::string &variableName)
{
    auto classIt = findClass(className);
    if (classIt != end())
    {
		dynamic_cast<vrb::serverRegClass*>(classIt->get())->unObserveVar(ID, variableName);
        if (classIt->get()->getID() == ID)
        {
            classIt->get()->setID(-1);
        }
    }
}
///unobserve a class and all its variables
void VrbServerRegistry::unObserveClass(int ID, const std::string &className)
{
    auto classIt = findClass(className);
    if (classIt != end())
    {
		dynamic_cast<vrb::serverRegClass*>(classIt->get())->unObserve(ID);
        if (classIt->get()->getID() == ID)
        {
            classIt->get()->setID(-1);
        }
    }
}
///observer "recvID" gets removed from all classes and variables
void VrbServerRegistry::unObserve(int recvID)
{
    for (const auto cl : m_classes)
    {
		dynamic_cast<vrb::serverRegClass*>(cl.get())->unObserve(recvID);
        if (cl.get()->getID() == recvID)
        {
            cl.get()->setID(-1);
        }
    }
}

std::shared_ptr<regClass> VrbServerRegistry::createClass(const std::string &name, int id)
{
    return std::shared_ptr<serverRegClass>(new serverRegClass(name, id));
}
/////////////SERVERREGVAR/////////////////////////////////////////////////
serverRegVar::~serverRegVar()
{
    informDeleteObservers();
}

void serverRegVar::update(int recvID)
{
    covise::TokenBuffer sb;
    sb << m_class->getID();
    sb << m_class->name();
    sb << name();
	sendValueChange(sb);
    clients.sendMessageToClient(recvID, sb, COVISE_MESSAGE_VRB_REGISTRY_ENTRY_CHANGED);
}
void serverRegVar::updateMap(int recvID)
{
	covise::TokenBuffer sb;

	sb << m_class->getID();
	sb << m_class->name();
	sb << name();
	sendValue(sb);
	clients.sendMessageToClient(recvID, sb, COVISE_MESSAGE_VRB_REGISTRY_ENTRY_CHANGED);
}
void serverRegVar::informDeleteObservers()
{
	covise::TokenBuffer sb;
    sb << getClass()->getID();
    sb << getClass()->name();
    sb << name();
	sendValueChange(sb);
    std::set<int> combinedObservers = observers;
	auto c = dynamic_cast<serverRegVar*>(getClass());
	if (c && c->getOList().size() != 0)
	{
		combinedObservers.insert(c->getOList().begin(), c->getOList().end());
	}
    for (const int obs : combinedObservers)
    {
        clients.sendMessageToClient(obs, sb, COVISE_MESSAGE_VRB_REGISTRY_ENTRY_DELETED);
    }
}


/////////////SERVERREGCLASS/////////////////////////////////////////////////
void serverRegClass::observeAllVars(int sender)
{
    if (m_variables.size() == 0)
    {
        observe(sender);
    }
    else
    {
        for (auto var : m_variables)
        {
			auto v = std::dynamic_pointer_cast<serverRegVar>(var.second);
			v->observe(sender);
            v->update(sender);
        }
    }
}

void serverRegClass::observe(int recvID)
{
    observers.insert(recvID);
}

void serverRegClass::observeVar(int recvID, const std::string &variableName, const DataHandle &value)
{
    serverRegVar *rv = dynamic_cast<serverRegVar*>(getVar(variableName)); 
    if (!rv)
    {
        rv = new serverRegVar(this, variableName, value);
        append(rv);
    }
    else
    {
		if (isMap())
		{
			rv->updateMap(recvID);
		}
		else
		{
			rv->update(recvID);
		}
    }
    rv->observe(recvID);
}

void serverRegClass::unObserveVar(int recvID, const std::string &variableName)
{
    serverRegVar *rv = dynamic_cast<serverRegVar*>(getVar(variableName));
    if (rv)
    {
        rv->unObserve(recvID);
    }
}

void serverRegClass::unObserve(int recvID)
{
    observers.erase(recvID);
    for (const auto &var : m_variables)
    {
       std::dynamic_pointer_cast<serverRegVar>(var.second)->unObserve(recvID);
    }
}

std::shared_ptr<regVar> serverRegClass::createVar(const std::string &name, const DataHandle &value)
{
    return std::shared_ptr<serverRegVar>(new serverRegVar(this, name, value));
}
}
