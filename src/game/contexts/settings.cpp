#include "contexts.hpp"
#include "../../utility/utility.hpp"

#include "SFML/System/Vector2.hpp"

using namespace game::contexts;

Settings::Settings(
    THE_BIG_THREE_WITH_TEXT,
    sf::Texture& screenshotTexture,
    Contexts& previousContext,
    engine::Settings& settings
    ) :
    engine::Context(winRef, viewGame, viewUI),
    captureTexture(screenshotTexture),
    capture(captureTexture),
    transparency((sf::Vector2f)winRef.getSize()),
    previousContext(previousContext),
    configRef(settings)
    {
        this->transparency.setFillColor(sf::Color(0, 0, 0, 230));
        this->transparency.setPosition(sf::Vector2f(0.f, 0.f));
    }

void Settings::Reload() {
    (void)this->captureTexture.resize(winRef.getSize());
    this->captureTexture.update(winRef);
    this->capture.setPosition(sf::Vector2f(0.f, 0.f));
}

bool Settings::Poll(const std::optional<sf::Event>& event,void* nextContext) {
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
        engine::Settings::Value* selectedValue = this->configRef.GetSelectedValue(winRef.mapPixelToCoords(sf::Mouse::getPosition(winRef), winRef.getView()));
        
        if (selectedValue != nullptr && selectedValue == this->configRef.GetToggledValueRef()) {
            // TODO: Figure out a modular way to determine if the fullscreen button has been triggered and perform an associated action
            selectedValue->ChangeValue();
            // Check for changes from the "->ChangeValue" trigger
            // Has fullscreen been toggled
            if (this->configRef.fullscreenEnabled != utility::_window::isWindowFullscreen) {
                utility::ReloadWindow(winRef, this->configRef.fullscreenEnabled);
                this->ResizeUI();
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

void Settings::ResizeUI() {
    // TODO: This does not work when fullscreen is toggled
    utility::logic::ResizeSpriteToWin(this->capture, viewUI);
    this->transparency.setSize(viewUI.getSize());
}

void Settings::DrawContext() { }

void Settings::DrawUIContext() {
    winRef.draw(this->capture);
    winRef.draw(this->transparency);

    this->configRef.DrawBooleanValues(winRef);
}
