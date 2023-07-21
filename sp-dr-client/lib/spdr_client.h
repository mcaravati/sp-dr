#ifndef __SPDR_CLIENT_H__
#define __SPDR_CLIENT_H__

#include <string>
#include <iostream>

namespace spdr {
    class Client {
    public:
        explicit Client(const std::string host, const int port);
        ~Client();
        void connect() const;
        void disconnect() const;
    private:
        std::string host;
        int port;
    };
}

#ifdef USE_EMSCRIPTEN
#include <emscripten.h>
#include <emscripten/bind.h>

EMSCRIPTEN_BINDINGS(spdr_client) {
    emscripten::class_<spdr::Client>("Client")
        .constructor<std::string, int>()
        .function("connect", &spdr::Client::connect)
        .function("disconnect", &spdr::Client::disconnect)
        ;
}
#endif // USE_EMSCRIPTEN

#endif // __SPDR_CLIENT_H__
