from server.OSCServer import OSCServer
from server.WebSocketServer import WebSocketServer
from robot_control.SerialControl import SerialControl
from robot_control.DummyRobotControl import DummyRobotControl
import argparse

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
    parser.add_argument('--serial-port', type=str, help='Serial port to connect to')
    parser.add_argument('-p', '--platform', type=str, help='Platform to connect to', required=True)

    args = parser.parse_args()
    robot_control = None
    server = None

    if args.dummy:
        robot_control = DummyRobotControl()
    else:
        robot_control = SerialControl(
            port=args.serial_port if args.serial_port else "/dev/ttyACM0",
            baudrate=115200,
            verbose=args.verbose
        )

    if args.platform in ['processing', 'puredata']:
        server = OSCServer(
            robot_control=robot_control,
        )
    elif args.platform in ['p5']:
        server = WebSocketServer(
            robot_control=robot_control,
        )

    server.start()

    while True:
        if input() == "q":
            break

    server.stop()
else:
    raise Exception("This script should be run as main")