#pragma once
#include "NovaClient/Net/Packet.hpp"
#include <string>

namespace NovaClient::Net
{
    class LoginStartPacket : public Packet
    {
    public:
        std::string username;

        static constexpr std::int32_t PACKET_ID = 0x00;

        std::int32_t id() const override { return PACKET_ID; }

        void write(PacketBuffer& buf) const override;
        void read(PacketBuffer& buf) override;
    };
}
