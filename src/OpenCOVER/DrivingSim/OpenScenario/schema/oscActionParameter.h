/* This file is part of COVISE.

You can use it under the terms of the GNU Lesser General Public License
version 2.1 or later, see lgpl - 2.1.txt.

* License: LGPL 2 + */


#ifndef OSCACTIONPARAMETER_H
#define OSCACTIONPARAMETER_H

#include "oscExport.h"
#include "oscObjectBase.h"
#include "oscObjectVariable.h"

#include "oscVariables.h"
#include "schema/oscSet.h"
#include "schema/oscModify.h"

namespace OpenScenario
{
class OPENSCENARIOEXPORT oscActionParameter : public oscObjectBase
{
public:
    oscActionParameter()
    {
        OSC_ADD_MEMBER(name);
        OSC_OBJECT_ADD_MEMBER_OPTIONAL(Set, "oscSet");
        OSC_OBJECT_ADD_MEMBER_OPTIONAL(Modify, "oscModify");
    };
    oscString name;
    oscSetMember Set;
    oscModifyMember Modify;

};

typedef oscObjectVariable<oscActionParameter *> oscActionParameterMember;


}

#endif //OSCACTIONPARAMETER_H