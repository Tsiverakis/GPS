#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <cstdlib>

// Include module headers
#include "world/gridworld.h"
#include "car/car.h"
#include "objects/StaticObjects.h"
#include "objects/MovingObjects.h"
#include "temp.h"

using namespace std;

// Δήλωση της global μεταβλητής για τα όρια
int max_value = 40; 

void printHelp() {
    cout << " Self-Driving Car Simulation " << endl;
    cout << "Usage : " << endl;
    cout << " --seed <num> Random seed (default: current time)" << endl;
    cout << " --dimX <num> World width (default: 40)" << endl;
    cout << " --dimY <num> World height (default: 40)" << endl;
    cout << " --numMovingCars <num> Number of moving cars (default: 3)" << endl;
    cout << " --numMovingBikes <num> Number of moving bikes (default: 4)" << endl;
    cout << " --numParkedCars <num> Number of parked cars (default: 5)" << endl;
    cout << " --numStopSigns <num> Number of stop signs (default: 2)" << endl;
    cout << " --numTrafficLights <num> Number of traffic lights (default: 2)" << endl;
    cout << " --simulationTicks <num> Maximum simulation ticks (default: 100)" << endl;
    cout << " --minConfidenceThreshold <num> Minimum confidence cutoff (default: 40)" << endl;
    cout << " --gps [x1 y1 x2 y2 ...] GPS target coordinates (required)" << endl;
    cout << " --help Show this help message " << endl << endl;
    cout << "Example usage : " << endl;
    cout << " ./oopproj_2025 --seed 12 --dimY 50 --gps 10 20 32 15 " << endl;
}

int main(int argc, char* argv[]) {
    int seed = time(0);
    int dimX = 40, dimY = 40;
    int numMovingCars = 3, numMovingBikes = 4, numParkedCars = 5;
    int numStopSigns = 2, numTrafficLights = 2;
    int simulationTicks = 100;
    double minConfidenceThreshold = 0.40;
    vector<Position> gpsTargets;

    if (argc == 1) { printHelp(); return 0; }

    for (int i = 1; i < argc; ++i) {
        string arg = argv[i];
        if (arg == "--help") { printHelp(); return 0; }
        else if (arg == "--seed" && i + 1 < argc) seed = stoi(argv[++i]);
        else if (arg == "--dimX" && i + 1 < argc) dimX = stoi(argv[++i]);
        else if (arg == "--dimY" && i + 1 < argc) dimY = stoi(argv[++i]);
        else if (arg == "--numMovingCars" && i + 1 < argc) numMovingCars = stoi(argv[++i]);
        else if (arg == "--numMovingBikes" && i + 1 < argc) numMovingBikes = stoi(argv[++i]);
        else if (arg == "--numParkedCars" && i + 1 < argc) numParkedCars = stoi(argv[++i]);
        else if (arg == "--numStopSigns" && i + 1 < argc) numStopSigns = stoi(argv[++i]);
        else if (arg == "--numTrafficLights" && i + 1 < argc) numTrafficLights = stoi(argv[++i]);
        else if (arg == "--simulationTicks" && i + 1 < argc) simulationTicks = stoi(argv[++i]);
        else if (arg == "--minConfidenceThreshold" && i + 1 < argc) minConfidenceThreshold = stod(argv[++i]) / 100.0;
        else if (arg == "--gps") {
            int j = i + 1;
            while (j < argc && argv[j][0] != '-') {
                int tx = stoi(argv[j++]);
                int ty = stoi(argv[j++]);
                gpsTargets.push_back(Position(tx, ty));
            }
            i = j - 1;
        }
    }

    if (gpsTargets.empty()) {
        cout << "Error: At least one GPS target is required." << endl;
        return 1;
    }

    srand(seed);
    max_value = dimX; 
    GridWorld world(dimX);
    
    SelfDrivingCar* egoCar = new SelfDrivingCar(Position(0,0), gpsTargets[0]);
    world.addObject(egoCar);
    
    cout << "[SYSTEM] Initializing world objects..." << endl;

    for (int i = 0; i < numMovingCars; i++) 
        world.addObject(new MovingCar(Position(rand() % dimX, rand() % dimY), "C" + to_string(i), 1, "UP"));

    for (int i = 0; i < numMovingBikes; i++) 
        world.addObject(new Bike(Position(rand() % dimX, rand() % dimY), "B" + to_string(i), 1, "RIGHT"));

    for (int i = 0; i < numParkedCars; i++) 
        world.addObject(new StationaryVehicle(rand() % dimX, rand() % dimY, "P" + to_string(i), "S"));

    for (int i = 0; i < numTrafficLights; i++) 
        world.addObject(new TrafficLight(rand() % dimX, rand() % dimY, "RED", "TL" + to_string(i), "L"));

    for (int i = 0; i < numStopSigns; i++) 
        world.addObject(new TrafficSign(rand() % dimX, rand() % dimY, "STOP", "SS" + to_string(i), "S"));

    cout << "[SYSTEM] Min Confidence Threshold: " << minConfidenceThreshold << endl;

    // ΠΛΗΡΗΣ ΟΠΤΙΚΟΠΟΙΗΣΗ ΣΤΗΝ ΑΡΧΗ
    world.visualization_full();

    for (int tick = 0; tick < simulationTicks; ++tick) {
        cout << "\n>>> Tick " << tick << " <<<" << endl;

        world.update();

        vector<ReadData> detections = egoCar->collectSensorData(world.getGrid());
        egoCar->makeDecision(detections);
        
        if (egoCar->executeMovement()) break; // Αν φτάσει στον στόχο επιστρέφει true

        Position newPos = egoCar->getPosition();
        if (newPos.getX() >= dimX || newPos.getY() >= dimY || newPos.getX() < 0 || newPos.getY() < 0) {
            cout << "[-] CAR: EGO Out of bounds! Terminating." << endl;
            break;
        }

        // ΜΕΡΙΚΗ ΟΠΤΙΚΟΠΟΙΗΣΗ ΣΕ ΚΑΘΕ ΒΗΜΑ
        world.visualization_pov(egoCar, 4, "centered"); 
    }

    // ΠΛΗΡΗΣ ΟΠΤΙΚΟΠΟΙΗΣΗ ΣΤΟ ΤΕΛΟΣ
    world.visualization_full();

    cout << "Simulation finished." << endl;
    return 0;
}