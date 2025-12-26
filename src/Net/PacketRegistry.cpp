#include "NovaClient/Net/PacketRegistry.hpp"
#include <stdexcept>

namespace NovaClient::Net
{
    void PacketRegistry::register_packet(int32_t id, Factory f)
    {
        map[id] = std::move(f);
    }

    std::unique_ptr<Packet> PacketRegistry::create(int32_t id) const
    {
        auto it = map.find(id);
        if (it == map.end())
            throw std::runtime_error("Unknown packet id");
        return it->second();
    }
}
