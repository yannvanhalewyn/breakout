#ifndef __TEXTURE_MANAGER_H__
#define __TEXTURE_MANAGER_H__

#include <SFML/graphics.hpp>

class TextureManager
{
public:
    static sf::Texture* get(const std::string& filename);

private:
    static std::map<std::string, sf::Texture*> m_texture_cache;

    static sf::Texture* load(const std::string& filename);
};

#endif
