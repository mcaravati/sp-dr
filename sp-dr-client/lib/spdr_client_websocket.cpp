#include "spdr_client_websocket.hpp"

#include <emscripten/emscripten.h>
#include <cstdio> // std::snprintf, std::sprintf
#include <memory> // std::unique_ptr
#include <sstream>
#include <iomanip>

#define BUFFER_SIZE 1024

std::string serialize_float(const float value) {
    std::ostringstream stream;
    stream << std::fixed << std::setprecision(2) << value;
    std::string serialized(stream.str());

    return serialized;
}

EM_BOOL onopen(int eventType, const EmscriptenWebSocketOpenEvent *websocketEvent, void *userData) {
    std::cout << "onOpen() handler called" << std::endl;

    return EM_TRUE;
}

EM_BOOL onerror(int eventType, const EmscriptenWebSocketErrorEvent *websocketEvent, void *userData) {
    std::cout << "onError() handler called" << std::endl;

    return EM_TRUE;
}

EM_BOOL onclose(int eventType, const EmscriptenWebSocketCloseEvent *websocketEvent, void *userData) {
    std::cout << "onClose() handler called" << std::endl;

    return EM_TRUE;
}

EM_BOOL onmessage(int eventType, const EmscriptenWebSocketMessageEvent *websocketEvent, void *userData) {
    std::cout << "onMessage() handler called" << std::endl;

    return EM_TRUE;
}

namespace spdr {
    WebsocketClient::WebsocketClient(const std::string host, const int port): host(host), port(port), open(false) {

    }

    WebsocketClient::~WebsocketClient() {
        this->disconnect();
    }

    int WebsocketClient::connect() {
        std::string address("ws://" + this->host + ":" + std::to_string(this->port));

        EmscriptenWebSocketCreateAttributes attributes = {
            address.c_str(),
            NULL,
            EM_TRUE
        };

        this->websocket = emscripten_websocket_new(&attributes);
        this->open = true;

        emscripten_websocket_set_onopen_callback(this->websocket, NULL, onopen);
        emscripten_websocket_set_onerror_callback(this->websocket, NULL, onerror);
        emscripten_websocket_set_onclose_callback(this->websocket, NULL, onclose);
        emscripten_websocket_set_onmessage_callback(this->websocket, NULL, onmessage);

        return 0;
    }

    int WebsocketClient::disconnect() {
        if (!this->open) {
            return 1;
        }

        emscripten_websocket_close(this->websocket, 0, "Connection closed");
        emscripten_websocket_delete(this->websocket);

        this->open = false;

        return 0;
    }

    int WebsocketClient::set_motor(const unsigned int motor_id, const float angle) const {
        std::string payload("{\"type\":\"set-motor\",\"data\":[" + std::to_string(motor_id) + "," + serialize_float(angle) + "]}");

        EMSCRIPTEN_RESULT result = emscripten_websocket_send_utf8_text(this->websocket, payload.c_str());
        if (result) {
            std::cerr << "Error while setting motor: " << result << std::endl;
            return 1;
        }
        
        return 0;
    }

    int WebsocketClient::toggle_led(const unsigned int motor_id, const bool state) const {
        std::string payload("{\"type\":\"set-led\",\"data\":[" + std::to_string(motor_id) + "," + std::to_string(state) + "]}");

        EMSCRIPTEN_RESULT result = emscripten_websocket_send_utf8_text(this->websocket, payload.c_str());
        if (result) {
            std::cerr << "Error while toggling led: " << result << std::endl;
            return 1;
        }
        
        return 0;
    }

    int WebsocketClient::toggle_torque(const unsigned int motor_id, const bool state) const {
        std::string payload("{\"type\":\"set-torque\",\"data\":[" + std::to_string(motor_id) + "," + std::to_string(state) + "]}");

        EMSCRIPTEN_RESULT result = emscripten_websocket_send_utf8_text(this->websocket, payload.c_str());
        if (result) {
            std::cerr << "Error while toggling torque: " << result << std::endl;
            return 1;
        }
        
        return 0;
    }

    int WebsocketClient::set_speed(const unsigned int motor_id, const float speed) const {
        std::string payload("{\"type\":\"set-speed\",\"data\":[" + std::to_string(motor_id) + "," + serialize_float(speed) + "]}");

        EMSCRIPTEN_RESULT result = emscripten_websocket_send_utf8_text(this->websocket, payload.c_str());
        if (result) {
            std::cerr << "Error while setting motor speed: " << result << std::endl;
            return 1;
        }
        
        return 0;
    }

    int WebsocketClient::inverse_kinematics(const float x, const float y, const float z) const {
        std::string payload("{\"type\":\"inverse-kinematics\",\"data\":[" + serialize_float(x) + "," + serialize_float(y) + "," + serialize_float(z) + "]}");

        EMSCRIPTEN_RESULT result = emscripten_websocket_send_utf8_text(this->websocket, payload.c_str());
        if (result) {
            std::cerr << "Error while sending inverse kinematics coordinates: " << result << std::endl;
            return 1;
        }
        
        return 0;
    }
}