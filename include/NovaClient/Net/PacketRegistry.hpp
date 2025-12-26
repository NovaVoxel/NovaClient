#pragma once
#include <unordered_map>
#include <functional>
#include <memory>
#include "NovaClient/Net/Packet.hpp"

namespace NovaClient::Net
{
    class PacketRegistry
    {
    public:
        using Factory = std::function<std::unique_ptr<Packet>()>;

        void register_packet(std::int32_t id, Factory f);
        std::unique_ptr<Packet> create(std::int32_t id) const;

    private:
        std::unordered_map<std::int32_t, Factory> m_factories;
    };

    PacketRegistry& registry_handshake_serverbound();
    PacketRegistry& registry_login_serverbound();
}
