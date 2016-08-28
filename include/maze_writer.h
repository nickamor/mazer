//
// Created by Nicholas Amor on 13/8/16.
//

#ifndef MAZER_FILEWRITER_H
#define MAZER_FILEWRITER_H

#include "maze.h"

namespace mazer {

    /**
     * Serialises a maze to disk.
     */
    class MazeWriter {
        std::string filename;
    public:
        MazeWriter(const std::string &filename);

        /**
         * Write the given Maze to file.
         * @param maze
         */
        void Write(std::shared_ptr<Maze> maze);
    };

}

#endif //MAZER_FILEWRITER_H
