#include <Dynamixel2Arduino.h>

#define DXL_SERIAL Serial1
#define DEBUG_SERIAL Serial

#define MOTOR_BAUDRATE 1000000 // DXL-320 baudrate
#define DXL_DIR_PIN 28         // OpenCM 9.04 DYNAMIXEL TTL Bus
#define DXL_PROTOCOL_VERSION 2.0

#define NEW_MOTOR_ID 1

Dynamixel2Arduino dxl(DXL_SERIAL, DXL_DIR_PIN);
using namespace ControlTableItem;

void setup()
{
    // Use UART port of DYNAMIXEL Shield to debug.
    DEBUG_SERIAL.begin(115200);
    while (!DEBUG_SERIAL)
        ;

    dxl.begin(MOTOR_BAUDRATE);
    dxl.setPortProtocolVersion(DXL_PROTOCOL_VERSION);

    DEBUG_SERIAL.println("Looking for motor...");
    if (!dxl.scan()) {
        DEBUG_SERIAL.println("No motor found.");
        return;
    }

    for (int index = 0; index < 256; index++) {
        if (dxl.ping(index)) {
            DEBUG_SERIAL.printf("Found motor at ID %d\n", index);
            dxl.setID(index, NEW_MOTOR_ID);
            DEBUG_SERIAL.printf("Set motor ID to %d\n", NEW_MOTOR_ID);
            return;
        }
    }

    DEBUG_SERIAL.println("No motor found.");
}

void loop()
{
}