#include "engine.h"

extern double minConfidenceThreshold;
using namespace std;

// constructor
SensorFusionEngine::SensorFusionEngine() {};

void SensorFusionEngine::create_map(vector<ReadData> readdata)
{
    all_grouped_data.clear();
    for (ReadData d : readdata)
    {
        all_grouped_data[d.objectid].push_back(d);
    }
}

vector<ReadData> SensorFusionEngine::fusion(std::unordered_map<std::string, std::vector<ReadData>> data)
{
    vector<ReadData> temp;
    for (auto &d : data)
    {
        vector<ReadData> tempd = d.second;
        string objid = d.first, obj;
        ReadData final;
        double conf_sum = 0.0, speed_sum = 0.0, dis_sum = 0.0, speed_conf_sum = 0;
        final.objectid = objid;
        final.type = tempd[0].type;
        final.p = tempd[0].p;
        if (final.type == "MovingObject")
        {
            final.signtext = "N/A";
            final.trafficlightp = "N/A";
            final.direction = "N/A";
        }
        else
        {
            final.speed = -1;
            final.direction = "N/A";
        }
        for (ReadData rd : tempd)
        {
            dis_sum += rd.confidence * rd.distance;
            conf_sum += rd.confidence;
            if (rd.type == "MovingObject" && rd.speed >= 0)
            {
                speed_conf_sum += rd.confidence;
                speed_sum += rd.speed * rd.confidence;
            }

            if (rd.type == "StaticObject" && rd.signtext != "N/A")
            {
                final.signtext = rd.signtext;
            }

            if (rd.type == "MovingObject" && rd.direction != "N/A")
            {
                final.direction = rd.direction;
            }

            if (rd.type == "StaticObject" && rd.trafficlightp != "N/A")
            {
                final.trafficlightp = rd.trafficlightp;
            }
        }

        if (speed_conf_sum != 0)
        {

            final.speed = speed_sum / speed_conf_sum;
        }
        else
        {
            final.speed = 0;
        }
        if (conf_sum != 0)
        {

            final.distance = dis_sum / conf_sum;
        }
        else
        {
            final.distance = 0;
        }
        if (tempd.size() != 0)
        {

            final.confidence = conf_sum / tempd.size();
        }
        else
        {
            final.confidence = 0;
        }
        size_t index = final.objectid.find(':');
        if (index != string::npos)
        {
            obj = final.objectid.substr(0, index);
        }
        else
        {
            obj = final.objectid;
        }

        if (final.confidence >= minConfidenceThreshold || obj == "BIKE")
        {
            temp.push_back(final);
        }
    }
    return temp;
}

unordered_map<std::string, vector<ReadData>> SensorFusionEngine:: getMap(){
        return all_grouped_data;
}
