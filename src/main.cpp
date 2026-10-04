// Global Imports
#include <SFML/Graphics.hpp> // SFML sf:: typing
#include <map>

// Utility variables
#include "utility/utility.hpp" // util:: variables

// Engine Classes
#include "engine/context/context.hpp" // Window context framework for typing
#include "engine/settings/settings.hpp" // Settings file object manager
#include "engine/render_utility/fpsdisplay.hpp" // FPS display object

// Game Classes
#include "game/contexts/contexts.hpp" // Window context classes

// Namespace simplifications
namespace g = game;
namespace e = engine;
namespace util = utility;

// Types
typedef std::map<g::Contexts, e::Context*> ContextList_t;

// Context knowledge
g::Contexts previousContext{ g::Contexts::Terminate };
g::Contexts selectedContext{ g::Contexts::SplashScreen };
g::Contexts nextContext{ selectedContext };

void ChangeCurrentContext(
	ContextList_t& contexts,
	sf::View& viewGame,
	sf::View& viewUI
) {
	previousContext = selectedContext;
	// TODO: Add Context::Unload() function
	// contexts[*currentContext]->Unload();
	if (nextContext == g::Contexts::Terminate) {
		exit(0);
	}
	selectedContext = nextContext;
	contexts[selectedContext]->Reload(viewGame, viewUI);
}

int main() {
	// Load all fonts
	sf::Font defaultFont{ ASSET_FILE(util::assets::defaultFont) };

	// Load settings config
	engine::Settings settings{ defaultFont };
	const util::StratErrorCodes settingsSuccess = settings.LoadFromFile(ASSET_FILE(util::settings::settingsFile));
	if (settingsSuccess != util::StratErrorCodes::OK) {
		exit((int)settingsSuccess);
	}

	// Initialise Render components
	sf::RenderWindow window( sf::VideoMode( util::defaultWindowSize ), util::windowName );
	window.setFramerateLimit(util::stepRate);

	// Load all textures
	sf::Texture screenshotTexture{ window.getSize() };
	sf::Texture splashScreenTexture{ ASSET_FILE(util::assets::splashScreen) };
	sf::Texture tilemapTexture{ ASSET_FILE(util::assets::tilemap) };

	// Initialise Contexts
	g::contexts::SplashScreen contextSplashScreen{ defaultFont, splashScreenTexture };
	g::contexts::Game contextGame{ tilemapTexture };
	g::contexts::Settings contextSettings{ window, screenshotTexture, previousContext, settings };

	// Map Contexts
	ContextList_t contexts {
		std::make_pair(g::Contexts::SplashScreen, &contextSplashScreen),
		std::make_pair(g::Contexts::Game, &contextGame),
		std::make_pair(g::Contexts::Settings, &contextSettings),
	};

	// Create views
	sf::View viewGame{ window.getView() };
	sf::View viewUI{ sf::FloatRect({ 0.f, 0.f }, (sf::Vector2f)util::defaultWindowSize) };

	// Create FPS tracking object
	engine::FPSCounter fpsCounter{ defaultFont };

	// TODO: Find a nice way to remove this and go straight to reload below
	contexts[selectedContext]->Reload(viewGame, viewUI);

	// Step loop
	while (window.isOpen()) {
		if (selectedContext != nextContext) {
			ChangeCurrentContext(contexts, viewGame, viewUI);
		}

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
				event->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::G
			) {
				nextContext = selectedContext == g::Contexts::SplashScreen ?
					g::Contexts::Game :
					g::Contexts::SplashScreen;
				ChangeCurrentContext(contexts, viewGame, viewUI);
			}
			// Let current context handle poll
			(void)contexts[selectedContext]->Poll(event, window, &nextContext);
		}

		// Perform physic steps
		window.setView(viewGame);
		contexts[selectedContext]->Physics();
		viewGame = window.getView();
		window.setView(viewUI);
		contexts[selectedContext]->PhysicsUI();

		// Update FPS step (if requested)
		if (settings.fpsEnabled)
			fpsCounter.UpdateFPSStep();

		// Rasterise current context
		window.clear();
		window.setView(viewGame);
		contexts[selectedContext]->DrawContext(window);
		viewGame = window.getView();
		window.setView(viewUI);
		contexts[selectedContext]->DrawUIContext(window);
		if (settings.fpsEnabled)
			fpsCounter.DrawFPS(window);
		window.display();
	}
}
