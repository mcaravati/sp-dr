from onshape_to_robot import simulation
import pybullet
import math
import time
import model

ergo_simulation = simulation.Simulation('ergo_jr/ergo_jr.urdf', fixed=True, panels=True)
sliders = {}
target = pybullet.loadURDF('frame/robot.urdf')

def reset_base_position_with_matrix(target, matrix):
    t, q = ergo_simulation.matrixToPose(matrix)
    pybullet.resetBasePositionAndOrientation(target, t, q)

joints = ergo_simulation.getJoints()
for joint in joints:
    sliders[joint] = pybullet.addUserDebugParameter(joint, -math.pi, math.pi, 0.)

last_line = time.time()
last_inverse = 0
targets = {'m' + str(k + 1): 0 for k in range(6)}

while True:
    if ergo_simulation.t > 1.:
        joints = ergo_simulation.getJoints()
        for joint in joints:
            targets[joint] = pybullet.readUserDebugParameter(sliders[joint])

        matrix = model.direct(list(targets.values()))
        reset_base_position_with_matrix(target, matrix)

        ergo_simulation.resetJoints(targets)

    ergo_simulation.tick()