/* This file is part of COVISE.

You can use it under the terms of the GNU Lesser General Public License
version 2.1 or later, see lgpl - 2.1.txt.

* License: LGPL 2 + */


#ifndef OSCFOG_H
#define OSCFOG_H

#include "oscExport.h"
#include "oscObjectBase.h"
#include "oscObjectVariable.h"

#include "oscVariables.h"
#include "schema/oscBoundingBox.h"

namespace OpenScenario
{
class OPENSCENARIOEXPORT oscFog : public oscObjectBase
{
public:
    oscFog()
    {
        OSC_ADD_MEMBER(visualRange);
        OSC_OBJECT_ADD_MEMBER_OPTIONAL(BoundingBox, "oscBoundingBox");
    };
    oscDouble visualRange;
    oscBoundingBoxMember BoundingBox;

};

typedef oscObjectVariable<oscFog *> oscFogMember;


}

#endif //OSCFOG_H