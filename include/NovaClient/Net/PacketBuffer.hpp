#pragma once
#include <vector>
#include <cstdint>
#include <string>

namespace NovaClient::Net
{
    class PacketBuffer
    {
    public:
        PacketBuffer() = default;

        const std::vector<std::uint8_t>& data() const { return m_data; }
        std::vector<std::uint8_t>& data() { return m_data; }

        std::size_t size() const { return m_data.size(); }

        // write
        void write_u8(std::uint8_t v);
        void write_u16(std::uint16_t v);        
        void write_varint(std::int32_t v);
        void write_string(const std::string& s);

        // read
        std::uint8_t read_u8();
        std::uint16_t read_u16();
        std::int32_t read_varint();
        std::string read_string();

    private:
        std::vector<std::uint8_t> m_data;
        std::size_t m_readPos = 0;

        void ensure(std::size_t n);
    };
}
