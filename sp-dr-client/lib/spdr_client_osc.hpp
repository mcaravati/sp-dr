#ifndef __SPDR_CLIENT_OSC_HPP__
#define __SPDR_CLIENT_OSC_HPP__

#include <iostream>
#include <string>

#include <ctime>
#include <cstring>
#include <arpa/inet.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>

#include <boost/python.hpp>
#include <oscpp/client.hpp>

#include "spdr_client.h"

namespace spdr {
    class OSCClient: public Client {
        public:
            explicit OSCClient(const std::string host, const int port);
            ~OSCClient();
            int connect();
            int disconnect();
            int set_motor(const unsigned int motor_id, const float angle) const;
            int toggle_led(const unsigned int motor_id, const bool state) const;
            int toggle_torque(const unsigned int motor_id, const bool state) const;
            int set_speed(const unsigned int motor_id, const float speed) const;
            int inverse_kinematics(const float x, const float y, const float z) const;
        private:
            std::string host;
            int port;
            struct sockaddr_in osc_server;
            int fd;

            int send_message(const void *buffer, const size_t len) const;
    };
}

BOOST_PYTHON_MODULE(libspdr)
{
    using namespace boost::python;
    class_<spdr::OSCClient>("Client", init<std::string, int>())
        .def("connect", &spdr::OSCClient::connect)
        .def("disconnect", &spdr::OSCClient::disconnect)
        .def("set_motor", &spdr::OSCClient::set_motor)
        .def("toggle_led", &spdr::OSCClient::toggle_led)
        .def("toggle_torque", &spdr::OSCClient::toggle_torque)
        .def("set_speed", &spdr::OSCClient::set_speed)
        .def("inverse_kinematics", &spdr::OSCClient::inverse_kinematics)
        ;
}

#endif // __SPDR_CLIENT_OSC_HPP__