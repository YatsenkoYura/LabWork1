CXX = g++
CXXFLAGS = -Werror -Wpedantic -Wall -pthread
DOXYFILE = Doxyfile

TARGET = lab1
SRCS = main.cpp ImageData.cpp ImageOperations.cpp

OBJS = $(SRCS:.cpp=.o)

all: $(TARGET)

.PHONY: all clean

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)
clean-docs:
	rm -rf docs
docs:
	doxygen $(DOXYFILE)

