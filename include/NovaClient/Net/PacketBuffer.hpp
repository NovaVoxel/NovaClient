#pragma once
#include <vector>
#include <cstdint>
#include <string>

namespace NovaClient::Net
{
    class PacketBuffer
    {
    public:
        void write_u8(uint8_t v);
        void write_varint(int32_t v);
        void write_string(const std::string& s);

        uint8_t read_u8();
        int32_t read_varint();
        std::string read_string();

        const std::vector<uint8_t>& data() const { return m_data; }

    private:
        std::vector<uint8_t> m_data;
        size_t readPos = 0;

        void ensure(size_t n);
    };
}
