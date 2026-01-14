# Hysteresis
Implementation and analysis of hysteresis modeling for dynamic systems, focusing on nonlinear behavior and memory effects in physical processes.

HYSTERESIS-BASED THERMAL CONTROL SYSTEM

This repository contains an experimental thermal control system based on hysteresis, designed for laboratory practices and educational purposes.
The system combines Arduino for real-time control and data acquisition with Processing for visualization, user interaction, and data logging.

SYSTEM OVERVIEW

The project implements a hysteresis controller to regulate the temperature of a thermal cell using a Peltier device.
The control strategy is simple, robust, and well suited for experimental analysis of nonlinear control behavior.

The overall data and control flow is:

Arduino <-> Serial communication <-> Processing

Arduino:

Reads temperature sensors (ambient and cell/surface temperature)

Executes the hysteresis control logic

Controls actuators (Peltier module and fan via relays)

Sends real-time data through the serial port

Processing:

Provides the graphical user interface (GUI)

Sends control parameters to Arduino

Displays real-time temperature evolution

Logs experimental data

Allows execution and monitoring of hysteresis tests

REPOSITORY STRUCTURE

repository
arduino
Arduino source code for control and data acquisition
processing
Processing sketch for GUI, visualization and logging
README.md
LICENSE
.gitignore

HYSTERESIS CONTROL EXPERIMENTS

All hysteresis experiments are performed from the Processing interface.

From the GUI, the user can:

Set the temperature setpoint

Define the hysteresis bands:

Delta T1 (upper hysteresis)

Delta T2 (lower hysteresis)

Start and stop experimental tests

Enable or disable the cooling fan

Visualize:

Ambient temperature

Cell/surface temperature

Setpoint and hysteresis limits

Save:

Experimental data to text files

Graphical results as image files

The Arduino executes the hysteresis logic locally, while Processing acts as a supervisory and visualization layer.

SERIAL COMMUNICATION

Communication between Arduino and Processing is performed through a serial interface.

Arduino continuously sends:

Ambient temperature

Cell temperature

Peltier state (ON/OFF)

Fan state (ON/OFF)

Processing sends commands to Arduino to:

Configure setpoint and hysteresis parameters

Start a new experimental test

Manually control the fan

This bidirectional communication enables real-time interaction and monitoring.

PROCESSING REQUIREMENTS

To run the Processing interface correctly, the following requirement must be met:

Two logo image files must be placed in the same folder as the Processing sketch.

These image files are used by the graphical interface and must remain in the Processing directory.
If the image files are missing, the interface may not display correctly.

INTENDED USE

This project is intended for:

Laboratory practices

Control engineering education

Experimental analysis of hysteresis-based control

Validation of thermal control strategies

The structure and implementation provide a clear and extensible framework that can later be expanded toward more advanced control techniques such as PID, FOPID, or adaptive control.
