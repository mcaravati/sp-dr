"""
    Dummy implementation of RobotControl
"""
from robot_control.RobotControl import RobotControl

class DummyRobotControl(RobotControl):
    def __init__(self, **kwargs):
        super().__init__(**kwargs)

        print("DummyRobotControl: Dummy robot control initialized")

    def set_motor_angle(self, motor: int = 1, value: int = 0) -> None:
        print(f"DummyRobotControl: Set motor {motor} to {value}")

    def set_led_on(self, motor: int = 1) -> None:
        print(f"DummyRobotControl: Set led of motor {motor} on")

    def set_led_off(self, motor: int = 1) -> None:
        print(f"DummyRobotControl: Set led of motor {motor} off")

    def set_torque_on(self, motor: int = 1) -> None:
        print(f"DummyRobotControl: Set torque of motor {motor} on")

    def set_torque_off(self, motor: int = 1) -> None:
        print(f"DummyRobotControl: Set torque of motor {motor} off")

    def set_motor_speed(self, motor: int = 1, speed: int = 0) -> None:
        print(f"DummyRobotControl: Set motor {motor} speed to {speed}")

    def compute_angles(self, x: float = 0, y: float = 0, z: float = 0) -> None:
        print(f"DummyRobotControl: Compute angles for x={x}, y={y}, z={z}")
        return super().compute_angles(x, y, z)

    