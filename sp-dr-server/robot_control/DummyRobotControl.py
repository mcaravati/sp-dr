"""
    Dummy implementation of RobotControl
"""
from robot_control.RobotControl import RobotControl
import logging

class DummyRobotControl(RobotControl):
    def __init__(self, **kwargs):
        super().__init__(**kwargs)

        self._logger = logging.getLogger("Dummy control")
        self._logger.setLevel(logging.INFO)

        self._logger.info("DummyRobotControl: Dummy robot control initialized")

    def set_motor_angle(self, motor: int = 1, value: int = 0) -> None:
        self._logger.info("DummyRobotControl: Set motor %s to %s", motor, value)

    def set_led_on(self, motor: int = 1) -> None:
        self._logger.info("DummyRobotControl: Set led of motor %s on", motor)

    def set_led_off(self, motor: int = 1) -> None:
        self._logger.info("DummyRobotControl: Set led of motor %s off", motor)

    def set_torque_on(self, motor: int = 1) -> None:
        self._logger.info("DummyRobotControl: Set torque of motor %s on", motor)

    def set_torque_off(self, motor: int = 1) -> None:
        self._logger.info("DummyRobotControl: Set torque of motor %s off", motor)

    def set_motor_speed(self, motor: int = 1, speed: int = 0) -> None:
        self._logger.info("DummyRobotControl: Set motor %s speed to %s", speed)

    def compute_angles(self, x: float = 0, y: float = 0, z: float = 0) -> None:
        self._logger.info("DummyRobotControl: Compute angles for x=%s, y=%s, z=%s", x, y, z)
        return super().compute_angles(x, y, z)

    