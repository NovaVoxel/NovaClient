#pragma once
#include <string>
#include <cstdint>

namespace NovaClient::Net
{
    class Socket
    {
    public:
        Socket();
        ~Socket();

        bool connect(const std::string& host, std::uint16_t port);
        void close();

        bool send_all(const std::uint8_t* data, std::size_t size);
        bool recv_all(std::uint8_t* data, std::size_t size);

        bool is_open() const { return sockfd != invalid_socket; }

    private:
        using socket_t =
        #ifdef _WIN32
            unsigned long long;
        #else
            int;
        #endif

        static constexpr socket_t invalid_socket =
        #ifdef _WIN32
            static_cast<socket_t>(~0ULL);
        #else
            -1;
        #endif

        socket_t sockfd = invalid_socket;

        static bool init_platform();
        static void cleanup_platform();
    };
}
