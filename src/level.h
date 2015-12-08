#ifndef __LEVEL_H__
#define __LEVEL_H__

#include <glm/glm.hpp>
#include <vector>

typedef struct Level {
    // in px/s
    float ballInitialSpeed = 300.0f;
    float paddleSize = 200.0f;
    std::vector<glm::vec2> brickPositions;
    Level(float b_speed, float p_size) : ballInitialSpeed(b_speed),
        paddleSize(p_size) {}
} Level;

const Level readLevelDataFromDisk(std::string fname);
const Level getLevel(int num);
#endif
