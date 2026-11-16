# F.I.R.E. --- Flexion Induced Rehabilitation Enhancer

F.I.R.E. (Flexion Induced Rehabilitation Enhancer) is a low-cost,
lightweight rehabilitation glove concept designed to assist finger
flexion and extension in people with limited hand movement, including
semi-paralyzed patients. The project explores shape memory alloy (SMA)
actuation, flex-sensor feedback, and an embedded control system to
support controlled finger movement during daily exercises and supervised
physiotherapy.

## Project Overview

Weakness, spasticity, and contractures can restrict basic finger
movements and make everyday activities---such as eating, dressing, and
personal hygiene---more difficult. Conventional rehabilitation equipment
can be bulky and expensive.

F.I.R.E. aims to provide a compact, wearable alternative that can assist
finger opening and closing while measuring finger bend. The prototype
focuses on a single finger rather than full-hand rehabilitation.

## Key Objectives

-   Develop a lightweight and portable rehabilitation glove.
-   Assist controlled finger flexion and extension using SMA actuators.
-   Measure finger bending using a flex sensor.
-   Use sensor feedback to control actuator operation through a
    microcontroller.
-   Explore a more affordable and wearable alternative to bulky
    rehabilitation equipment.

## System Architecture

The system follows a feedback-based control pipeline:

1.  The flex sensor measures the finger's bending angle.
2.  The sensor signal is read by an Arduino microcontroller.
3.  The controller compares the measured bend with a reference or
    threshold.
4.  Based on the control decision, the corresponding MOSFET switches the
    SMA actuator circuit.
5.  Joule heating causes the SMA actuator to contract and assist finger
    movement.
6.  The flex sensor measures the resulting movement and feeds it back to
    the controller.

The actuator arrangement is intended to support both flexion and
extension through opposing actuation paths.

## Hardware Components

  -----------------------------------------------------------------------
  Component                           Purpose
  ----------------------------------- -----------------------------------
  Arduino Uno                         Reads the flex sensor and executes
                                      the control logic

  Flex sensor                         Measures finger bending and
                                      provides feedback

  SMA actuators / springs             Generate the force used to assist
                                      finger movement

  N-channel MOSFETs                   Switch the higher-current SMA
                                      actuator circuits

  Buck converter / voltage regulator  Steps the supply voltage down to 5
                                      V for the Arduino

  Power source                        Supplies the electrical energy
                                      required by the controller and SMA
                                      actuators

  Glove base and mechanical           Provide the wearable structure for
  attachments                         mounting the system
  -----------------------------------------------------------------------

The design also includes mechanical elements such as finger-joint
attachments, SMA wire holders, and a wrist joint.

## Working Principle

The prototype uses the electrical resistance heating of shape memory
alloy (SMA) elements to produce actuation. When current passes through
an SMA element, Joule heating raises its temperature and causes it to
contract. This contraction is used to assist finger movement.

A flex sensor continuously provides information about the finger's bend.
The Arduino uses this feedback to decide which actuator path should be
enabled.

The control concept includes:

-   Reading an initial flex-sensor value as a baseline.
-   Measuring the current sensor value during operation.
-   Calculating the deviation from the baseline.
-   Comparing the deviation with a bend threshold.
-   Switching the appropriate SMA actuator through a MOSFET.
-   Introducing a cooling interval after actuation to account for the
    relatively slow cooling response of SMA.

The project presentation describes a threshold-based control approach
rather than proportional or continuous closed-loop control.

## SMA Characterisation

SMA actuator behaviour was experimentally characterised by examining the
relationship between current, response time, speed, and power. The
recorded trends indicate that increasing current reduces the time
required for actuation, while the electrical and thermal limits of the
SMA and power supply constrain operation.

These characterisation tests informed the actuator and power
considerations for the prototype.

## Prototype and Mechanical Design

The wearable assembly was developed around a glove base, with mechanical
attachments for the finger joints, SMA elements, and wrist. The
prototype integrates the flex sensor, actuator elements, switching
circuit, microcontroller, and power supply.

The demonstrated prototype focuses on assisting movement of a single
finger. It is an experimental rehabilitation aid concept and is not a
clinically validated medical device.

## Challenges Encountered

-   **SMA cooling time:** Slow cooling limits the speed and
    repeatability of repeated flexion-extension cycles.
-   **Asymmetric actuation:** Differences between bending and relaxation
    behaviour make reliable motion control difficult.
-   **Electrical noise and grounding:** High-current actuator switching
    can interfere with stable sensor readings.
-   **Power and wiring constraints:** Jumper-wire heating and the need
    for reliable current paths complicate the circuit.
-   **Packaging:** Integrating the actuator wiring and electronics into
    a compact, comfortable wearable form is challenging.

## Current Limitations

-   A single flex sensor and a single-finger, three-SMA setup limit
    sensing and actuation to a small part of the hand.
-   SMA cooling delays, heating limits, and the prototype's 3 A supply
    constraint limit speed, repeatability, and continuous operation.
-   The current control strategy is threshold-based and does not
    implement proportional or continuous closed-loop control.
-   High current can cause wiring to heat up and create grounding
    instability; the prototype required temporary wiring workarounds.

## Future Scope

Potential improvements include:

1.  **Wireless monitoring:** Add ESP32-based connectivity and real-time
    data logging for remote monitoring.
2.  **Improved power management:** Introduce safer and more efficient
    power management, adaptive calibration, and current/thermal
    feedback.
3.  **Expanded actuation:** Develop multi-joint SMA actuation to support
    more complete finger movement.
4.  **Improved integration:** Design a compact PCB and refine the
    mechanical packaging to improve reliability and wearability.

## Repository Contents

Add the project files to this repository as they become available.
Suggested organisation:

``` text
FIRE/
├── README.md
├── firmware/
│   └── <Arduino source files>
├── electronics/
│   └── <circuit diagrams and design files>
└── mechanical/
    └── <CAD files and mechanical drawings>
```

The folder structure above is a suggested organisation; it does not
imply that these files are included in this repository yet.

## Team

Developed at **Indian Institute of Technology Indore**, under the
guidance of **Prof. IA Palani**.

-   Manthripragada Viswajith
-   Muhamed Nihal
-   Nambiar Anand S
-   Pranshu Devlia
-   R. Gopikrishnan
-   Nikunj Bheda
-   Arpit Kumar Singh

## Safety Notice

This project is an academic prototype intended for experimentation and
development. It is not a certified medical device and should not be used
as a substitute for professional medical advice, diagnosis, or
supervised rehabilitation. SMA elements can become hot, and the actuator
circuit can draw high current. Test the electronics and actuators with
appropriate current limiting, insulation, thermal precautions, and
supervision. Do not wear or test the prototype on a person unless it has
been reviewed for electrical, thermal, and mechanical safety by
qualified supervisors.

## Acknowledgement

We thank **Prof. IA Palani** and the **Indian Institute of Technology
Indore** for their guidance and support during the project.
