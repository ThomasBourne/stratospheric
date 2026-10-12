#include "contexts.hpp"

#include "SFML/System/Vector2.hpp"

#include "../../utility/utility.hpp"

using namespace game::contexts;

Game::Game(THE_BIG_THREE_WITH_TEXT, sf::Texture& tilemap) :
    engine::Context(winRef, viewGame, viewUI),
    tileExample(tilemap)
    { }

void Game::Reload() {
    tileExample.setPosition(sf::Vector2f(800.f, 200.f));
    tileExample.setTextureRect({{0, 0}, {utility::tilemapDefinition, utility::tilemapDefinition}});
}

bool Game::Poll(const std::optional<sf::Event>& event, void* nextContext) {
    return false;
}

void Game::Physics() {

}

void Game::PhysicsUI() {

}

void Game::ResizeUI() {

}

void Game::DrawContext() {
    winRef.draw(this->tileExample);
}

void Game::DrawUIContext() {

}
