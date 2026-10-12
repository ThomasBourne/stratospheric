#include "contexts.hpp"

#include "SFML/System/Vector2.hpp"

#include "../../utility/utility.hpp"

using namespace game::contexts;

Game::Game(THE_BIG_THREE_WITH_TEXT, sf::Texture& tilemap, sf::Texture& entityTexture) :
    engine::Context(winRef, viewGame, viewUI),
    tileExample(tilemap),
    entity(entityTexture, sf::Vector2f(50.f, 30.f), {std::make_pair<size_t, size_t>(0, 0),std::make_pair<size_t, size_t>(1, 2)})
    { }

void Game::Reload() {
    tileExample.setPosition(sf::Vector2f(800.f, 200.f));
    tileExample.setTextureRect({{0, 0}, {utility::tilemapDefinition, utility::tilemapDefinition}});
}

bool Game::Poll(const std::optional<sf::Event>& event, void* nextContext) {
    return false;
}

void Game::Physics() {
    // TODO: Current implementation will enable sideways movement to be quicker than L-R & U-D
    // Must take in vec2f of magnitude (0-1, 0-1) then perform calculation with stepWeight to determine where on the circle the 2 points are 
    constexpr float stepWeight{ 1.25f };
    const sf::Vector2f cardinality {
        stepWeight * sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::D) +
        -stepWeight * sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::A),
        stepWeight * sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::S) +
        -stepWeight * sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::W)
    };
    
    tileExample.move(cardinality);

    entity.RunPhysics();
}

void Game::PhysicsUI() {

}

void Game::ResizeUI() {

}

void Game::DrawContext() {
    winRef.draw(this->tileExample);
    entity.Draw(winRef);
}

void Game::DrawUIContext() {

}
