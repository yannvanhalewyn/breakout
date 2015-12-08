#ifndef __GLM_HELPERS_H__
#define __GLM_HELPERS_H__

std::string vec2ToString(glm::vec2 v) {
    char buff[100];
    snprintf(buff, sizeof(buff), "{%f, %f}", v.x, v.y);
    return std::string(buff);
}

#endif
