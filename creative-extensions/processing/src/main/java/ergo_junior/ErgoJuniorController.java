package ergo_junior;

import java.util.HashMap;
import java.util.List;
import java.util.Arrays;
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

    private HashMap<Integer, Float> motorMap = new HashMap<>();

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

        sendPacket("/connected", Arrays.asList(new Integer(1)));
    }

    /**
     * Save the motor angle in memory and send it to the OSC server if it has changed.
     * 
     * @param motorId {Integer} The motor id.
     * @param motorAngle {Float} The motor angle.
     */
    public void setMotorAngle(Integer motorId, Float motorAngle) {
        if (motorId < 1 || motorId > 6) {
            throw new IllegalArgumentException(MOTOR_ID_ERROR_MESSAGE);
        }
        if (motorAngle < 0 || motorAngle > 255) {
            throw new IllegalArgumentException(MOTOR_ANGLE_ERROR_MESSAGE);
        }

        if (this.motorMap.containsKey(motorId)) {
            float prevAngle = this.motorMap.get(motorId);
            if (prevAngle != motorAngle) {
                this.motorMap.put(motorId, motorAngle);
                sendPacket("/set-motor", Arrays.asList(motorId, motorAngle));
            }
        } else {
            this.motorMap.put(motorId, motorAngle);
            sendPacket("/set-motor", Arrays.asList(motorId, motorAngle));
        }
    }

    /**
     * Set the LED of the given motor to on.
     * 
     * @param motorId {Integer} The motor id.
     */
    public void setLedOn(Integer motorId) {
        if (motorId < 1 || motorId > 6) {
            throw new IllegalArgumentException(MOTOR_ID_ERROR_MESSAGE);
        }

        sendPacket("/set-led", Arrays.asList(motorId, 1));
    }

    /**
     * Set the LED of the given motor to off.
     * 
     * @param motorId {Integer} The motor id.
     */
    public void setLedOff(Integer motorId) {
        if (motorId < 1 || motorId > 6) {
            throw new IllegalArgumentException(MOTOR_ID_ERROR_MESSAGE);
        }

        sendPacket("/set-led", Arrays.asList(motorId, 0));
    }

    /**
     * Set the torque of the given motor to on.
     * 
     * @param motorId {Integer} The motor id.
     */
    public void setTorqueOn(Integer motorId) {
        if (motorId < 1 || motorId > 6) {
            throw new IllegalArgumentException(MOTOR_ID_ERROR_MESSAGE);
        }

        sendPacket("/set-torque", Arrays.asList(motorId, 1));
    }

    /**
     * Set the torque of the given motor to off.
     * 
     * @param motorId {Integer} The motor id.
     */
    public void setTorqueOff(Integer motorId) {
        if (motorId < 1 || motorId > 6) {
            throw new IllegalArgumentException(MOTOR_ID_ERROR_MESSAGE);
        }

        sendPacket("/set-torque", Arrays.asList(motorId, 0));
    }

    /**
     * Sets the goal speed of a given motor.
     * 
     * @param motorId {Integer} The motor id.
     * @param motorSpeed {Integer} The motor speed.
     */
    public void setMotorSpeed(Integer motorId, Integer motorSpeed) {
        if (motorId < 1 || motorId > 6) {
            throw new IllegalArgumentException(MOTOR_ID_ERROR_MESSAGE);
        }
        if (motorSpeed < 0 || motorSpeed > 255) {
            throw new IllegalArgumentException(MOTOR_SPEED_ERROR_MESSAGE);
        }

        sendPacket("/set-speed", Arrays.asList(motorId, motorSpeed));
    }

    /**
     * Make the robot point to the given coordinates.
     * 
     * @param x {Float} The x coordinate.
     * @param y {Float} The y coordinate.
     * @param z {Float} The z coordinate.
     */
    public void inverseKinematics(Float x, Float y, Float z) {
        sendPacket("/inverse-kinematics", Arrays.asList(x, y, z));
    }

    /**
     * Simply send the motor packet to the OSC server.
     * 
     * @param path {String} The OSC path.
     * @param args {List<Object>} The arguments to send to the OSC server.
     */
    private void sendPacket(String path, List<Object> args) {
        // Check that the arguments are integers or floats.
        for (Object arg : args) {
            if (!(arg instanceof Integer) && !(arg instanceof Float) || arg == null) {
                throw new IllegalArgumentException("Arguments must be integers or floats.");
            }
        }

        OscMessage msg = new OscMessage(path);
        args.forEach(arg -> {
            if (arg instanceof Integer) {
                msg.add(((Integer) arg).intValue());
            } else {
                msg.add(((Float) arg).floatValue());
            }
        });
        oscP5.send(msg, this.oscServerAddress);
    }
}