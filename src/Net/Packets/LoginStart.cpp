#include "NovaClient/Net/Packets/LoginStart.hpp"

namespace NovaClient::Net
{
    void LoginStartPacket::write(PacketBuffer& buf) const
    {
        buf.write_string(username);
    }

    void LoginStartPacket::read(PacketBuffer& buf)
    {
        username = buf.read_string();
    }
}
