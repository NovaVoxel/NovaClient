#pragma once
#include <cstdint>
#include "PacketBuffer.hpp"

namespace NovaClient::Net
{
    class Packet
    {
    public:
        virtual ~Packet() = default;

        virtual int32_t id() const = 0;
        virtual void write(PacketBuffer& buf) const = 0;
        virtual void read(PacketBuffer& buf) = 0;
    };
}
