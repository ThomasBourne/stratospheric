#include "contexts.hpp"

#include "SFML/System/Vector2.hpp"

#include "../../utility/utility.hpp"

using namespace game::contexts;

Game::Game(sf::Texture& tilemap) : engine::Context(),
    tileExample(tilemap)
    { }

void Game::Reload(sf::View& viewGame, sf::View& viewUI) {
    tileExample.setPosition(sf::Vector2f(800.f, 200.f));
    tileExample.setTextureRect({{0, 0}, {utility::tilemapDefinition, utility::tilemapDefinition}});
}

bool Game::Poll(const std::optional<sf::Event>& event, sf::RenderWindow& win, void* nextContext) {
    return false;
}

void Game::Physics() {

}

void Game::PhysicsUI() {

}

void Game::ResizeUI(sf::View&) {

}

void Game::DrawContext(sf::RenderWindow& win) {
    win.draw(this->tileExample);
}

void Game::DrawUIContext(sf::RenderWindow& win) {

}
