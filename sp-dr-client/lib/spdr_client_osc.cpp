#include "spdr_client_osc.hpp"

#define MAX_PACKET_SIZE 1024

namespace spdr {
    OSCClient::OSCClient(const std::string host, const int port): host(host), port(port) {}

    OSCClient::~OSCClient() {
        this->disconnect();
    }

    int OSCClient::connect() {
        std::cerr << "[W] OSC being a UDP-based protocol, the call to Client.connect() is not necessary here" << std::endl;

        this->fd = ::socket(AF_INET, SOCK_DGRAM, 0);
        if (this->fd < 0) {
            std::cerr << "[E] Error creating a socket for to connect to the OSC server" << std::endl;
            return 1;
        }

        std::memset(&(this->osc_server), 0, sizeof(this->osc_server));
        this->osc_server.sin_family = AF_INET;
        this->osc_server.sin_port = ::htons(this->port);
        this->osc_server.sin_addr.s_addr = ::inet_addr(this->host.c_str());

        return 0;
    }

    int OSCClient::disconnect() {
        std::cerr << "[W] OSC being a UDP-based protocol, the call to Client.disconnect() is not necessary here" << std::endl;

        return 0;
    }

    int OSCClient::set_motor(const unsigned int motor_id, const float angle) const {
        char buffer[MAX_PACKET_SIZE] = {0};

        OSCPP::Client::Packet packet(buffer, MAX_PACKET_SIZE);
        packet
            .openBundle(std::time(nullptr))
                .openMessage("/set-motor", 2)
                    .int32((int) motor_id)
                    .float32(angle)
                .closeMessage()
            .closeBundle();

        return this->send_message(buffer, packet.size());
    }

    int OSCClient::toggle_led(const unsigned int motor_id, const bool state) const {
        char buffer[MAX_PACKET_SIZE] = {0};

        OSCPP::Client::Packet packet(buffer, MAX_PACKET_SIZE);
        packet
            .openBundle(std::time(nullptr))
                .openMessage("/set-led", 2)
                    .int32((int) motor_id)
                    .int32((int) state)
                .closeMessage()
            .closeBundle();

        return this->send_message(buffer, packet.size());        
    }

    int OSCClient::toggle_torque(const unsigned int motor_id, const bool state) const {
        char buffer[MAX_PACKET_SIZE] = {0};

        OSCPP::Client::Packet packet(buffer, MAX_PACKET_SIZE);
        packet
            .openBundle(std::time(nullptr))
                .openMessage("/set-torque", 2)
                    .int32((int) motor_id)
                    .int32((int) state)
                .closeMessage()
            .closeBundle();

        return this->send_message(buffer, packet.size());
    }

    int OSCClient::set_speed(const unsigned int motor_id, const float speed) const {
        char buffer[MAX_PACKET_SIZE] = {0};

        OSCPP::Client::Packet packet(buffer, MAX_PACKET_SIZE);
        packet
            .openBundle(std::time(nullptr))
                .openMessage("/set-speed", 2)
                    .int32((int) motor_id)
                    .float32(speed)
                .closeMessage()
            .closeBundle();

        return this->send_message(buffer, packet.size());
    }

    int OSCClient::inverse_kinematics(const float x, const float y, const float z) const {
        char buffer[MAX_PACKET_SIZE] = {0};

        OSCPP::Client::Packet packet(buffer, MAX_PACKET_SIZE);
        packet
            .openBundle(std::time(nullptr))
                .openMessage("/inverse-kinematics", 3)
                    .float32(x)
                    .float32(y)
                    .float32(z)
                .closeMessage()
            .closeBundle();

        return this->send_message(buffer, packet.size());
    }

    int OSCClient::send_message(const void *buffer, const size_t len) const {
        if (::connect(this->fd, (struct sockaddr *)&(this->osc_server), sizeof(this->osc_server)) < 0)
        {
            std::cerr << "[E] Error connecting to OSC server" << std::endl;
            return 1;
        }

        if (::send(this->fd, buffer, len, 0) < 0)
        {
            std::cerr << "[E] Error sending message to OSC server" << std::endl;
            return 1;
        }

        return 0;
    }
}