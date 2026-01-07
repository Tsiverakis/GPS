#ifndef ENGINE
#define ENGINE
#include "temp.h"
#include <unordered_map>
#include <vector>

class SensorFusionEngine
{
private:
    std::unordered_map<std::string, std::vector<ReadData>> all_grouped_data;

public:
    // constructor
    SensorFusionEngine();

    // converts a vector into a map
    void create_map(std::vector<ReadData> readdata);

    std::vector<ReadData> fusion(std::unordered_map<std::string, std::vector<ReadData>> data);

    std::unordered_map<std::string, std::vector<ReadData>> getMap();
};

#endif