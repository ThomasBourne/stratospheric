#include "context.hpp"

engine::Context::Context() = default;
void engine::Context::Init() { }
void engine::Context::Reload() { }
void engine::Context::Poll() { }
void engine::Context::Physics() { }
void engine::Context::PhysicsUI() { }
void engine::Context::ResizeUI(sf::View&) { }
void engine::Context::DrawContext(sf::RenderWindow&) { }
void engine::Context::DrawUIContext(sf::RenderWindow&) { }