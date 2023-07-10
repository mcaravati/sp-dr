#include <arpa/inet.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>

#include "flext/source/flext.h"
#include "tinyosc/tinyosc.h"

#define PORT 9000
#define BUFFER_SIZE 1024

#if !defined(FLEXT_VERSION) || (FLEXT_VERSION < 400)
#error You need at least flext version 0.4.0
#endif

class ergojunior : public flext_base
{
    FLEXT_HEADER(ergojunior, flext_base)

public:
    // Constructor
    ergojunior() : motor_id(0), motor_angle(0), fd(-1)
    {
        // Add two float inlets
        AddInAnything();
        AddInFloat();

        FLEXT_ADDMETHOD(0, handle_id_change);
        FLEXT_ADDMETHOD(1, handle_angle_change);

        // Create a UDP socket
        this->fd = socket(AF_INET, SOCK_DGRAM, 0);
        if (this->fd < 0)
        {
            error("Error creating socket for OSC server");
            return;
        }

        memset(&(this->osc_server), 0, sizeof(this->osc_server));
        // Configure osc_server
        this->osc_server.sin_family = AF_INET;
        this->osc_server.sin_port = htons(PORT);
        this->osc_server.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    }

protected:
    void handle_id_change(float motor_id_arg)
    {
        int motor_id = static_cast<int>(motor_id_arg);

        if (motor_id < 0 || motor_id > 5)
        {
            error("Invalid motor id: %d", motor_id);
            return;
        }

        this->motor_id = motor_id;
    }

    void handle_angle_change(float motor_angle_arg)
    {
        int motor_angle = static_cast<int>(motor_angle_arg);

        if (motor_angle < 0 || motor_angle > 255)
        {
            error("Invalid motor angle: %d", motor_angle);
            return;
        }
        this->motor_angle = motor_angle;

        post("Motor %d angle: %d", this->motor_id, this->motor_angle);
        this->motor_control();
    }

private:
    struct sockaddr_in osc_server;
    int fd;
    int motor_id;
    int motor_angle;

    FLEXT_CALLBACK_1(handle_id_change, float);
    FLEXT_CALLBACK_1(handle_angle_change, float);

    void motor_control()
    {
        char buffer[BUFFER_SIZE] = {0};

        int len = tosc_writeMessage(buffer, sizeof(buffer), "/set-motor", "ii", this->motor_id, this->motor_angle);

        if (connect(this->fd, (struct sockaddr *)&(this->osc_server), sizeof(this->osc_server)) < 0)
        {
            error("Error connecting to OSC server");
            return;
        }

        if (send(this->fd, buffer, len, 0) < 0)
        {
            error("Error sending message to OSC server");
            return;
        }
    }
};

FLEXT_NEW("ergojunior", ergojunior)