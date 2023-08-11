from osc4py3 import oscbuildparse
from osc4py3.as_eventloop import osc_send, osc_startup, osc_udp_client, osc_process, osc_terminate

class Client:
    def __init__(self, host: str, port: int, client_name: str = "Python OSC Client") -> None:
        self._name = client_name

        osc_startup()
        osc_udp_client(host, port, self._name)

        self._send_message(oscbuildparse.OSCMessage("/connected", None, [True])) # The 'True' value is required or else the message is ignored by the server

    def _send_message(self, message: oscbuildparse.OSCMessage) -> None:
        osc_send(message, self._name)
        osc_process()

    def set_motor(self, motor_id: int, angle: float) -> None:
        self._send_message(oscbuildparse.OSCMessage("/set-motor", None, [motor_id, angle]))

    def toggle_led(self, motor_id: int, state: bool) -> None:
        self._send_message(oscbuildparse.OSCMessage("/set-led", None, [motor_id, state]))

    def toggle_torque(self, motor_id: int, state: bool) -> None:
        self._send_message(oscbuildparse.OSCMessage("/set-torque", None, [motor_id, state]))

    def set_speed(self, motor_id: int, speed: int) -> None:
        self._send_message(oscbuildparse.OSCMessage("/set-speed", None, [motor_id, speed]))

    def inverse_kinematics(self, x: float, y: float, z: float) -> None:
        self._send_message(oscbuildparse.OSCMessage("/inverse-kinematics", None, [x, y, z]))

    def __del__(self):
        osc_terminate()
        