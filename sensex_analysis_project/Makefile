# Makefile for Sensex Analysis Project

CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++11

TARGET = sensex_analysis_project
SRCS = main.cpp analysis.cpp data_reader.cpp
OBJS = $(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)
