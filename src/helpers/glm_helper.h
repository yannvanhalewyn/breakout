#ifndef __GLM_HELPERS_H__
#define __GLM_HELPERS_H__


glm::vec2 sfVectToGlm(sf::Vector2f v) {
    return glm::vec2(v.x, v.y);
}

std::string vec2ToString(glm::vec2 v) {
    char buff[100];
    snprintf(buff, sizeof(buff), "{%f, %f}", v.x, v.y);
    return std::string(buff);
}

// Check if a float rect is within another based on width
bool isWithinWidth(sf::FloatRect child, sf::FloatRect parent) {
    return
        child.left > parent.left &&
        child.left + child.width < parent.left + parent.width;
}

// Check if a float rect is within another based on width
bool isWithinHeight(sf::FloatRect child, sf::FloatRect parent) {
    return
        child.top > parent.top &&
        child.top + child.height < parent.top + parent.height;
}


#endif
