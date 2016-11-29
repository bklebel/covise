/* This file is part of COVISE.

You can use it under the terms of the GNU Lesser General Public License
version 2.1 or later, see lgpl - 2.1.txt.

* License: LGPL 2 + */


#ifndef OSCTARGET_H
#define OSCTARGET_H

#include "oscExport.h"
#include "oscObjectBase.h"
#include "oscObjectVariable.h"

#include "oscVariables.h"
#include "schema/oscRelative.h"
#include "schema/oscAbsolute.h"

namespace OpenScenario
{
class OPENSCENARIOEXPORT oscTarget : public oscObjectBase
{
public:
    oscTarget()
    {
        OSC_OBJECT_ADD_MEMBER_OPTIONAL(Relative, "oscRelative");
        OSC_OBJECT_ADD_MEMBER_OPTIONAL(Absolute, "oscAbsolute");
    };
    oscRelativeMember Relative;
    oscAbsoluteMember Absolute;

};

typedef oscObjectVariable<oscTarget *> oscTargetMember;


}

#endif //OSCTARGET_H