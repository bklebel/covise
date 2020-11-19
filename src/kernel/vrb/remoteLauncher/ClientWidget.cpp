#include "ClientWidget.h"
#include "MessageTypes.h"

#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QTextStream>

#include <iostream>

using namespace vrb::launcher;

ClientWidget::ClientWidget(int clientID, const QString &clientInfo, QWidget *parent)
    : QWidget(parent), m_clientID(clientID)
{
    QString s;
    QTextStream ss(&s);
    ss << "Client " << clientID << "\n"
       << clientInfo;
    auto *layout = new QVBoxLayout(this);
    layout->setDirection(QVBoxLayout::LeftToRight);
    auto *content = new QLabel(s, this);
    layout->addWidget(content, 0, Qt::AlignTop);

    for (int i = 0; i < static_cast<int>(Program::LAST_DUMMY); i++)
    {
        Program p = Program::COVER;
        auto b = new QPushButton(programNames[i], this);
        layout->addWidget(b);
        connect(b, &QPushButton::clicked, this, [this, i]() {
            emit requestProgramLaunch(static_cast<Program>(i), m_clientID);
        });
    }
}

ClientWidgetList::ClientWidgetList(QScrollArea *scrollArea, QWidget *parent)
    : QWidget(parent), m_layout(new QVBoxLayout(this))
{
    m_layout->setDirection(QVBoxLayout::TopToBottom);
    scrollArea->setWidget(this);
}

void ClientWidgetList::addClient(int clientID, const QString &clientInfo)
{
    auto cw = new ClientWidget(clientID, clientInfo, this);
    m_layout->addWidget(cw);
    removeClient(clientID);
    m_clients[clientID] = cw;
    connect(cw, &ClientWidget::requestProgramLaunch, this, [this](Program programID, int clientID) {
        emit requestProgramLaunch(programID, clientID);
    });
}

void ClientWidgetList::removeClient(int clientID)
{
    auto cl = m_clients.find(clientID);
    if (cl != m_clients.end())
    {
        m_layout->removeWidget(cl->second);
        delete cl->second;
        cl->second = nullptr;
        m_clients.erase(cl);
    }
}
