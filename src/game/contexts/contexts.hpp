#ifndef GAME_CONTEXTS_CONTEXTS_HPP
#define GAME_CONTEXTS_CONTEXTS_HPP

// Local Imports
#include "../../engine/context/context.hpp"

namespace game {
    enum Contexts {
        SplashScreen = 0,
        count
    };

    namespace contexts {
        class SplashScreen : public engine::Context {
            // Public functions
        public:
            SplashScreen();
            void Init();
            void Reload();
            void Poll();
            void Physics();
            void UIPhysics();
            void DrawContext(sf::RenderWindow&);
            void DrawUIContext();

            // Private members
        private:
            sf::RectangleShape testShape;
        };
    }
}

#endif