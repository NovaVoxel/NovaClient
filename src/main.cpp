#include "NovaClient/Client.hpp"

int main()
{
    NovaClient::Client client;
    client.init();
    client.run();
    client.shutdown();
    return 0;
}
