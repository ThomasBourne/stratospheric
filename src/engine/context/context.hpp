#ifndef ENGINE_CONTEXT_CONTEXT_HPP
#define ENGINE_CONTEXT_CONTEXT_HPP

// Global Imports
#include <SFML/Graphics.hpp>

namespace engine {
    class Context {
        // Public functions
    public:
        Context();
        virtual void Reload(sf::View&, sf::View&);
        virtual bool Poll(const std::optional<sf::Event>&, sf::RenderWindow&, void*);
        virtual void Physics();
        virtual void PhysicsUI();
        virtual void ResizeUI(sf::View&);
        virtual void DrawContext(sf::RenderWindow&);
        virtual void DrawUIContext(sf::RenderWindow&);
    };
}


#endif