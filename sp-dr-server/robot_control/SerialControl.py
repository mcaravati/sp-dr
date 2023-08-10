"""
    Implementation of RobotControl for serial communication via USB
"""
from robot_control.RobotControl import RobotControl
import serial
import struct
import time
import logging

last_function_call = time.time()

def cooldown(seconds: float):
    """
        Do not call the function if it was called less than seconds ago
    """
    def decorator(func):
        def wrapper(*args, **kwargs):
            global last_function_call
            if time.time() - last_function_call > seconds:
                last_function_call = time.time()
                return func(*args, **kwargs)
            else:
                return None
        return wrapper
    return decorator

class SerialControl(RobotControl):
    def __init__(self, **kwargs):
        super().__init__(**kwargs)

        self._serial = serial.Serial(kwargs.get("port", "/dev/ttyACM0"), kwargs.get("baudrate", 115200), timeout=1)
        self._verbose = kwargs.get("verbose", False)

        if kwargs['verbose']:
            self._logger = logging.getLogger('Serial control')
            self._logger.setLevel(logging.DEBUG)

            self._logger.info("SerialControl: %s opened", self._serial.name)
        else:
            self._logger = None

    def _send_serial(self, op_code, motor_id, value: str) -> None:
        """
            Send a serial command to the robot
        """
        # Create payload hex(op_code)hex(motor_id)hex(value)\n with 0-padded hex values using struct
        header = struct.pack("<BB", int(op_code), int(motor_id)).hex()
        payload = header + value

        self._serial.write(bytearray.fromhex(payload))

        if self._logger:
            self._logger.info(self._serial.read(120))

    def set_led_on(self, motor: int = 1) -> None:
        """
            Set the led of the specified motor on
        """
        self._send_serial(0x01, motor, struct.pack("<B", 0x01).hex())

    def set_led_off(self, motor: int = 1) -> None:
        """
            Set the led of the specified motor off
        """
        self._send_serial(0x01, motor, struct.pack("<B", 0x00).hex())

    def set_torque_on(self, motor: int = 1) -> None:
        """
            Set the torque of the specified motor on
        """
        self._send_serial(0x02, motor, struct.pack("<B", 0x01).hex())

    def set_torque_off(self, motor: int = 1) -> None:
        """
            Set the torque of the specified motor off
        """
        self._send_serial(0x02, motor, struct.pack("<B", 0x00).hex())

    def set_motor_speed(self, motor: int = 1, speed: int = 0) -> None:
        """
            Set the motor speed
        """
        self._send_serial(0x03, motor, struct.pack("<l", speed).hex())

    @cooldown(0.009)
    def set_motor_angle(self, motor: int = 1, value: float = 0) -> None:
        """
            Set the motor to the value
        """
        self._send_serial(0x04, motor, struct.pack("<f", value).hex())

    def compute_angles(self, x: float = 0, y: float = 0, z: float = 0) -> None:
        return super().compute_angles(x, y, z)

    