/* This file is part of COVISE.

   You can use it under the terms of the GNU Lesser General Public License
   version 2.1 or later, see lgpl-2.1.txt.

 * License: LGPL 2+ */

///class to identify Sessions
///SessionsID(0,"",false) is global Session
#ifndef SESSION_H
#define SESSION_H

#include <string>
#include <util/coExport.h>

namespace vrb {
class VRBEXPORT SessionID {

public:
    SessionID() = default;
    SessionID(int owner, bool isPrivate = true);
    SessionID(int owner, const std::string &name, bool isPrivate = true);

    std::string name() const;
    bool isPrivate()const ;
    int owner() const;
    void setOwner(int id) const;
    void setName(const std::string &name);
    void setPrivate(bool isPrivate);
    bool operator ==(const SessionID &other) const;
    bool operator !=(const SessionID &other) const;
    bool operator <(const SessionID &other) const;
    SessionID &operator=(const SessionID &other);
    SessionID &operator=(const int other) = delete;
    std::string toText() const;
private:
	mutable int m_owner = 0;
    std::string m_name;
    bool m_isPrivate = true;
};
template<typename Stream>
Stream& operator<<(Stream& s, const vrb::SessionID& id) {
    s << id.owner();
    s << id.name();
    s << id.isPrivate();
    return s;
}
template<typename Stream>
Stream& operator>>(Stream& s, vrb::SessionID& id) {
    int owner;
    std::string name;
    bool isPrivate;
    s >> owner;
    s >> name;
    s >> isPrivate;
    id.setOwner(owner);
    id.setName(name);
    id.setPrivate(isPrivate);
    return s;
}

}

#endif // !SESSION_H
