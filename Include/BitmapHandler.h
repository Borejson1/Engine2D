#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <memory>

class BitmapHandler {
public:
    static std::shared_ptr<sf::Image> loadFromFile(const std::string& filename) {
        auto image = std::make_shared<sf::Image>();
        if (image->loadFromFile(filename)) {
            return image;
        }
        return nullptr;
    }

    static bool saveToFile(const sf::Image& image, const std::string& filename) {
        return image.saveToFile(filename);
    }

    static void copy(sf::Image& dest, const sf::Image& source, unsigned int destX, unsigned int destY, const sf::IntRect& sourceRect = sf::IntRect(0, 0, 0, 0)) {
        dest.copy(source, destX, destY, sourceRect);
    }

};