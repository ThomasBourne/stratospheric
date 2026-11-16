#include "context.hpp"

engine::Context::Context(sf::RenderWindow& win, sf::View& viewGame, const sf::View& viewUI) :
    winRef(win),
    viewGame(viewGame),
    viewUI(viewUI)
    { }
void engine::Context::Reload() { }
bool engine::Context::Poll(const std::optional<sf::Event>&, engine::Keybinds& keybinds, void* nextContext) { return false; }
void engine::Context::Physics(engine::Keybinds& keybinds) { }
void engine::Context::PhysicsUI() { }
void engine::Context::ResizeUI() { }
void engine::Context::DrawContext() { }
void engine::Context::DrawUIContext() { }