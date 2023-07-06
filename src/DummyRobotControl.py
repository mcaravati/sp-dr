"""
    Dummy implementation of RobotControl
"""
from RobotControl import RobotControl

class DummyRobotControl(RobotControl):
    def __init__(self, **kwargs):
        super().__init__(**kwargs)

        print("DummyRobotControl: Dummy robot control initialized")

    def set_motor_angle(self, motor: int = 1, value: int = 0) -> None:
        print(f"DummyRobotControl: Set motor {motor} to {value}")
        pass

    def get_motor_angle(self, motor: int = 1) -> int:
        print(f"DummyRobotControl: Get motor {motor}")
        pass

    