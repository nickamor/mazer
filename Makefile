CXXFLAGS := -std=c++14 -Wall -pedantic -Ilibmazer/include -Imazer/include
LDFLAGS := -g -lboost_program_options

SOURCES := libmazer/src/maze.cc \
			libmazer/src/maze_builder.cc \
			libmazer/src/maze_generator.cc \
			libmazer/src/maze_reader.cc \
			libmazer/src/maze_svg_writer.cc \
			libmazer/src/maze_writer.cc \
			libmazer/src/strong_random.cc \
			libmazer/src/generators/aldousbroder_generator.cc \
			libmazer/src/generators/eller_generator.cc \
			mazer/src/arguments_parser.cc \
			mazer/src/main.cc

OBJECTS := $(patsubst %.cc,%.o,$(SOURCES))

TARGET := mazer_app

.PHONY: clean

$(TARGET): $(OBJECTS)
	$(CXX) $(LDFLAGS) $^ -o $@

clean:
	$(RM) $(TARGET) $(OBJECTS)
