#include "NovaClient/Net/PacketBuffer.hpp"
#include <stdexcept>

namespace NovaClient::Net
{
    void PacketBuffer::ensure(std::size_t n)
    {
        if (m_readPos + n > m_data.size())
            throw std::runtime_error("PacketBuffer: not enough data");
    }

    void PacketBuffer::write_u8(std::uint8_t v)
    {
        m_data.push_back(v);
    }

    void PacketBuffer::write_u16(std::uint16_t v)
    {
        // big endian (network order)
        m_data.push_back(static_cast<std::uint8_t>((v >> 8) & 0xFF));
        m_data.push_back(static_cast<std::uint8_t>(v & 0xFF));
    }

    void PacketBuffer::write_varint(std::int32_t v)
    {
        std::uint32_t uv = static_cast<std::uint32_t>(v);
        do
        {
            std::uint8_t temp = uv & 0x7F;
            uv >>= 7;
            if (uv != 0)
                temp |= 0x80;
            m_data.push_back(temp);
        } while (uv != 0);
    }

    void PacketBuffer::write_string(const std::string& s)
    {
        write_varint(static_cast<std::int32_t>(s.size()));
        m_data.insert(m_data.end(), s.begin(), s.end());
    }

    std::uint8_t PacketBuffer::read_u8()
    {
        ensure(1);
        return m_data[m_readPos++];
    }

    std::uint16_t PacketBuffer::read_u16()
    {
        ensure(2);
        std::uint16_t hi = m_data[m_readPos++];
        std::uint16_t lo = m_data[m_readPos++];
        return static_cast<std::uint16_t>((hi << 8) | lo);
    }

    std::int32_t PacketBuffer::read_varint()
    {
        std::int32_t numRead = 0;
        std::int32_t result = 0;
        std::uint8_t read;

        do
        {
            ensure(1);
            read = m_data[m_readPos++];

            std::int32_t value = (read & 0x7F);
            result |= (value << (7 * numRead));

            numRead++;
            if (numRead > 5)
                throw std::runtime_error("VarInt too big");
        } while (read & 0x80);

        return result;
    }

    std::string PacketBuffer::read_string()
    {
        std::int32_t len = read_varint();
        if (len < 0)
            throw std::runtime_error("Negative string length");

        ensure(static_cast<std::size_t>(len));

        std::string s;
        s.reserve(static_cast<std::size_t>(len));

        for (int i = 0; i < len; ++i)
            s.push_back(static_cast<char>(m_data[m_readPos++]));

        return s;
    }
}
