CXXFLAGS = -std=c++14 -Wall -Wextra -pedantic
LDFLAGS  = -g

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
