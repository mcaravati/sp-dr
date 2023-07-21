#include "spdr_client.h"

namespace spdr {
    Client::Client(const std::string host, const int port) {
        this->host = host;
        this->port = port;
    }

    Client::~Client() {
        std::cout << "Client::~Client()" << std::endl;
    }

    void Client::connect() const {
        std::cout << "Client::connect()" << std::endl;
    }

    void Client::disconnect() const {
        std::cout << "Client::disconnect()" << std::endl;
    }
}