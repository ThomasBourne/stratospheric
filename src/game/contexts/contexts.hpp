#ifndef GAME_CONTEXTS_CONTEXTS_HPP
#define GAME_CONTEXTS_CONTEXTS_HPP

// Global Imports
#include <vector>

// Local Imports
#include "../../engine/context/context.hpp"
#include "../../engine/settings/settings.hpp"

#define THE_BIG_THREE sf::RenderWindow&, const sf::View&, const sf::View&
#define THE_BIG_THREE_WITH_TEXT sf::RenderWindow& winRef, const sf::View& viewGame, const sf::View& viewUI

namespace game {
    enum class Contexts {
        SplashScreen = 0,
        Game,
        Settings,
        Terminate
    };

    namespace contexts {
        class SplashScreen : public engine::Context {
            // Public functions
        public:
            SplashScreen(THE_BIG_THREE, sf::Font&, sf::Texture&);
            void Reload();
            bool Poll(const std::optional<sf::Event>&, void*);
            void Physics();
            void PhysicsUI();
            void ResizeUI();
            void DrawContext();
            void DrawUIContext();

            // Private classes
        private:
            struct Button {
                sf::Text displayText;
                Contexts action;
                Button(sf::Text t, Contexts c) : displayText(t), action(c) { }
            };
            
            // Private members
        private:
            sf::Sprite splashImage;
            sf::Font& sharedFont;
            std::vector<SplashScreen::Button> actionButtons;
        };

        class Game : public engine::Context {
            // Public functions
        public:
            Game(THE_BIG_THREE, sf::Texture&);
            void Reload();
            bool Poll(const std::optional<sf::Event>&, void*);
            void Physics();
            void PhysicsUI();
            void ResizeUI();
            void DrawContext();
            void DrawUIContext();

            // Private members
        private:
            sf::Sprite tileExample;
        };

        class Settings : public engine::Context {
            // Public functions
        public:
            Settings(THE_BIG_THREE,  sf::Texture&, Contexts&, engine::Settings&);
            void Reload();
            bool Poll(const std::optional<sf::Event>&, void*);
            void Physics();
            void PhysicsUI();
            void ResizeUI();
            void DrawContext();
            void DrawUIContext();

            // Private members
        private:
            Contexts& previousContext;
            engine::Settings& configRef;
            // Background freeze frame
            sf::Texture& captureTexture;
            sf::Sprite capture;
            sf::RectangleShape transparency;
        };
    }
}

#endif