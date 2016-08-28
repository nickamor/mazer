//
// Created by Nicholas Amor on 12/8/16.
//

#ifndef __ARGUMENTS_PARSER_H__
#define __ARGUMENTS_PARSER_H__

#include <memory>
#include <vector>
#include <boost/program_options.hpp>
#include "maze.h"

namespace po = boost::program_options;

namespace mazer {

    /**
     * A task to perform.
     */
    class Task {
    public:
        virtual ~Task() = 0;

        virtual void run();
    };

    class FileTask : public virtual Task {
    protected:
        std::string filename;
    public:
        FileTask(const std::string &filename);

        ~FileTask() = 0;

        inline const std::string get_filename() {
            return filename;
        }
    };

    class InputTask : public virtual Task {
    public:
        ~InputTask() = 0;

        virtual std::shared_ptr<Maze> read() = 0;
    };

    class OutputTask : public virtual Task {
    public:
        ~OutputTask() = 0;

        virtual void write(std::shared_ptr<Maze>) = 0;
    };

    /**
     * Parses program arguments into a set of actions to perform.
     */
    class ArgumentsParser {
        int argc;
        const char **argv;
    public:
        ArgumentsParser(int argc, char const *argv[]);

        std::vector<std::shared_ptr<Task> > get_tasks();
    };

}

#endif
