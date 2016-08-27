## mazer - C++ maze generator
## Nick Amor 2016

# Compiler options
CXXFLAGS := -std=c++14 -Wall -Wextra -Wfatal-errors -pedantic -I/usr/local/include -Iinclude
LDFLAGS  := -lboost_program_options -g -L/usr/local/lib 

# Directories
SRCDIR := src
INCLUDEDIR := include
BUILDDIR := build
TESTDIR := tests

# Output files
TARGET := mazer
SOURCES := $(wildcard $(SRCDIR)/*.cpp)
OBJECTS := $(patsubst $(SRCDIR)/%.cpp,$(BUILDDIR)/%.o,$(SOURCES))
TEST_TARGETS := $(patsubst $(SRCDIR)/%.cpp,$(TESTDIR)/%,$(SOURCES))

.PHONY: all clean test

all: $(BUILDDIR) $(TARGET) test

clean:
	$(RM) -rf $(TARGET) $(BUILDDIR) $(TESTDIR)

$(TARGET): $(OBJECTS)
	$(CXX) $(LDFLAGS) -o $@ $^

$(BUILDDIR) $(TESTDIR):
	mkdir $@

$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) -c -o $@ $< $(CXXFLAGS)

# test : build and run all tests
# tests/% : build and run specific test
test: $(TESTDIR) $(TEST_TARGETS)

tests/%: $(SRCDIR)/%.cpp
	$(CXX) $(LDFLAGS) -o $@ $(CXXFLAGS) -D __TEST__ $<
