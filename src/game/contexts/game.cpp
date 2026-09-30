#include "contexts.hpp"

#include "SFML/System/Vector2.hpp"

using namespace game::contexts;

Game::Game() : engine::Context()
    { }

void Game::Init() {
    this->testShape.setSize(sf::Vector2f(100.f, 100.f));
    this->testShape.setFillColor(sf::Color::Blue);
}

void Game::Reload() {
    testShape.setPosition(sf::Vector2f(800.f, 200.f));
}

void Game::Poll() {

}

void Game::Physics() {

}

void Game::UIPhysics() {

}

void Game::DrawContext(sf::RenderWindow& win) {
    win.draw(this->testShape);
}

void Game::DrawUIContext() {

}
