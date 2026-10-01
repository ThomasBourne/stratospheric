#include "contexts.hpp"
#include "../../utility/utility.hpp"

#include "SFML/System/Vector2.hpp"

using namespace game::contexts;

Settings::Settings(
    sf::RenderWindow& win,
    sf::Texture& screenshotTexture,
    Contexts& previousContext
    ) : engine::Context(),
    win(win),
    captureTexture(screenshotTexture),
    capture(captureTexture),
    transparency((sf::Vector2f)win.getSize()),
    previousContext(previousContext)
    {
        this->transparency.setFillColor(sf::Color(0, 0, 0, 230));
        this->transparency.setPosition(sf::Vector2f(0.f, 0.f));
    }

void Settings::Reload() {
    (void)this->captureTexture.resize(
        sf::Vector2u(
            (unsigned int)win.getView().getSize().x,
            (unsigned int)win.getView().getSize().y
        )
    );
    this->captureTexture.update(win);
    this->capture.setPosition(sf::Vector2f(0.f, 0.f));
}

bool Settings::Poll(const std::optional<sf::Event>& event, sf::RenderWindow& win, void* nextContext) {
    if (
        event->is<sf::Event::KeyPressed>() &&
        event->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::Escape
    ) {
        *((Contexts*)nextContext) = previousContext;
        return true;
    }
    return false;
}

void Settings::Physics() { }

void Settings::PhysicsUI() {

}

void Settings::ResizeUI(sf::View& viewUI) {

}

void Settings::DrawContext(sf::RenderWindow& win) { }

void Settings::DrawUIContext(sf::RenderWindow& win) {
    win.draw(this->capture);
    win.draw(this->transparency);
}
