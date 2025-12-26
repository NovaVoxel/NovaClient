#include "NovaClient/Client.hpp"
#include "NovaClient/ClientState.hpp"
#include <NovaForge/Engine.hpp>
#include <iostream>

namespace NovaClient
{
    Client::Client() = default;
    Client::~Client() = default;

    void Client::init()
    {
        std::cout << "[Client] Init\n";

        engine = std::make_unique<NovaForge::Engine>();
        engine->init();
        engine->set_window_title("NovaClient");

        running = true;
    }

    void Client::shutdown()
    {
        std::cout << "[Client] Shutdown\n";

        if (state)
        {
            state->on_exit(*this);
            state.reset();
        }

        if (engine)
        {
            engine->shutdown();
            engine.reset();
        }

        running = false;
    }

    void Client::set_state(std::unique_ptr<ClientState> newState)
    {
        if (state)
            state->on_exit(*this);

        state = std::move(newState);

        if (state)
            state->on_enter(*this);
    }

    void Client::run()
    {
        double last = NovaForge::Time::now();

        while (running)
        {
            double now = NovaForge::Time::now();
            double dt = now - last;
            last = now;

            if (state)
                state->tick(*this, dt);

            engine->run(); // Engine tick + render
        }
    }
}
