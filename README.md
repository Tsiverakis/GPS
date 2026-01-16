# GPS

# Self-Driving Car Simulation

## Project Overview

This project is a C++ simulation of an autonomous vehicle navigating a 2D grid environment[cite: 1]. The simulation integrates multiple OOP concepts to model the interaction between an ego car, static obstacles (traffic lights, signs), and moving entities (other cars, bikes).

## System Architecture

### 1. The GridWorld

The environment is managed by the `GridWorld` class, which acts as a container for all `WorldObject` pointers.

- **Coordinate System**: Uses a 2D grid where (0,0) is typically the bottom-left or top-left depending on visualization.
- **Updates**: The world handles the lifecycle of traffic lights (switching between RED, YELLOW, GREEN) and triggers the movement of non-ego vehicles.

### 2. Perception (Sensors)

The `SelfDrivingCar` perceives its surroundings through a suite of virtual sensors defined in `sensors.cpp`:

- **Lidar**: Provides a 360-degree scan in a $9 \times 9$ area (radius 4). It is primary for detecting object positions.
- **Radar**: A long-range directional sensor (12 units) that detects the speed and heading of moving objects.
- **Camera**: A front-facing sensor (7 units) that identifies semantic data like traffic light colors and sign text.

### 3. Sensor Fusion Engine

The `SensorFusionEngine` processes raw data from all sensors to create a unified world model:

- **Data Grouping**: Readings are grouped by object ID.
- **Weighted Fusion**: It calculates the final distance and speed using a weighted average based on the confidence level of each sensor.
- **Safety Filter**: It ignores objects with confidence below `minConfidenceThreshold` (default 0.40), but prioritizes **BIKE** objects for maximum safety.

### 4. Decision Making & Movement

The car's logic in `car.cpp` follows a hierarchical approach:

- **Navigation**: Calculates a path towards the GPS target based on coordinate differences.
- **Traffic Compliance**: Decelerates when a RED or YELLOW light is detected within 3 units.
- **Obstacle Avoidance**: Modifies direction if an object is detected directly in the path of movement.

---

## Makefile Explained

The provided `Makefile` automates the compilation process:

- **Compiler Settings**: Uses `g++` with the `C++11` standard and `-Wall` for error checking.
- **Dependency Management**:
  - **`SRCS`**: Defines all source files across different modules (world, car, objects).
  - **`OBJS`**: Automatically generates object file names from the source list.
- **Rules**:
  - `all`: Builds the final executable `self_driving_sim`.
  - `clean`: Removes binary and object files to allow for a fresh build.

---

## How to Run

1. **Compile the project**:
   ```bash
   make
   ```
2. **Example run format**:
   ```bash
   ./self_driving_sim --dimX 25 --dimY 25 --numMovingCars 8 --numTrafficLights 4 --numParkedCars 6 --numStopSigns 3 --gps 20 20
   ```

## Developers

| Ονοματεπώνυμο                | Αριθμός μητρώου |
| :--------------------------- | :-------------- |
| Τσιβεράκης Αντώνιος          | 1115202400299   |
| Μουσουρης Χαραλαμπος-Ραφαη΄λ | 1115202400130   |

## Specifications

[![View PDF](https://img.shields.io/badge/View-PDF-red?style=for-the-badge&logo=adobe-acrobat-reader)](./docs/Specifications.pdf)
