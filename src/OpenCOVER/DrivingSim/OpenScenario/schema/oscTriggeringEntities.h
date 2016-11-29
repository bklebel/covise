/* This file is part of COVISE.

You can use it under the terms of the GNU Lesser General Public License
version 2.1 or later, see lgpl - 2.1.txt.

* License: LGPL 2 + */


#ifndef OSCTRIGGERINGENTITIES_H
#define OSCTRIGGERINGENTITIES_H

#include "oscExport.h"
#include "oscObjectBase.h"
#include "oscObjectVariable.h"

#include "oscVariables.h"
#include "schema/oscNamedEntity.h"

namespace OpenScenario
{
class OPENSCENARIOEXPORT Enum_TriggeringEntities_ruleType : public oscEnumType
{
public:
static Enum_TriggeringEntities_ruleType *instance();
    private:
		Enum_TriggeringEntities_ruleType();
	    static Enum_TriggeringEntities_ruleType *inst; 
};
class OPENSCENARIOEXPORT oscTriggeringEntities : public oscObjectBase
{
public:
    oscTriggeringEntities()
    {
        OSC_ADD_MEMBER(rule);
        OSC_OBJECT_ADD_MEMBER_OPTIONAL(NamedEntity, "oscNamedEntity");
    };
    oscEnum rule;
    oscNamedEntityMember NamedEntity;

    enum Enum_TriggeringEntities_rule
    {
any,
all,

    };

};

typedef oscObjectVariable<oscTriggeringEntities *> oscTriggeringEntitiesMember;


}

#endif //OSCTRIGGERINGENTITIES_H