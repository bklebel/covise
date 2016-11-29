/* This file is part of COVISE.

You can use it under the terms of the GNU Lesser General Public License
version 2.1 or later, see lgpl - 2.1.txt.

* License: LGPL 2 + */


#ifndef OSCACTION_H
#define OSCACTION_H

#include "oscExport.h"
#include "oscObjectBase.h"
#include "oscObjectVariable.h"

#include "oscVariables.h"
#include "schema/oscGlobalAction.h"
#include "schema/oscUserDefinedAction.h"
#include "schema/oscPrivateAction.h"

namespace OpenScenario
{
class OPENSCENARIOEXPORT oscAction : public oscObjectBase
{
public:
    oscAction()
    {
        OSC_ADD_MEMBER(name);
        OSC_OBJECT_ADD_MEMBER_OPTIONAL(Global, "oscGlobalAction");
        OSC_OBJECT_ADD_MEMBER_OPTIONAL(UserDefined, "oscUserDefinedAction");
        OSC_OBJECT_ADD_MEMBER_OPTIONAL(Private, "oscPrivateAction");
    };
    oscString name;
    oscGlobalActionMember Global;
    oscUserDefinedActionMember UserDefined;
    oscPrivateActionMember Private;

};

typedef oscObjectVariable<oscAction *> oscActionMember;


}

#endif //OSCACTION_H