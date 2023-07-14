"""
    Abstract class for the control server via real-time communication protocol
"""
from abc import ABC, abstractmethod
from robot_control.RobotControl import RobotControl

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

    @abstractmethod
    def inverse_kinematics_handler(self, args) -> None:
        """
            Handle the message for the inverse kinematics
        """
        self._compute_angles(*args)

    @abstractmethod
    def motor_led_handler(self, args) -> None:
        """
            Handle the message for the motor led
        """
        self._set_led(*args)

    @abstractmethod
    def torque_handler(self, args) -> None:
        """
            Handle the message for the motor torque
        """
        self._set_torque(*args)

    @abstractmethod
    def speed_handler(self, args) -> None:
        """
            Handle the message for the motor speed
        """
        self._set_motor_speed(*args)

    def _set_motor(self, motor: int = 1, value: float = 0.0) -> None:
        """
            Set the motor to the value
        """
        self._robot_control.set_motor_angle(motor, value)

    def _compute_angles(self, x: float = 0.0, y: float = 0.0, z: float = 0.0) -> None:
        """
            Compute the angles for an x, y, z position
        """
        return self._robot_control.compute_angles(x, y, z)

    def _set_led(self, motor: int = 1, value: bool = False) -> None:
        """
            Set the led of the specified motor
        """
        if value:
            self._robot_control.set_led_on(motor)
        else:
            self._robot_control.set_led_off(motor)

    def _set_torque(self, motor: int = 1, value: bool = False) -> None:
        """
            Set the torque of the specified motor
        """
        if value:
            self._robot_control.set_torque_on(motor)
        else:
            self._robot_control.set_torque_off(motor)

    def _set_motor_speed(self, motor: int = 1, value: float = 0.0) -> None:
        """
            Set the motor speed
        """
        self._robot_control.set_motor_speed(motor, value)

    