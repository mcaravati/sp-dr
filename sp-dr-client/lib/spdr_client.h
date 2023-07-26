#ifndef __SPDR_CLIENT_H__
#define __SPDR_CLIENT_H__

#include <string>
#include <iostream>

namespace spdr {
    class Client {
    public:
        explicit Client(const std::string host, const int port);
        ~Client();
        int connect() const;
        int disconnect() const;
    private:
        std::string host;
        int port;
    };
}

#ifdef USE_EMSCRIPTEN // Javascript / WASM bindings
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

#ifdef USE_PYTHON // Python bindings using Boost::Python
#include <boost/python.hpp>

BOOST_PYTHON_MODULE(libspdr)
{
    using namespace boost::python;
    class_<spdr::Client>("Client", init<std::string, int>())
        .def("connect", &spdr::Client::connect)
        .def("disconnect", &spdr::Client::disconnect)
        ;
}

#endif // USE_PYTHON

#endif // __SPDR_CLIENT_H__
