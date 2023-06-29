"""
    Abstract class for the robot control (Poppy Ergo Jr)
"""
from abc import ABC, abstractmethod
from typing import Callable, List, Optional, Tuple, Union
import ikpy

class RobotControl(ABC):
    """
        Abstract class for the robot control
    """
    def __init__(self, **kwargs):
        """
            Abstract class for the robot control
        """
        super().__init__()

    @abstractmethod
    def set_motor_angle(self, motor: int = 1, value: int = 0) -> None:
        """
            Set the motor to the value
        """
        pass

    @abstractmethod
    def get_motor_angle(self, motor: int = 1) -> int:
        """
            Get the motor angle
        """
        pass

    def _inverse_kinematics_handler(self, *args) -> None:
        """
            Inverse kinematics handler
        """
        pass
        
