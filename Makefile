CXXFLAGS = -std=c++14 -Wall -Wextra -pedantic -I/usr/local/include
LDFLAGS  = -lboost_program_options -g -L/usr/local/lib

TARGET = mazer
OBJECTS = mazer.o ArgHandler.o FileReader.o FileWriter.o VectorWriter.o
TEST_TARGETS = ArgHandler.test FileReader.test  

.PHONY: all clean test

all: mazer

clean:
	$(RM) $(TARGET) $(OBJECTS) $(TEST_TARGETS)

$(TARGET): $(OBJECTS)
	$(CXX) -o $@ $^ $(LDFLAGS)

%.o: %.cpp %.h
	$(CXX) -c -o $@ $< $(CXXFLAGS)

# test all, test : build and run all tests
# test X : build and run specific test
test: $(TEST_TARGETS)

%.test: %.cpp
	$(CXX) $(LDFLAGS) FileReader.o -o $@ $(CXXFLAGS) -D __TEST__ $^
