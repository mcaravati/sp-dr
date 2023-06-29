from OSCServer import OSCServer
from SerialControl import SerialControl

if __name__ == "__main__":
    server = OSCServer(
        robot_control=SerialControl(
            port="/dev/ttyACM0",
            baudrate=115200,
            verbose=True
        ),
    )
    server.start()

    while True:
        if input() == "q":
            break

    server.stop()