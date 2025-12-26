#pragma once
#include <unordered_map>
#include <functional>
#include <memory>
#include "Packet.hpp"

namespace NovaClient::Net
{
    class PacketRegistry
    {
    public:
        using Factory = std::function<std::unique_ptr<Packet>()>;

        void register_packet(int32_t id, Factory f);
        std::unique_ptr<Packet> create(int32_t id) const;

    private:
        std::unordered_map<int32_t, Factory> map;
    };
}
