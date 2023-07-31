#ifndef __SPDR_CLIENT_H__
#define __SPDR_CLIENT_H__

#include <string>
#include <iostream>

namespace spdr {
    class Client {
    public:
        virtual ~Client() {};
        virtual int connect() = 0;
        virtual int disconnect() = 0;
        virtual int set_motor(const unsigned int motor_id, const float angle) const = 0;
        virtual int toggle_led(const unsigned int motor_id, const bool state) const = 0;
        virtual int toggle_torque(const unsigned int motor_id, const bool state) const = 0;
        virtual int set_speed(const unsigned int motor_id, const float speed) const = 0;
        virtual int inverse_kinematics(const float x, const float y, const float z) const = 0;
    };
}

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
