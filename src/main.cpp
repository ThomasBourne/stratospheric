// Global Imports
#include <SFML/Graphics.hpp> // SFML sf:: typing
#include <map>

// Utility variables
#include "utility/utility.hpp" // util:: variables

// Engine Classes
#include "engine/context/context.hpp" // Window context framework

// Game Classes
#include "game/contexts/contexts.hpp" // Window context classes


// Namespace simplifications
namespace g = game;
namespace e = engine;
namespace util = utility;

// Types
typedef std::map<g::Contexts, e::Context*> ContextList_t;

void ChangeCurrentContext(
	ContextList_t& contexts,
	g::Contexts* currentContext,
	g::Contexts newContext
) {
	// TODO: add unload/close functionality to contexts
	*currentContext = newContext;
	contexts[*currentContext]->Reload();
}

int main() {
	// Load all textures
	sf::Texture splashScreenTexture{ ASSET_FILE(util::assets::splashScreen) };
	// sf::Texture tilemapTexture{};

	// Initialise Contexts
	g::contexts::SplashScreen contextSplashScreen{ splashScreenTexture };
	g::contexts::Game contextGame{ };

	// Map Contexts
	ContextList_t contexts {
		std::make_pair(g::Contexts::SplashScreen, &contextSplashScreen),
		std::make_pair(g::Contexts::Game, &contextGame),
	};

	// Initialise Render components
	sf::RenderWindow window( sf::VideoMode( util::windowSize ), util::windowName );
	window.setFramerateLimit(util::stepRate);

	sf::View viewGame{ window.getView() };
	sf::View viewUI{ sf::FloatRect({ 0.f, 0.f }, (sf::Vector2f)util::windowSize) };
	
	for (auto& c : contexts) {
		c.second->Init();
	}

	g::Contexts selectedContext{ g::SplashScreen };
	contexts[selectedContext]->Reload();

	// Step loop
	while (window.isOpen()) {
		// System polls
		while (const std::optional event = window.pollEvent()) {
			// Exit application
			if ( event->is<sf::Event::Closed>() )
				window.close();
			else if (event->is<sf::Event::Resized>()) {
				// Resize views
				viewGame.setSize((sf::Vector2f)window.getSize());
				viewUI.setSize((sf::Vector2f)window.getSize());
				// Recentre ui view (game view should remain unchanged)
				viewUI.setCenter(
					sf::Vector2f(
						(float)viewUI.getSize().x / 2,
						(float)viewUI.getSize().y / 2
					)
				);
				// While this resizes correctly, it does not move items calculated at 1920x1080 to new padding
				// Call custom resize function for context to fix this issue
				contexts[selectedContext]->ResizeUI(viewUI);
			}
			// Custom Function
			else if (
				event->is<sf::Event::KeyPressed>() &&
				event->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::G)
				ChangeCurrentContext(
					contexts,
					&selectedContext,
					selectedContext == g::Contexts::SplashScreen ?
						g::Contexts::Game :
						g::Contexts::SplashScreen
				);
		}

		// Perform physic steps
		window.setView(viewGame);
		contexts[selectedContext]->Physics();
		viewGame = window.getView();
		window.setView(viewUI);
		contexts[selectedContext]->PhysicsUI();

		window.clear();
		window.setView(viewGame);
		contexts[selectedContext]->DrawContext(window);
		viewGame = window.getView();
		window.setView(viewUI);
		contexts[selectedContext]->DrawUIContext(window);
		window.display();
	}
}
