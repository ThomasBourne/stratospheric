#ifndef ENGINE_ENTITY_ENTITY_HPP
#define ENGINE_ENTITY_ENTITY_HPP

#include <SFML/Graphics.hpp>

namespace engine {
    class Entity {
        // Public Members
    public:

        // Public Functions
    public:
        typedef std::vector<std::pair<size_t, size_t>> AnimationSet;
        Entity(sf::Texture&, sf::Vector2f, AnimationSet);
        virtual void RunPhysics(/*Tilemap&, void**/);
        void UpdateAnimation(size_t, bool);
        void SetPosition(const sf::Vector2f);
        const sf::Vector2f GetPosition();
        const sf::Vector2f GetSize();
        // TODO: See if a friend function is what we want here
        void Draw(sf::RenderWindow&);

        // Protected Members
    protected:
        sf::Texture& texture;
        sf::Sprite shape;
        sf::Vector2f size;

        // Animation
        size_t framesSinceLastAnimationFrame;
        size_t textureIndex;
        std::vector<std::pair<size_t, size_t>> animationSets;
        size_t currentAnimationSet;
    };
}

#endif