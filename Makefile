CXXFLAGS = -std=c++14 -Wall -Wextra -pedantic -I/usr/local/include -Iinclude
LDFLAGS  = -lboost_program_options -g -L/usr/local/lib 

TARGET = mazer
SOURCES = $(wildcard src/*.cpp)
OBJECTS = $(patsubst src/%.cpp,build/%.o,$(SOURCES))
TEST_TARGETS = $(patsubst src/%.cpp,tests/%,$(SOURCES))

.PHONY: all clean test

all: $(TARGET)

clean:
	$(RM) $(TARGET) $(OBJECTS) $(TEST_TARGETS)

$(TARGET): $(OBJECTS)
	$(CXX) $(LDFLAGS) -o $@ $^

build/%.o: src/%.cpp include/%.h
	$(CXX) -c -o $@ $< $(CXXFLAGS)

# test all, test : build and run all tests
# test X : build and run specific test
test: $(TEST_TARGETS)

tests/%: src/%.cpp include/%.h
	$(CXX) $(LDFLAGS) -o $@ $(CXXFLAGS) -D __TEST__ $<

echo:
	@echo $(patsubst src/%.cpp,build/%.o,$(SOURCES))