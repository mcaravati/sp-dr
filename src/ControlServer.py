"""
    Abstract class for the control server via real-time communication protocol
"""
from abc import ABC, abstractmethod
from typing import Callable, List, Optional, Tuple, Union
from RobotControl import RobotControl

class ControlServer(ABC):
    """
        Abstract class for the control server via real-time communication protocol
    """
    def __init__(self, **kwargs):
        """
            Abstract class for the control server via real-time communication protocol
        """
        super().__init__()

        self._robot_control: RobotControl = kwargs.get("robot_control", None)

        if self._robot_control is None:
            raise ValueError("robot_control is required")
        elif not isinstance(self._robot_control, RobotControl):
            raise ValueError("robot_control must be an instance of RobotControl")

    @abstractmethod
    def start(self) -> None:
        """
            Start the server
        """
        pass

    @abstractmethod
    def stop(self) -> None:
        """
            Stop the server
        """
        pass

    @abstractmethod
    def forward_kinematics_handler(self, args) -> None:
        """
            Handle the message for the forward kinematics
        """
        self._set_motor(*args)
        pass

    def _set_motor(self, motor: int = 1, value: float = 0.0) -> None:
        """
            Set the motor to the value
        """
        self._robot_control.set_motor_angle(motor, value)
