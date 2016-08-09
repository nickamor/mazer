CXXFLAGS = -std=c++14 -Wall -Wextra -pedantic
LDFLAGS  = -lboost_program_options -g

TARGET = mazer
OBJECTS = mazer.o FileReader.o

.PHONY: all clean

all: mazer

clean:
	$(RM) $(TARGET) $(OBJECTS)

$(TARGET): $(OBJECTS)
	$(CXX) -o $@ $^ $(LDFLAGS)

%.o: %.cpp %.h
	$(CXX) -c -o $@ $< $(CXXFLAGS)

# test all, test : build and run all tests
# test X : build and run specific test
test:
	$(CXX) -o FileReader.test -D __TEST__ FileReader.cpp
	./FileReader.test
