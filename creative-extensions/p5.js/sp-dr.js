// Check that p5 variable is defined
if (typeof p5 === 'undefined') {
    throw new Error('sp-dr.js: sp-dr.js requires p5.js');
} else if (typeof address === 'undefined') {
    throw new Error('sp-dr.js: sp-dr.js requires address to be defined');
} else if (typeof port === 'undefined') {
    throw new Error('sp-dr.js: sp-dr.js requires port to be defined');
}

const websocket = new WebSocket(`ws://${address}:${port}`);
let connectionOpened = false;
const messageQueue = [];

websocket.onopen = function () {
    console.info('Websocket connection opened');
    connectionOpened = true;

    messageQueue.forEach(message => websocket.send(message));
}
websocket.onclose = function () {
    console.info('Websocket connection closed');
}
websocket.onerror = function (error) {
    console.error('Websocket error: ' + error);
}

/**
 * Sets the position of a motor
 * 
 * @param {number} motor The ID of the motor
 * @param {number} position The desired position of the motor
 */
p5.prototype.setMotor = function (motor, position) {
    if (!motor || !position) {
        throw new Error('setMotor: Motor and position must be defined');
    } else if (typeof motor !== 'number' || typeof position !== 'number') {
        throw new Error('setMotor: Motor and position must be numbers');
    } else if (position < 0 || position > 255) {
        throw new Error('setMotor: Motor position must be between 0 and 255');
    }

    const message = JSON.stringify({
        type: 'set-motor',
        data: [
            motor,
            position
        ]
    });

    if (!connectionOpened) {
        messageQueue.push(message);
    } else {
        websocket.send(message);
    }
}

/**
 * Enable or disable the LED of a given motor
 * 
 * @param {number} motor The ID of the motor
 * @param {boolean} state The state of the LED
 */
p5.prototype.toggleLED = function (motor, state) {
    if (!motor || !state) {
        throw new Error('toggleLED: Motor and state must be defined');
    } else if (typeof motor !== 'number' || typeof state !== 'boolean') {
        throw new Error('toggleLED: Motor must be a number and state must be a boolean');
    }

    const message = JSON.stringify({
        type: 'set-led',
        data: [
            led,
            state
        ]
    });

    if (!connectionOpened) {
        messageQueue.push(message);
    } else {
        websocket.send(message);
    }
}

/**
 * Enable or disable the torque of a motor
 * 
 * @param {number} motor The ID of the motor 
 * @param {boolean} state The state of the torque of the motor
 */
p5.prototype.toggleTorque = function (motor, state) {
    if (!motor || !state) {
        throw new Error('toggleTorque: Motor and state must be defined');
    } else if (typeof motor !== 'number' || typeof state !== 'boolean') {
        throw new Error('toggleTorque: Motor must be a number and state must be a boolean');
    }

    const message = JSON.stringify({
        type: 'set-torque',
        data: [
            motor,
            state
        ]
    });

    if (!connectionOpened) {
        messageQueue.push(message);
    } else {
        websocket.send(message);
    }
}

/**
 * Set the desired speed of a motor
 * 
 * @param {number} motor The ID of the motor
 * @param {number} speed The desired speed of the motor
 */
p5.prototype.setSpeed = function (motor, speed) {
    if (!motor || !speed) {
        throw new Error('setSpeed: Motor and speed must be defined');
    } else if (typeof motor !== 'number' || typeof speed !== 'number') {
        throw new Error('setSpeed: Motor and speed must be numbers');
    } else if (speed < 0 || speed > 255) {
        throw new Error('setSpeed: Motor speed must be between 0 and 255');
    }

    const message = JSON.stringify({
        type: 'set-speed',
        data: [
            motor,
            speed
        ]
    });

    if (!connectionOpened) {
        messageQueue.push(message);
    } else {
        websocket.send(message);
    }
}

/**
 * Make the robot point to position x, y, z
 * 
 * @param {number} x The x position
 * @param {number} y The y position
 * @param {number} z The z position
 */
p5.prototype.inverseKinematics = function (x, y, z) {
    if (!x || !y || !z) {
        throw new Error('inverseKinematics: x, y and z must be defined');
    } else if (typeof x !== 'number' || typeof y !== 'number' || typeof z !== 'number') {
        throw new Error('inverseKinematics: x, y and z must be numbers');
    }

    const message = JSON.stringify({
        type: 'inverse-kinematics',
        data: [
            x,
            y,
            z
        ]
    });

    if (!connectionOpened) {
        messageQueue.push(message);
    } else {
        websocket.send(message);
    }
}

/**
 * Sets the handler for when a message is received from the websocket connection
 * 
 * @param {function} handler The handler function
 */
p5.prototype.setWebsocketMessageHandler = function (handler) {
    if (!handler) {
        throw new Error('setWebsocketMessageHandler: Handler must be defined');
    } else if (typeof handler !== 'function') {
        throw new Error('setWebsocketMessageHandler: Handler must be a function');
    }

    websocket.onmessage = handler;
}