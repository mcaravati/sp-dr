#include "spdr_client.h"

namespace spdr {
    Client::Client(const std::string host, const int port) {
        this->host = host;
        this->port = port;
    }

    Client::~Client() {
        std::cout << "Client::~Client()" << std::endl;
    }

    int Client::connect() const {
        std::cout << "Client::connect()" << std::endl;
        return 0;
    }

    int Client::disconnect() const {
        std::cout << "Client::disconnect()" << std::endl;
        return 0;
    }
}
