/* This file is part of COVISE.

You can use it under the terms of the GNU Lesser General Public License
version 2.1 or later, see lgpl - 2.1.txt.

* License: LGPL 2 + */


#ifndef OSCPRIVATEACTION_H
#define OSCPRIVATEACTION_H

#include "oscExport.h"
#include "oscObjectBase.h"
#include "oscObjectVariable.h"

#include "oscVariables.h"
#include "schema/oscLongitudinalAction.h"
#include "schema/oscLateralAction.h"
#include "schema/oscVisibility.h"
#include "schema/oscMeeting.h"
#include "schema/oscAutonomous.h"
#include "schema/oscDriverAction.h"
#include "schema/oscPosition.h"
#include "schema/oscRouting.h"

namespace OpenScenario
{
class OPENSCENARIOEXPORT oscPrivateAction : public oscObjectBase
{
public:
    oscPrivateAction()
    {
        OSC_OBJECT_ADD_MEMBER_OPTIONAL(LongitudinalAction, "oscLongitudinalAction");
        OSC_OBJECT_ADD_MEMBER_OPTIONAL(LateralAction, "oscLateralAction");
        OSC_OBJECT_ADD_MEMBER_OPTIONAL(Visibility, "oscVisibility");
        OSC_OBJECT_ADD_MEMBER_OPTIONAL(Meeting, "oscMeeting");
        OSC_OBJECT_ADD_MEMBER_OPTIONAL(Autonomous, "oscAutonomous");
        OSC_OBJECT_ADD_MEMBER_OPTIONAL(DriverAction, "oscDriverAction");
        OSC_OBJECT_ADD_MEMBER_OPTIONAL(Position, "oscPosition");
        OSC_OBJECT_ADD_MEMBER_OPTIONAL(Routing, "oscRouting");
    };
    oscLongitudinalActionMember LongitudinalAction;
    oscLateralActionMember LateralAction;
    oscVisibilityMember Visibility;
    oscMeetingMember Meeting;
    oscAutonomousMember Autonomous;
    oscDriverActionMember DriverAction;
    oscPositionMember Position;
    oscRoutingMember Routing;

};

typedef oscObjectVariable<oscPrivateAction *> oscPrivateActionMember;


}

#endif //OSCPRIVATEACTION_H