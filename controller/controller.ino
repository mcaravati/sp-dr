#include <Dynamixel2Arduino.h>

#define DXL_SERIAL Serial1
#define DEBUG_SERIAL Serial

#define MOTOR_BAUDRATE 1000000 // DXL-320 baudrate
#define DXL_DIR_PIN 28         // OpenCM 9.04 DYNAMIXEL TTL Bus
#define DXL_PROTOCOL_VERSION 2.0
#define ANGLE_TOLERANCE 0.5
#define VELOCITY 0

Dynamixel2Arduino dxl(DXL_SERIAL, DXL_DIR_PIN);

// This namespace is required to use Control table item names
using namespace ControlTableItem;

void setup()
{
  // Use UART port of DYNAMIXEL Shield to debug.
  DEBUG_SERIAL.begin(115200);
  while (!DEBUG_SERIAL)
    ;

  dxl.begin(MOTOR_BAUDRATE);
  dxl.setPortProtocolVersion(DXL_PROTOCOL_VERSION);

  for (int motor_index = 1; motor_index <= 6; motor_index++)
  {
    // Get DYNAMIXEL information
    dxl.ping(motor_index);

    // Turn off torque when configuring items in EEPROM area
    dxl.torqueOff(motor_index);
    dxl.setOperatingMode(motor_index, OP_POSITION);
    dxl.torqueOn(motor_index);

    // Limit the maximum velocity in Position Control Mode. Use 0 for Max speed
    dxl.writeControlTableItem(PROFILE_VELOCITY, motor_index, VELOCITY);
  }

  DEBUG_SERIAL.println("ready");
}

/**
 * @brief Sets The goal position of a motor.
 *
 * @param motor The Motor struct representing the motor to set the position for.
 */
void _set_motor(int motor_index, int position)
{
  int moving = 1;

  if (dxl.setGoalPosition(motor_index, position, UNIT_DEGREE) != 1)
  {
#ifdef DEBUG
    DEBUG_SERIAL.printf("Failed to set goal position for motor %d: Error code %d\n", motor_index, dxl.getLastLibErrCode());
#endif
    return;
  }

  // while((moving = dxl.readControlTableItem(MOVING, motor_index)) == 1);
#ifdef DEBUG
  DEBUG_SERIAL.printf("Motor %d has finished moving\n", motor_index);
#endif
}

void loop()
{
  if (DEBUG_SERIAL.available() > 0)
  {
    byte buffer[2] = {0};
    size_t bytes_read = DEBUG_SERIAL.readBytes(buffer, 2);

    if (bytes_read % 2 != 0)
    {
#ifdef DEBUG
      DEBUG_SERIAL.println("Invalid message length");
#endif
      return;
    }

    _set_motor((int)buffer[0], (int)buffer[1]);

#ifdef DEBUG
    DEBUG_SERIAL.printf("Motor ID: %d. Motor Position: %d\n", (int)buffer[0], (int)buffer[1]);
#endif
  }
}
