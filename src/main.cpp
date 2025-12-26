#include <iostream>

#include "NovaClient/Net/PacketBuffer.hpp"
#include "NovaClient/Net/Packets/Handshake.hpp"
#include "NovaClient/Net/Packets/LoginStart.hpp"

using namespace NovaClient::Net;

int main()
{
    try
    {
        std::cout << "=== NovaClient 1.8.9 Packet Test ===\n";

        // Test 1: Encode + decode HandshakePacket
        {
            HandshakePacket out;
            out.protocolVersion = Protocol::Version_1_8_9;
            out.serverAddress   = "example.com";
            out.serverPort      = 25565;
            out.nextState       = ProtocolState::Login;

            PacketBuffer buf;
            out.write(buf);

            // Copy buffer so reading starts from index 0
            PacketBuffer bufRead = buf;

            HandshakePacket in;
            in.read(bufRead);

            std::cout << "[Handshake]\n";
            std::cout << " protocolVersion = " << in.protocolVersion << "\n";
            std::cout << " serverAddress   = " << in.serverAddress << "\n";
            std::cout << " serverPort      = " << in.serverPort << "\n";
            std::cout << " nextState       = " << static_cast<int>(in.nextState) << "\n";
        }

        // Test 2: Encode + decode LoginStartPacket
        {
            LoginStartPacket out;
            out.username = "TestPlayer";

            PacketBuffer buf;
            out.write(buf);

            PacketBuffer bufRead = buf;

            LoginStartPacket in;
            in.read(bufRead);

            std::cout << "[LoginStart]\n";
            std::cout << " username = " << in.username << "\n";
        }

        std::cout << "=== Done ===\n";
    }
    catch (const std::exception& ex)
    {
        std::cerr << "[Error] " << ex.what() << "\n";
        return 1;
    }

    return 0;
}
