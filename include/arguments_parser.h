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

    class task {
    public:
        virtual ~task() = 0;

        virtual void run();
    };

    class file_task : public virtual task {
    protected:
        std::string filename;
    public:
        file_task(const std::string &filename);

        ~file_task() = 0;

        inline const std::string get_filename() {
            return filename;
        }
    };

    class input_task : public virtual task {
    public:
        ~input_task() = 0;

        virtual std::shared_ptr<maze> read() = 0;
    };

    class output_task : public virtual task {
    public:
        ~output_task() = 0;

        virtual void write(std::shared_ptr<maze>) = 0;
    };

    class arguments_parser {
        po::options_description desc;
        po::variables_map map;
    public:
        arguments_parser(int argc, char const *argv[]);

        std::vector<std::shared_ptr<task> > get_tasks();
    };

}

#endif
