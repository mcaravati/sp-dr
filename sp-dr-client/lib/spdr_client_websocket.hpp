#ifndef __SPDR_CLIENT_WEBSOCKET_HPP__

#include <emscripten.h>
#include <emscripten/bind.h>
#include <emscripten/websocket.h>

#include "spdr_client.h"

namespace spdr {
    class WebsocketClient: public Client {
        public:
            explicit WebsocketClient(const std::string host, const int port);
            ~WebsocketClient();
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
            EMSCRIPTEN_WEBSOCKET_T websocket;
            bool open;
    };
}

EMSCRIPTEN_BINDINGS(spdr_client) {
    emscripten::class_<spdr::WebsocketClient>("Client")
        .constructor<std::string, int>()
        .function("connect", &spdr::WebsocketClient::connect)
        .function("disconnect", &spdr::WebsocketClient::disconnect)
        .function("set_motor", &spdr::WebsocketClient::set_motor)
        .function("toggle_led", &spdr::WebsocketClient::toggle_led)
        .function("toggle_torque", &spdr::WebsocketClient::toggle_torque)
        .function("set_speed", &spdr::WebsocketClient::set_speed)
        .function("inverse_kinematics", &spdr::WebsocketClient::inverse_kinematics)
        ;
}

#endif // __SPDR_CLIENT_WEBSOCKET_HPP__