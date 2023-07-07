"""
    Abstract class for the robot control (Poppy Ergo Jr)
"""
from abc import ABC, abstractmethod

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
    def set_led_on(self, motor: int = 1) -> None:
        """
            Set the led of the specified motor on
        """
        pass

    @abstractmethod
    def set_led_off(self, motor: int = 1) -> None:
        """
            Set the led of the specified motor off
        """
        pass

    @abstractmethod
    def set_torque_on(self, motor: int = 1) -> None:
        """
            Set the torque of the specified motor on
        """
        pass

    @abstractmethod
    def set_torque_off(self, motor: int = 1) -> None:
        """
            Set the torque of the specified motor off
        """
        pass

    @abstractmethod
    def set_motor_speed(self, motor: int = 1, speed: int = 0) -> None:
        """
            Set the motor speed
        """
        pass

    @abstractmethod
    def set_motor_angle(self, motor: int = 1, value: int = 0) -> None:
        """
            Set the motor to the value
        """
        pass

    def _inverse_kinematics_handler(self, *args) -> None:
        """
            Inverse kinematics handler
        """
        pass
        
