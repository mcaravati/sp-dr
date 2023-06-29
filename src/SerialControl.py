"""
    Implementation of RobotControl for serial communication via USB
"""
from RobotControl import RobotControl
import serial
import struct
import time

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

        if self._verbose:
            print(f"SerialControl: {self._serial.name} opened")

    @cooldown(0.009)
    def set_motor_angle(self, motor: int = 1, value: int = 0) -> None:
        """
            Set the motor to the value
        """
        # Read while there is data
        while self._serial.in_waiting:
            print(self._serial.readline().decode("utf-8").rstrip())

        # Truncate float
        value = int(value)
        motor = int(motor)

        # Create payload hex(motor)hex(value)\n with 0-padded hex values using struct
        payload = struct.pack("BB", motor, value).hex()

        self._serial.write(bytearray.fromhex(payload))

    def get_motor_angle(self, motor: int = 1) -> int:
        """
            Get the motor angle
        """
        pass

    