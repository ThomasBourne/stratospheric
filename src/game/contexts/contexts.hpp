#ifndef GAME_CONTEXTS_CONTEXTS_HPP
#define GAME_CONTEXTS_CONTEXTS_HPP

// Global Imports
#include <vector>

// Local Imports
#include "../../engine/context/context.hpp"
#include "../../engine/settings/settings.hpp"

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
            SplashScreen(sf::Font&, sf::Texture&);
            void Reload(sf::View&, sf::View&);
            bool Poll(const std::optional<sf::Event>&, sf::RenderWindow&, void*);
            void Physics();
            void PhysicsUI();
            void ResizeUI(sf::View&);
            void DrawContext(sf::RenderWindow&);
            void DrawUIContext(sf::RenderWindow&);

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
            Game(sf::Texture&);
            void Reload(sf::View&, sf::View&);
            bool Poll(const std::optional<sf::Event>&, sf::RenderWindow&, void*);
            void Physics();
            void PhysicsUI();
            void ResizeUI(sf::View&);
            void DrawContext(sf::RenderWindow&);
            void DrawUIContext(sf::RenderWindow&);

            // Private members
        private:
            sf::Sprite tileExample;
        };

        class Settings : public engine::Context {
            // Public functions
        public:
            Settings(sf::RenderWindow&, sf::Texture&, Contexts&, engine::Settings&);
            void Reload(sf::View&, sf::View&);
            bool Poll(const std::optional<sf::Event>&, sf::RenderWindow&, void*);
            void Physics();
            void PhysicsUI();
            void ResizeUI(sf::View&);
            void DrawContext(sf::RenderWindow&);
            void DrawUIContext(sf::RenderWindow&);

            // Private members
        private:
            sf::RenderWindow& win;
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