#ifndef ENGINE_H 
#define ENGINE_H
#include "../temp.h"
#include <unordered_map>
#include <vector>
#include <string>

class SensorFusionEngine {
private:
    std::unordered_map<std::string, std::vector<ReadData>> all_grouped_data;

public:
    SensorFusionEngine();
    void create_map(std::vector<ReadData> readdata);

    std::vector<ReadData> fusion(std::unordered_map<std::string, std::vector<ReadData>> data);
    std::unordered_map<std::string, std::vector<ReadData>> getMap();
};

#endif