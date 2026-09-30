#include <SFML/Graphics.hpp>
#include "utility/utility.hpp"

namespace e = engine;
namespace util = engine::utility;

int main()
{
	sf::RenderWindow window( sf::VideoMode( util::windowSize ), util::windowName );
	sf::CircleShape shape( 100.f );
	shape.setFillColor( sf::Color::Green );

	while ( window.isOpen() )
	{
		while ( const std::optional event = window.pollEvent() )
		{
			if ( event->is<sf::Event::Closed>() )
				window.close();
		}

		window.clear();
		window.draw( shape );
		window.display();
	}
}
