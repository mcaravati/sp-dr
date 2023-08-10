#include <Dynamixel2Arduino.h>
#include "op_codes.h"

#define DXL_SERIAL Serial1
#define DEBUG_SERIAL Serial

#define MOTOR_BAUDRATE 1000000 // DXL-320 baudrate
#define DXL_DIR_PIN 28         // OpenCM 9.04 DYNAMIXEL TTL Bus
#define DXL_PROTOCOL_VERSION 2.0
#define ANGLE_TOLERANCE 0.5
#define VELOCITY 0
#define BUFFER_SIZE 4

#define DEBUG

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
void _set_motor(int motor_index, float position)
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
    byte buffer[BUFFER_SIZE] = {0};
    size_t bytes_read = DEBUG_SERIAL.readBytes(buffer, 2);

    if (bytes_read % 2 != 0)
    {
#ifdef DEBUG
      DEBUG_SERIAL.println("Invalid message length");
#endif
      return;
    }

    byte header = buffer[0];
    byte motorID = buffer[1];

    if (motorID < 1 || motorID > 6)
    {
#ifdef DEBUG
      DEBUG_SERIAL.println("Invalid motor ID");
#endif
      return;
    }

#ifdef DEBUG
    DEBUG_SERIAL.printf("Received packet: Header: 0x%02X, Motor ID: %d\n", header, motorID);
#endif

    switch (header)
    {
      case OP_LED: // Setting the LED state of a motor
        {
          DEBUG_SERIAL.readBytes(buffer, 1);
          byte data = buffer[0];

          if (data == 0x00)
          {
            // Turn off LED for motorID
            dxl.ledOff(motorID);
          }
          else if (data == 0x01)
          {
            // Turn on LED for motorID
            dxl.ledOn(motorID);
          }
          break;
        }

      case OP_TORQUE: // Setting the torque state of a motor
        {
          DEBUG_SERIAL.readBytes(buffer, 1);
          byte data = buffer[0];

          if (data == 0x00)
          {
            // Turn off torque for motorID
            dxl.torqueOff(motorID);
          }
          else if (data == 0x01)
          {
            // Turn on torque for motorID
            dxl.torqueOn(motorID);
          }
          break;
        }

      case OP_SPEED: // Setting the speed of a motor
        {
          DEBUG_SERIAL.readBytes(buffer, 4);
          int32_t data;
          memcpy(&data, buffer, 4);

          dxl.writeControlTableItem(GOAL_VELOCITY, motorID, data);
          break;
        }

      case OP_POSITION: // Setting the angle of a motor
        {
          DEBUG_SERIAL.readBytes(buffer, 4);
          float data;
          memcpy(&data, buffer, 4);

#ifdef DEBUG
          DEBUG_SERIAL.printf("Float value: %f\n", data);
#endif
          _set_motor(motorID, data);
          break;
        }

      default:
#ifdef DEBUG
        DEBUG_SERIAL.println("Invalid header");
#endif
        break;
    }
  }
}
