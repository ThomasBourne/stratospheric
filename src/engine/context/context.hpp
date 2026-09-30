#ifndef ENGINE_CONTEXT_CONTEXT_HPP
#define ENGINE_CONTEXT_CONTEXT_HPP

// Global Imports
#include <SFML/Graphics.hpp>

namespace engine {
    class Context {
        // Public functions
    public:
        Context();
        virtual void Init();
        virtual void Reload();
        virtual void Poll();
        virtual void Physics();
        virtual void UIPhysics();
        virtual void DrawContext(sf::RenderWindow&);
        virtual void DrawUIContext();
    };
}


#endif