#pragma once
#include <cstdint>

namespace NovaClient::Net
{
    enum class ProtocolState : std::int32_t
    {
        Handshake = 0,
        Status    = 1,
        Login     = 2,
        Play      = 3
    };

    namespace Protocol
    {
        constexpr std::int32_t Version_1_8_9 = 47;
    }
}
