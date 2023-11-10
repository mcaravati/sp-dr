from server.OSCServer import OSCServer
from server.WebSocketServer import WebSocketServer
from robot_control.SerialControl import SerialControl
from robot_control.DummyRobotControl import DummyRobotControl
import argparse
import logging

if __name__ == "__main__":
    parser = argparse.ArgumentParser(
        prog='SP//dr Server',
        description='Start the linking server between platforms and the robot',
        epilog='This script is distributed as free software and comes with no warranty'
    )

    parser.add_argument(
        '--dummy',
        action='store_true',
        help='Use a dummy robot control instead of a serial connection'
    )
    parser.add_argument('-v', '--verbose', action='store_true', help='Verbose output')
    parser.add_argument('-p', '--protocol', type=str, help='Protocol to use of the server/client communication', required=True)
    parser.add_argument('--serial-port', type=str, help='Serial port to connect to', default="/dev/ttyACM0")
    parser.add_argument('--baudrate', type=int, help='The baudrate to use for the serial connection', default=115200)
    parser.add_argument('--host', type=str, help="The address on which the server should bind", default='127.0.0.1')
    parser.add_argument('--port', type=str, help="The port on which the server should listen", default=9000)
    parser.add_argument('--nb-motors', type=int, help="The number of motors to control", default=6)

    args = parser.parse_args()
    robot_control = None
    server = None

    logging.basicConfig(format='[%(name)s]\t[%(levelname).1s] %(message)s')
    logger = logging.getLogger('Main thread')
    logger.setLevel(logging.DEBUG)

    if args.dummy:
        robot_control = DummyRobotControl()
    else:
        robot_control = SerialControl(
            port=args.serial_port,
            baudrate=args.baudrate,
            verbose=args.verbose,
            nb_motors=args.nb_motors
        )

    if args.protocol == 'osc':
        server = OSCServer(
            robot_control=robot_control,
            host=args.host,
            port=args.port,
            verbose=args.verbose
        )
    elif args.protocol == 'websockets':
        server = WebSocketServer(
            robot_control=robot_control,
            host=args.host,
            port=args.port,
            verbose=args.verbose
        )

    try:
        logger.info(f"Server running on {args.host}:{args.port}")
        logger.info("Enter 'q' or press Ctrl+C to exit")
        server.start()

        while True:
            if input() == "q":
                break

    except KeyboardInterrupt:
        pass
    finally:
        server.stop()
else:
    raise Exception("This script should be run as main")