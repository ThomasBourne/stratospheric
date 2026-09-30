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
	// Initialise Contexts
	g::contexts::SplashScreen contextSplashScreen{ };
	g::contexts::Game contextGame{ };

	// Map Contexts
	ContextList_t contexts {
		std::make_pair(g::Contexts::SplashScreen, &contextSplashScreen),
		std::make_pair(g::Contexts::Game, &contextGame),
	};

	// Initialise Render components
	sf::RenderWindow window( sf::VideoMode( util::windowSize ), util::windowName );
	
	for (auto& c : contexts) {
		c.second->Init();
	}

	g::Contexts selectedContext{ g::SplashScreen };
	contexts[selectedContext]->Reload();

	// Step loop
	while ( window.isOpen() )
	{
		while ( const std::optional event = window.pollEvent() )
		{
			if ( event->is<sf::Event::Closed>() )
				window.close();
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

		window.clear();
		contexts[selectedContext]->DrawContext(window);
		window.display();
	}
}
