#include "texture_manager.h"
#include <iostream>

sf::Texture* TextureManager::get(const std::string& filename) {
    // If texture had already been loaded, return it:
    if (m_texture_cache[filename]) {
        return m_texture_cache[filename];


    // Else attempt to load it and store it in cache.
    } else {
        sf::Texture* texture;
        try {
            texture = load(filename);
        } catch(std::string s) {
            std::cerr << "Error: " << s << std::endl;
            return nullptr;
        }
        m_texture_cache[filename] = texture;
        return texture;
    }
}

sf::Texture* TextureManager::load(const std::string& filename) {
    std::cout << "loading texture " << filename << std::endl;
    sf::Texture* t = new sf::Texture;
    if (!t->loadFromFile(filename)) {
        throw "Could not load " + filename + ".";
    }
    return t;
}

std::map<std::string, sf::Texture*> TextureManager::m_texture_cache;
