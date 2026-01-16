# compiler
CXX = g++
CXXFLAGS = -std=c++11 -Wall -I.

SRCS = main.cpp \
       modules/temp.cpp \
       modules/car/car.cpp \
       modules/car/sensorfusionengine/engine.cpp \
       modules/car/sensors/sensors.cpp \
       modules/world/gridworld.cpp \
       modules/objects/StaticObjects.cpp \
       modules/objects/MovingObjects.cpp

OBJS = $(SRCS:.cpp=.o)

TARGET = self_driving_sim

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

