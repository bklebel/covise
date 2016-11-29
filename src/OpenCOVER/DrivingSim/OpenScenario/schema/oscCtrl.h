/* This file is part of COVISE.

You can use it under the terms of the GNU Lesser General Public License
version 2.1 or later, see lgpl - 2.1.txt.

* License: LGPL 2 + */


#ifndef OSCCTRL_H
#define OSCCTRL_H

#include "oscExport.h"
#include "oscObjectBase.h"
#include "oscObjectVariable.h"

#include "oscVariables.h"
#include "schema/oscCatalogReference.h"

namespace OpenScenario
{
class OPENSCENARIOEXPORT oscCtrl : public oscObjectBase
{
public:
    oscCtrl()
    {
        OSC_OBJECT_ADD_MEMBER_OPTIONAL(CatalogReference, "oscCatalogReference");
    };
    oscCatalogReferenceMember CatalogReference;

};

typedef oscObjectVariable<oscCtrl *> oscCtrlMember;


}

#endif //OSCCTRL_H