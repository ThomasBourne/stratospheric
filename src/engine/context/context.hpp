#ifndef ENGINE_CONTEXT_CONTEXT_HPP
#define ENGINE_CONTEXT_CONTEXT_HPP

// Global Imports
#include <SFML/Graphics.hpp>

// Local Imports
#include "../settings/keybinds.hpp"

namespace engine {
    class Context {
        // Public functions
    public:
        Context(sf::RenderWindow&, sf::View&, const sf::View&); // TODO: 1st view should not be const for game context bus assess later
        virtual void Reload();
        virtual bool Poll(const std::optional<sf::Event>&, engine::Keybinds&, void*);
        virtual void Physics(engine::Keybinds&);
        virtual void PhysicsUI();
        virtual void ResizeUI();
        virtual void DrawContext();
        virtual void DrawUIContext();

        // Private members
    protected:
        sf::RenderWindow& winRef;
        sf::View& viewGame;
        const sf::View& viewUI;
    };
}


#endif