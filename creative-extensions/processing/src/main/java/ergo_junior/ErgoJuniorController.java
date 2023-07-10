package ergo_junior;

import java.util.HashMap;
import processing.core.*;
import oscP5.*;
import netP5.*;


public class ErgoJuniorController {
    private static final String MOTOR_ID_ERROR_MESSAGE = "Motor id must be between 1 and 6.";
    private static final String MOTOR_ANGLE_ERROR_MESSAGE = "Motor angle must be between 0 and 255.";
    private static final String MOTOR_SPEED_ERROR_MESSAGE = "Motor speed must be between 0 and 255.";
    private static final String PAPPLET_ERROR_MESSAGE = "Parent PApplet must not be null.";
    private static final String EMPTY_OSC_ADDRESS = "OSC server IP address must not be null or empty.";
    private static final String BAD_OSC_PORT = "OSC server port number must be between 0 and 65535.";

    private PApplet parent;
    private OscP5 oscP5;
    private NetAddress oscServerAddress;

    private HashMap<Integer, Integer> motorMap = new HashMap<>();

    public ErgoJuniorController(PApplet parent, String oscServerIP, int oscServerPort) {
        if (parent == null) {
            throw new IllegalArgumentException(PAPPLET_ERROR_MESSAGE);
        
        // Check if the OSC server address is valid.
        } else if (oscServerIP == null || oscServerIP.equals("")) {
            throw new IllegalArgumentException(EMPTY_OSC_ADDRESS);
        
        // Check if the OSC server port is valid.
        } else if (oscServerPort < 0 || oscServerPort > 65535) {
            throw new IllegalArgumentException(BAD_OSC_PORT);
        }

        // Set the OSC server address.
        this.oscServerAddress = new NetAddress(oscServerIP, oscServerPort);
        this.parent = parent;
        this.oscP5 = new OscP5(this.parent, 12000);
    }

    /**
     * Save the motor angle in memory and send it to the OSC server if it has changed.
     * 
     * @param motorId {int} The motor id.
     * @param motorAngle {int} The motor angle.
     */
    public void setMotorAngle(int motorId, int motorAngle) {
        if (motorId < 1 || motorId > 6) {
            throw new IllegalArgumentException(MOTOR_ID_ERROR_MESSAGE);
        }
        if (motorAngle < 0 || motorAngle > 255) {
            throw new IllegalArgumentException(MOTOR_ANGLE_ERROR_MESSAGE);
        }

        if (this.motorMap.containsKey(motorId)) {
            int prevAngle = this.motorMap.get(motorId);
            if (prevAngle != motorAngle) {
                this.motorMap.put(motorId, motorAngle);
                sendPacket("/set-motor", motorId, motorAngle);
            }
        } else {
            this.motorMap.put(motorId, motorAngle);
            sendPacket("/set-motor", motorId, motorAngle);
        }
    }

    /**
     * Set the LED of the given motor to on.
     * 
     * @param motorId {int} The motor id.
     */
    public void setLedOn(int motorId) {
        if (motorId < 1 || motorId > 6) {
            throw new IllegalArgumentException(MOTOR_ID_ERROR_MESSAGE);
        }

        sendPacket("/set-led", motorId, 1);
    }

    /**
     * Set the LED of the given motor to off.
     * 
     * @param motorId {int} The motor id.
     */
    public void setLedOff(int motorId) {
        if (motorId < 1 || motorId > 6) {
            throw new IllegalArgumentException(MOTOR_ID_ERROR_MESSAGE);
        }

        sendPacket("/set-led", motorId, 0);
    }

    /**
     * Set the torque of the given motor to on.
     * 
     * @param motorId {int} The motor id.
     */
    public void setTorqueOn(int motorId) {
        if (motorId < 1 || motorId > 6) {
            throw new IllegalArgumentException(MOTOR_ID_ERROR_MESSAGE);
        }

        sendPacket("/set-torque", motorId, 1);
    }

    /**
     * Set the torque of the given motor to off.
     * 
     * @param motorId {int} The motor id.
     */
    public void setTorqueOff(int motorId) {
        if (motorId < 1 || motorId > 6) {
            throw new IllegalArgumentException(MOTOR_ID_ERROR_MESSAGE);
        }

        sendPacket("/set-torque", motorId, 0);
    }

    public void setMotorSpeed(int motorId, int motorSpeed) {
        if (motorId < 1 || motorId > 6) {
            throw new IllegalArgumentException(MOTOR_ID_ERROR_MESSAGE);
        }
        if (motorSpeed < 0 || motorSpeed > 255) {
            throw new IllegalArgumentException(MOTOR_SPEED_ERROR_MESSAGE);
        }

        sendPacket("/set-speed", motorId, motorSpeed);
    }

    /**
     * Simply send the motor packet to the OSC server.
     * 
     * @param path {String} The OSC path.
     * @param motorId {int} The motor id.
     * @param value {int} Arbitrary value for the given path.
     */
    private void sendPacket(String path, int motorId, int value) {
        OscMessage msg = new OscMessage(path);
        msg.add(motorId);
        msg.add(value);
        oscP5.send(msg, this.oscServerAddress);
    }
}