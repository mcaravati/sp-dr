"""
    Implements the ControlServer class using the OSC protocol
"""

from typing import Union
from server.ControlServer import ControlServer
from osc4py3.as_eventloop import osc_startup, osc_udp_server, osc_method, osc_process, osc_terminate
import logging
from StoppableThread import StoppableThread
import threading

class OSCServer(ControlServer):
    def __init__(self, **kwargs) -> None:
        """
            Implements the ControlServer class using the OSC protocol
        """
        super().__init__(**kwargs)

        self._osc_server = None

        self._host = kwargs['host']
        self._port = kwargs['port']

        if kwargs['verbose']:
            self._logger = logging.getLogger("OSC server")
            self._logger.setLevel(logging.DEBUG)
        else:
            self._logger = None
    
    def start(self) -> None:
        """
            Start the server
        """
        osc_startup(
            logger=self._logger,
        )

        osc_udp_server(self._host, self._port, "server")

        osc_method("/set-motor", self.forward_kinematics_handler)
        osc_method("/set-led", self.motor_led_handler)
        osc_method("/set-torque", self.torque_handler)
        osc_method("/set-speed", self.speed_handler)
        osc_method("/inverse-kinematics", self.inverse_kinematics_handler)

        self._osc_server = StoppableThread(target=self._osc_process)
        self._osc_server.start()

    def _osc_process(self) -> None:
        while not threading.current_thread().stopped():
            osc_process()

    def stop(self) -> None:
        """
            Stop the server
        """
        self._osc_server.stop()
        self._osc_server.join()
        osc_terminate()

    def forward_kinematics_handler(self, *args) -> None:
        return super().forward_kinematics_handler(args)
    
    def motor_led_handler(self, *args) -> None:
        return super().motor_led_handler(args)
    
    def torque_handler(self, *args) -> None:
        return super().torque_handler(args)
    
    def speed_handler(self, *args) -> None:
        return super().speed_handler(args)
    
    def inverse_kinematics_handler(self, args) -> None:
        return super().inverse_kinematics_handler(args)