#include "contexts.hpp"
#include "../../utility/utility.hpp"

#include "SFML/System/Vector2.hpp"

using namespace game::contexts;

SplashScreen::SplashScreen(THE_BIG_THREE_WITH_TEXT, sf::Font& sharedFont, sf::Texture& splashTexture) :
    engine::Context(winRef, viewGame, viewUI),
    sharedFont(sharedFont),
    splashImage(splashTexture)
    {
        this->actionButtons = {
            SplashScreen::Button(sf::Text(this->sharedFont, "Continue"), Contexts::Game),
            SplashScreen::Button(sf::Text(this->sharedFont, "New Game"), Contexts::Game),
            SplashScreen::Button(sf::Text(this->sharedFont, "Settings"), Contexts::Settings),
            SplashScreen::Button(sf::Text(this->sharedFont, "Exit"), Contexts::Terminate),
        };
    }

void SplashScreen::Reload() {
    this->splashImage.setPosition({0.f, 0.f});
    utility::logic::ResizeSpriteToWin(this->splashImage, viewUI);

    for (int i = 0; i < this->actionButtons.size(); i++) {
        this->actionButtons[i].displayText.setPosition(
            {
                (70 * this->splashImage.getScale().x) - this->actionButtons[i].displayText.getGlobalBounds().size.x / 2,
                ((30 * this->splashImage.getScale().y) * i) + (60 * this->splashImage.getScale().y)
            }
        );
    }
}

bool SplashScreen::Poll(const std::optional<sf::Event>& event, void* nextContext) {
    if (
        event->is<sf::Event::MouseButtonReleased>() &&
        event->getIf<sf::Event::MouseButtonReleased>()->button == sf::Mouse::Button::Left
    ) {
        for (size_t i = 0; i < this->actionButtons.size(); i++) {
            if (this->actionButtons[i].displayText.getGlobalBounds().contains(sf::Vector2f(winRef.mapPixelToCoords(sf::Mouse::getPosition(winRef), winRef.getView())))) {
                *((Contexts*)nextContext) = this->actionButtons[i].action;
                return true;
            }
        }
        return true;
    }
    return false;
}

void SplashScreen::Physics() { }

void SplashScreen::PhysicsUI() {

}

void SplashScreen::ResizeUI() {
    utility::logic::ResizeSpriteToWin(this->splashImage, viewUI);

    for (size_t i = 0; i < this->actionButtons.size(); i++) {
        this->actionButtons[i].displayText.setPosition(
            {
                (70 * this->splashImage.getScale().x) - this->actionButtons[i].displayText.getGlobalBounds().size.x / 2,
                ((30 * this->splashImage.getScale().y) * i) + (60 * this->splashImage.getScale().y)
            }
        );
    }
}

void SplashScreen::DrawContext() { }

void SplashScreen::DrawUIContext() {
    winRef.draw(this->splashImage);
    for (const auto& button : this->actionButtons) {
        winRef.draw(button.displayText);
    }
}
