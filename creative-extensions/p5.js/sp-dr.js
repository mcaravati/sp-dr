// Check that p5 variable is defined
if (typeof p5 === 'undefined') {
    throw new Error('sp-dr.js requires p5.js');
} else if (typeof address === 'undefined') {
    throw new Error('sp-dr.js requires address to be defined');
} else if (typeof port === 'undefined') {
    throw new Error('sp-dr.js requires port to be defined');
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

p5.prototype.setMotor = function (motor, position) {
    if (!motor || !position) {
        throw new Error('Motor and position must be defined');
    } else if (typeof motor !== 'number' || typeof position !== 'number') {
        throw new Error('Motor and position must be numbers');
    } else if (position < 0 || position > 255) {
        throw new Error('Motor position must be between 0 and 255');
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

p5.prototype.enableLED = function (motor, state) {
    if (!motor || !state) {
        throw new Error('Motor and state must be defined');
    } else if (typeof motor !== 'number' || typeof state !== 'boolean') {
        throw new Error('Motor must be a number and state must be a boolean');
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

p5.prototype.enableTorque = function (motor, state) {
    if (!motor || !state) {
        throw new Error('Motor and state must be defined');
    } else if (typeof motor !== 'number' || typeof state !== 'boolean') {
        throw new Error('Motor must be a number and state must be a boolean');
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

p5.prototype.setSpeed = function (motor, speed) {
    if (!motor || !speed) {
        throw new Error('Motor and speed must be defined');
    } else if (typeof motor !== 'number' || typeof speed !== 'number') {
        throw new Error('Motor and speed must be numbers');
    } else if (speed < 0 || speed > 255) {
        throw new Error('Motor speed must be between 0 and 255');
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

p5.prototype.setWebsocketMessageHandler = function (handler) {
    if (!handler) {
        throw new Error('Handler must be defined');
    } else if (typeof handler !== 'function') {
        throw new Error('Handler must be a function');
    }

    websocket.onmessage = handler;
}