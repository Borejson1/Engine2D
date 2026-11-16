#pragma once
#include "GameObject.h"
#include <vector>
#include <memory>

class AnimatedObject : public virtual GameObject {
public:
    virtual void animate() = 0;
};

class BitmapObject : public DrawableObject, public TransformableObject {
protected:
    std::vector<sf::Sprite> sprites;
    std::vector<std::shared_ptr<sf::Texture>> textures;

public:
    void addBitmap(std::shared_ptr<sf::Texture> texture) {
        textures.push_back(texture);
        sprites.emplace_back(*texture);
    }

    void addSpriteFrame(std::shared_ptr<sf::Texture> texture, const sf::IntRect& frameRect) {
        textures.push_back(texture);
        sf::Sprite sprite(*texture);
        sprite.setTextureRect(frameRect);
        sprites.push_back(sprite);
    }

    virtual void draw(sf::RenderTarget& target) override {
        for (const auto& sprite : sprites) {
            target.draw(sprite);
        }
    }
};

class SpriteObject : public BitmapObject, public AnimatedObject {
protected:
    int currentSpriteIndex = 0;
    float animationTimer = 0.0f;
    float framesPerSecond = 10.0f;
};