CXX = g++
CXXFLAGS = -Werror -Wpedantic -Wall -pthread
DOXYFILE = Doxyfile

TARGET = lab1
SRCS = main.cpp include/ImageData.cpp include/ImageOperations.cpp

TEST_TARGET:= gtest
TEST_SRCS  := tests/test.cpp
TEST_OBJS  := $(TEST_SRCS:.cpp=.o)
GTEST_LIBS := -lgtest -lgtest_main

OBJS = $(SRCS:.cpp=.o)

all: $(TARGET)

.PHONY: all clean

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(TEST_TARGET): $(TEST_OBJS) include/ImageData.o include/ImageOperations.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(GTEST_LIBS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET) $(TEST_TARGET) $(TEST_OBJS)
clean-docs:
	rm -rf docs
docs:
	doxygen $(DOXYFILE)

