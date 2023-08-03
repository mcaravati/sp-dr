from setuptools import find_packages, setup

setup(
    name="ergojunior",
    packages=find_packages(include=['ergojunior']),
    version="0.1.0",
    description="Basic OSC controller for the Poppy Ergo Jr. 6-DOF robot",
    author="Matteo Caravati",
    install_requires=[
        "osc4py3"
    ]
)