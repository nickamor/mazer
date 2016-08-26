//
// Created by Nicholas Amor on 12/8/16.
//

#ifndef __FILEREADER_H__
#define __FILEREADER_H__

#include <string>
#include <iostream>
#include <memory>
#include "maze.h"

namespace mazer {

    class reader {
    private:
        std::string filename;
    public:
        reader(const std::string &filename);

        std::shared_ptr<maze> read();

        friend std::ostream &operator<<(std::ostream &, const reader &);
    };

}

#endif
