#include "spdr_client_websocket.hpp"

#include <emscripten/emscripten.h>
#include <cstdio> // std::snprintf, std::sprintf
#include <memory> // std::unique_ptr
#include <format>

#define BUFFER_SIZE 1024

std::unique_ptr<std::string> serialize_float(const float value) {
    std::unique_ptr<std::string> serialized(std::format("{:.2f}", value))

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
        char host_buffer[BUFFER_SIZE] = {0};
        char buffer[BUFFER_SIZE] = {0};
        std::copy(this->host.begin(), this->host.end(), host_buffer);
        sprintf(buffer, "ws://%s:%d", host_buffer, this->port);

        EmscriptenWebSocketCreateAttributes attributes = {
            buffer,
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
        char buffer[BUFFER_SIZE] = {0};
        std::sprintf(buffer, "{\"type\":\"set-motor\",\"data\":[%d,%s]}", motor_id, serialize_float(angle).get());

        EMSCRIPTEN_RESULT result = emscripten_websocket_send_utf8_text(this->websocket, buffer);
        if (result) {
            std::cerr << "Error while setting motor: " << result << std::endl;
            return 1;
        }
        
        return 0;
    }

    int WebsocketClient::toggle_led(const unsigned int motor_id, const bool state) const {
        char buffer[BUFFER_SIZE] = {0};
        std::sprintf(buffer, "{\"type\":\"set-led\",\"data\":[%d,%d]}", motor_id, int(state));

        EMSCRIPTEN_RESULT result = emscripten_websocket_send_utf8_text(this->websocket, buffer);
        if (result) {
            std::cerr << "Error while toggling led: " << result << std::endl;
            return 1;
        }
        
        return 0;
    }

    int WebsocketClient::toggle_torque(const unsigned int motor_id, const bool state) const {
        char buffer[BUFFER_SIZE] = {0};
        std::sprintf(buffer, "{\"type\":\"set-torque\",\"data\":[%d,%d]}", motor_id, int(state));

        EMSCRIPTEN_RESULT result = emscripten_websocket_send_utf8_text(this->websocket, buffer);
        if (result) {
            std::cerr << "Error while toggling torque: " << result << std::endl;
            return 1;
        }
        
        return 0;
    }

    int WebsocketClient::set_speed(const unsigned int motor_id, const float speed) const {
        char buffer[BUFFER_SIZE] = {0};
        std::sprintf(buffer, "{\"type\":\"set-speed\",\"data\":[%d,%s]}", motor_id, serialize_float(speed).get());

        EMSCRIPTEN_RESULT result = emscripten_websocket_send_utf8_text(this->websocket, buffer);
        if (result) {
            std::cerr << "Error while setting motor speed: " << result << std::endl;
            return 1;
        }
        
        return 0;
    }

    int WebsocketClient::inverse_kinematics(const float x, const float y, const float z) const {
        char buffer[BUFFER_SIZE] = {0};
        std::sprintf(buffer, "{\"type\":\"inverse-kinematics\",\"data\":[%s,%s,%s]}", serialize_float(x).get(), serialize_float(y).get(), serialize_float(z).get());

        EMSCRIPTEN_RESULT result = emscripten_websocket_send_utf8_text(this->websocket, buffer);
        if (result) {
            std::cerr << "Error while sending inverse kinematics coordinates: " << result << std::endl;
            return 1;
        }
        
        return 0;
    }
}