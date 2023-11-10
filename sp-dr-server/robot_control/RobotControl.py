"""
    Abstract class for the robot control (Poppy Ergo Jr)
"""
from abc import ABC, abstractmethod
import ikpy.chain as ikchain
import math
import numpy as np

urdf_file = "simulator/ergo_jr/ergo_jr.urdf"
ergo_jr_chain = ikchain.Chain.from_urdf_file(urdf_file)

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

    @abstractmethod
    def compute_angles(self, x: float = 0.0, y: float = 0.0, z: float = 0.0) -> None:
        """
            Inverse kinematics handler
        """
        result = ergo_jr_chain.inverse_kinematics([x, y, z])
        angles = np.degrees(result)
        for index, motor_angle in enumerate(angles):
            # Angle is in radian, convert to degree
            self.set_motor_angle(index + 1, (motor_angle + 360) % 360)  
        
        
