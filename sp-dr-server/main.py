from server.OSCServer import OSCServer
from server.WebSocketServer import WebSocketServer
from robot_control.SerialControl import SerialControl
from robot_control.DummyRobotControl import DummyRobotControl

if __name__ == "__main__":
    robot_control = DummyRobotControl()
    # robot_control = SerialControl(
    #         port="/dev/ttyACM1",
    #         baudrate=115200,
    #         verbose=True
    #     )


    server = WebSocketServer(
        robot_control=robot_control,
    )
    # server = OSCServer(
    #     robot_control=robot_control,
    # )
    server.start()

    while True:
        if input() == "q":
            break

    server.stop()