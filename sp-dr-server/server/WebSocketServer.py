from server.ControlServer import ControlServer
from websockets import serve
import asyncio
import json
import logging

class UnknownMessageTypeException(Exception):
    """
        Exception raised when an unknown message type is received through the websocket
    """
    pass

class WebSocketServer(ControlServer):

    def __init__(self, **kwargs):
        super().__init__(**kwargs)

        self._websocket_server = None

        self._host = kwargs['host']
        self._port = kwargs['port']

        self._function_map = {
            'set-motor': self.forward_kinematics_handler,
            'set-led': self.motor_led_handler,
            'set-torque': self.torque_handler,
            'set-speed': self.speed_handler,
            'inverse-kinematics': self.inverse_kinematics_handler,
            'connected': self.manifest_connection
        }

        self._logger = logging.getLogger("Websocket server")
        self._logger.setLevel(logging.DEBUG)

    async def _server_wrapper(self):
        """
            Wrapper for the websocket server runner
        """
        async with serve(self._message_handler, self._host, self._port):
            await asyncio.Future()

    def start(self):
        asyncio.get_event_loop().run_until_complete(self._server_wrapper())

    def stop(self):
        self._websocket_server.shutdown()
    
    async def _message_handler(self, websocket):
        async for message in websocket:
            json_data = json.loads(message)

            if json_data['type'] in self._function_map:
                self._function_map[json_data['type']](json_data['data'])
            else:
                raise UnknownMessageTypeException("Invalid message type")

    def forward_kinematics_handler(self, args):
        return super().forward_kinematics_handler(args)
    
    def motor_led_handler(self, args):
        return super().motor_led_handler(args)
    
    def torque_handler(self, args):
        return super().torque_handler(args)
    
    def speed_handler(self, args):
        return super().speed_handler(args)
    
    def inverse_kinematics_handler(self, args) -> None:
        return super().inverse_kinematics_handler(args)