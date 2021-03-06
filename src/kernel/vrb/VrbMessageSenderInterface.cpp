/* This file is part of COVISE.

   You can use it under the terms of the GNU Lesser General Public License
   version 2.1 or later, see lgpl-2.1.txt.

 * License: LGPL 2+ */

#include "VrbMessageSenderInterface.h"
#include <net/message.h>
#include <net/udpMessage.h>

bool vrb::VrbMessageSenderInterface::send(const covise::MessageBase *msg)
{
  if (const covise::Message *tcp = dynamic_cast<const covise::Message *>(msg))
  {
    return sendMessage(tcp);
  }
  if (const UdpMessage *udp = dynamic_cast<const UdpMessage *>(msg))
  {
    return sendMessage(udp);
  }
  return false;
}

bool vrb::VrbMessageSenderInterface::send(covise::TokenBuffer &tb, int type, Protocol p)
{
  switch (p)
  {
  case Protocol::TCP:
  {
    covise::Message msg{tb};
    msg.type = type;
    return sendMessage(&msg);
  }
  case Protocol::UDP:
  {
    vrb::UdpMessage msg{tb};
    msg.type = static_cast<vrb::udp_msg_type>(type);
    return sendMessage(&msg);
  }
  default:
    return false;
  }
}
