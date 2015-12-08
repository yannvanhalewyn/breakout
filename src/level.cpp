#include "level.h"
#include "path.h"
#include <iostream>
#include <fstream>

#define BRICK_CHAR 'x'
#define SPACE_CHAR '.'

const Level readLevelDataFromDisk(std::string fname) {
    Level lvl(0, 0);

    // Open filestream
    std::ifstream file(Path::resourcePath(fname));
    if (file.fail()) {
        std::cerr << "Could not open file: " << fname << std::endl;
        // TODO (null pattern?)
        return lvl;
    }

    std::string tmp;
    file >> tmp >> lvl.ballInitialSpeed;
    file >> tmp >> lvl.paddleSize;

    // Read in brick data
    char c;
    glm::vec2 pos(0, 0);
    while(file.get(c)) {
        switch (c) {
            case BRICK_CHAR:
                lvl.brickPositions.emplace_back(pos);
            case SPACE_CHAR:
                pos.x++;
                break;
            case '\n':
                pos.x = 0;
                pos.y++;
        }
    }

    return lvl;
}

const Level getLevel(int num) {
    char buff[100];
    snprintf(buff, sizeof(buff), "levels/level%d.txt", num);
    return readLevelDataFromDisk({buff});
}
