#include "NovaClient/Net/PacketBuffer.hpp"
#include <stdexcept>

namespace NovaClient::Net
{
    void PacketBuffer::ensure(size_t n)
    {
        if (readPos + n > m_data.size())
            throw std::runtime_error("PacketBuffer: not enough data");
    }

    void PacketBuffer::write_u8(uint8_t v)
    {
        m_data.push_back(v);
    }

    void PacketBuffer::write_varint(int32_t v)
    {
        uint32_t uv = static_cast<uint32_t>(v);
        do
        {
            uint8_t temp = uv & 0x7F;
            uv >>= 7;
            if (uv != 0)
                temp |= 0x80;
            m_data.push_back(temp);
        } while (uv != 0);
    }

    void PacketBuffer::write_string(const std::string& s)
    {
        write_varint((int32_t)s.size());
        m_data.insert(m_data.end(), s.begin(), s.end());
    }

    uint8_t PacketBuffer::read_u8()
    {
        ensure(1);
        return m_data[readPos++];
    }

    int32_t PacketBuffer::read_varint()
    {
        int32_t numRead = 0;
        int32_t result = 0;
        uint8_t read;

        do
        {
            ensure(1);
            read = m_data[readPos++];

            int32_t value = (read & 0x7F);
            result |= (value << (7 * numRead));

            numRead++;
            if (numRead > 5)
                throw std::runtime_error("VarInt too big");
        } while (read & 0x80);

        return result;
    }

    std::string PacketBuffer::read_string()
    {
        int32_t len = read_varint();
        ensure(len);

        std::string s;
        s.reserve(len);

        for (int i = 0; i < len; i++)
            s.push_back((char)m_data[readPos++]);

        return s;
    }
}
