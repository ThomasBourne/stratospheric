#ifndef GAME_CONTEXTS_CONTEXTS_HPP
#define GAME_CONTEXTS_CONTEXTS_HPP

// Local Imports
#include "../../engine/context/context.hpp"

namespace game {
    enum Contexts {
        SplashScreen = 0,
        Game,
        count,
    };

    namespace contexts {
        class SplashScreen : public engine::Context {
            // Public functions
        public:
            SplashScreen(sf::Texture&);
            void Init();
            void Reload();
            void Poll();
            void Physics();
            void PhysicsUI();
            void ResizeUI(sf::View&);
            void DrawContext(sf::RenderWindow&);
            void DrawUIContext(sf::RenderWindow&);

            // Private members
        private:
            sf::Sprite splashImage;
        };

        class Game : public engine::Context {
            // Public functions
        public:
            Game();
            void Init();
            void Reload();
            void Poll();
            void Physics();
            void PhysicsUI();
            void ResizeUI(sf::View&);
            void DrawContext(sf::RenderWindow&);
            void DrawUIContext(sf::RenderWindow&);

            // Private members
        private:
            sf::RectangleShape testShape;
        };
    }
}

#endif