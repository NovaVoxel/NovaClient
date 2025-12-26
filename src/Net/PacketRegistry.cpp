#include "NovaClient/Net/PacketRegistry.hpp"
#include "NovaClient/Net/Packets/Handshake.hpp"
#include "NovaClient/Net/Packets/LoginStart.hpp"
#include <stdexcept>

namespace NovaClient::Net
{
    void PacketRegistry::register_packet(std::int32_t id, Factory f)
    {
        m_factories[id] = std::move(f);
    }

    std::unique_ptr<Packet> PacketRegistry::create(std::int32_t id) const
    {
        auto it = m_factories.find(id);
        if (it == m_factories.end())
            throw std::runtime_error("Unknown packet id");
        return it->second();
    }

    PacketRegistry& registry_handshake_serverbound()
    {
        static PacketRegistry reg;
        static bool initialized = false;

        if (!initialized)
        {
            initialized = true;
            reg.register_packet(
                HandshakePacket::PACKET_ID,
                []() { return std::make_unique<HandshakePacket>(); }
            );
        }

        return reg;
    }

    PacketRegistry& registry_login_serverbound()
    {
        static PacketRegistry reg;
        static bool initialized = false;

        if (!initialized)
        {
            initialized = true;
            reg.register_packet(
                LoginStartPacket::PACKET_ID,
                []() { return std::make_unique<LoginStartPacket>(); }
            );
        }

        return reg;
    }
}
