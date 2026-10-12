#include "context.hpp"

engine::Context::Context() = default;
void engine::Context::Reload(const sf::View&, const sf::View&) { }
bool engine::Context::Poll(const std::optional<sf::Event>&, sf::RenderWindow& event, void* nextContext) { return false; }
void engine::Context::Physics() { }
void engine::Context::PhysicsUI() { }
void engine::Context::ResizeUI(const sf::View&) { }
void engine::Context::DrawContext(sf::RenderWindow&) { }
void engine::Context::DrawUIContext(sf::RenderWindow&) { }