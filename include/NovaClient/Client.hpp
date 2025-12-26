#pragma once
#include <memory>
#include <string>

namespace NovaForge { class Engine; }

namespace NovaClient
{
    class ClientState;

    class Client
    {
    public:
        Client();
        ~Client();

        void init();
        void run();
        void shutdown();

        void set_state(std::unique_ptr<ClientState> newState);

    private:
        std::unique_ptr<NovaForge::Engine> engine;
        std::unique_ptr<ClientState> state;

        bool running = false;
    };
}
