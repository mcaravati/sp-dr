"""
    Implements the ControlServer class using the OSC protocol
"""

from typing import Union
from ControlServer import ControlServer
from osc4py3.as_eventloop import *
import logging
from StoppableThread import StoppableThread
import threading
import osc4py3.oscmethod as osm

class OSCServer(ControlServer):
    def __init__(self, **kwargs) -> None:
        """
            Implements the ControlServer class using the OSC protocol
        """
        super().__init__(**kwargs)

        self._osc_server = None

        logging.basicConfig(format='%(asctime)s - %(threadName)s ø %(name)s - %(levelname)s - %(message)s')
        self._logger = logging.getLogger("osc")
        self._logger.setLevel(logging.DEBUG)
    
    def start(self) -> None:
        """
            Start the server
        """
        osc_startup(
            logger=self._logger,
        )

        osc_udp_server("127.0.0.1", 9000, "server")

        osc_method("/set-motor", self.forward_kinematics_handler)

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