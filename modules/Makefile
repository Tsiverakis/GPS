# compiler
CXX = g++
CXXFLAGS = -std=c++11 -Wall -I.

SRCS = main.cpp \
       temp.cpp \
       car/car.cpp \
       sensorfusionengine/engine.cpp \
       sensors/sensors.cpp \
       world/gridworld.cpp \
       objects/StaticObjects.cpp \
       objects/MovingObjects.cpp

OBJS = $(SRCS:.cpp=.o)

TARGET = self_driving_sim

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

