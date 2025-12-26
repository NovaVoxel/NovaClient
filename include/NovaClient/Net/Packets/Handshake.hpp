#pragma once
#include "NovaClient/Net/Packet.hpp"
#include "NovaClient/Net/Protocol.hpp"
#include <string>

namespace NovaClient::Net
{
    class HandshakePacket : public Packet
    {
    public:
        std::int32_t protocolVersion = Protocol::Version_1_8_9;
        std::string serverAddress;
        std::uint16_t serverPort = 25565;
        ProtocolState nextState = ProtocolState::Login;

        static constexpr std::int32_t PACKET_ID = 0x00;

        std::int32_t id() const override { return PACKET_ID; }

        void write(PacketBuffer& buf) const override;
        void read(PacketBuffer& buf) override;
    };
}
