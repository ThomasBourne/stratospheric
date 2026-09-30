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

int main() {
	// Initialise Contexts
	g::contexts::SplashScreen contextSplashScreen{ };

	// Map Contexts
	std::map<g::Contexts, e::Context*> contexts {
		std::make_pair(g::Contexts::SplashScreen, &contextSplashScreen),
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
		}

		window.clear();
		contexts[selectedContext]->DrawContext(window);
		window.display();
	}
}
