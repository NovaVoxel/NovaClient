#include "NovaClient/Net/Packets/Handshake.hpp"

namespace NovaClient::Net
{
    void HandshakePacket::write(PacketBuffer& buf) const
    {
        buf.write_varint(protocolVersion);
        buf.write_string(serverAddress);
        buf.write_u16(serverPort);
        buf.write_varint(static_cast<std::int32_t>(nextState));
    }

    void HandshakePacket::read(PacketBuffer& buf)
    {
        protocolVersion = buf.read_varint();
        serverAddress   = buf.read_string();
        serverPort      = buf.read_u16();
        nextState       = static_cast<ProtocolState>(buf.read_varint());
    }
}
