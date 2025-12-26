#pragma once

namespace NovaClient
{
    class Client;

    class ClientState
    {
    public:
        virtual ~ClientState() = default;

        virtual void on_enter(Client& client) = 0;
        virtual void on_exit(Client& client) = 0;

        virtual void tick(Client& client, double dt) = 0;
    };
}
