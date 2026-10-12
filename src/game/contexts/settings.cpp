#include "contexts.hpp"
#include "../../utility/utility.hpp"

#include "SFML/System/Vector2.hpp"

using namespace game::contexts;

Settings::Settings(
    sf::RenderWindow& win,
    sf::Texture& screenshotTexture,
    Contexts& previousContext,
    engine::Settings& settings
    ) : engine::Context(),
    win(win),
    captureTexture(screenshotTexture),
    capture(captureTexture),
    transparency((sf::Vector2f)win.getSize()),
    previousContext(previousContext),
    configRef(settings)
    {
        this->transparency.setFillColor(sf::Color(0, 0, 0, 230));
        this->transparency.setPosition(sf::Vector2f(0.f, 0.f));
    }

void Settings::Reload(const sf::View& viewGame, const sf::View& viewUI) {
    (void)this->captureTexture.resize(win.getSize());
    this->captureTexture.update(win);
    this->capture.setPosition(sf::Vector2f(0.f, 0.f));
}

bool Settings::Poll(const std::optional<sf::Event>& event, sf::RenderWindow& win, void* nextContext) {
    // Return to previous context
    if (
        event->is<sf::Event::KeyPressed>() &&
        event->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::Escape
    ) {
        *((Contexts*)nextContext) = previousContext;
        return true;
    }
    // Check for click
    else if (
        event->is<sf::Event::MouseButtonReleased>() &&
        event->getIf<sf::Event::MouseButtonReleased>()->button == sf::Mouse::Button::Left
    ) {
        // Check for press on a config
        engine::Settings::Value* selectedValue = this->configRef.GetSelectedValue(win.mapPixelToCoords(sf::Mouse::getPosition(win), win.getView()));
        
        if (selectedValue != nullptr && selectedValue == this->configRef.GetToggledValueRef()) {
            // TODO: Figure out a modular way to determine if the fullscreen button has been triggered and perform an associated action
            selectedValue->ChangeValue();
            // Check for changes from the "->ChangeValue" trigger
            // Has fullscreen been toggled
            if (this->configRef.fullscreenEnabled != utility::_window::isWindowFullscreen) {
                utility::ReloadWindow(win, this->configRef.fullscreenEnabled);
                // TODO: This does not work, I think each context needs a ref to both View instances & pass the UI one in
                this->ResizeUI(win.getView());
            }
        }
        
        this->configRef.SetToggleValue(selectedValue);
        
        return false;
    }
    return false;
}

void Settings::Physics() { }

void Settings::PhysicsUI() {

}

void Settings::ResizeUI(const sf::View& viewUI) {
    utility::logic::ResizeSpriteToWin(this->capture, viewUI);
    this->transparency.setSize(viewUI.getSize());
}

void Settings::DrawContext(sf::RenderWindow& win) { }

void Settings::DrawUIContext(sf::RenderWindow& win) {
    win.draw(this->capture);
    win.draw(this->transparency);

    this->configRef.DrawBooleanValues(win);
}
