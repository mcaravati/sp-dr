package ergo_junior;

import java.util.HashMap;
import processing.core.*;
import oscP5.*;
import netP5.*;

public class ErgoJuniorController {
    private PApplet parent;
    private OscP5 oscP5;
    private NetAddress oscServerAddress;

    private HashMap<Integer, Integer> motorMap = new HashMap<Integer, Integer>();

    public ErgoJuniorController(PApplet parent, String oscServerIP, int oscServerPort) {
        if (parent == null) {
            throw new IllegalArgumentException("Parent PApplet must not be null.");
        
        // Check if the OSC server address is valid.
        } else if (oscServerIP == null || oscServerIP.equals("")) {
            throw new IllegalArgumentException("OSC server IP address must not be null or empty.");
        
        // Check if the OSC server port is valid.
        } else if (oscServerPort < 0 || oscServerPort > 65535) {
            throw new IllegalArgumentException("OSC server port number must be between 0 and 65535.");
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
    public void setMotor(int motorId, int motorAngle) {
        if (motorId < 0 || motorId > 6) {
            throw new IllegalArgumentException("Motor id must be between 0 and 6.");
        }
        if (motorAngle < 0 || motorAngle > 255) {
            throw new IllegalArgumentException("Motor angle must be between 0 and 255.");
        }

        if (this.motorMap.containsKey(motorId)) {
            int prevAngle = this.motorMap.get(motorId);
            if (prevAngle != motorAngle) {
                this.motorMap.put(motorId, motorAngle);
                sendMotorAngle(motorId, motorAngle);
            }
        } else {
            this.motorMap.put(motorId, motorAngle);
            sendMotorAngle(motorId, motorAngle);
        }
    }

    /**
     * Simply send the motor angle to the OSC server.
     * 
     * @param motorId {int} The motor id.
     * @param motorAngle {int} The motor angle.
     */
    private void sendMotorAngle(int motorId, int motorAngle) {
        OscMessage msg = new OscMessage("/set-motor");
        msg.add(motorId);
        msg.add(motorAngle);
        oscP5.send(msg, this.oscServerAddress);
    }
}