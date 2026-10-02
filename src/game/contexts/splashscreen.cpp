#include "contexts.hpp"
#include "../../utility/utility.hpp"

#include "SFML/System/Vector2.hpp"

using namespace game::contexts;

SplashScreen::SplashScreen(sf::Font& sharedFont, sf::Texture& splashTexture) : engine::Context(),
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

void SplashScreen::Reload(sf::View& viewGame, sf::View& viewUI) {
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

bool SplashScreen::Poll(const std::optional<sf::Event>& event, sf::RenderWindow& win, void* nextContext) {
    if (
        event->is<sf::Event::MouseButtonPressed>() &&
        event->getIf<sf::Event::MouseButtonPressed>()->button == sf::Mouse::Button::Left
    ) {
        for (size_t i = 0; i < this->actionButtons.size(); i++) {
            if (this->actionButtons[i].displayText.getGlobalBounds().contains(sf::Vector2f(win.mapPixelToCoords(sf::Mouse::getPosition(win), win.getView())))) {
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

void SplashScreen::ResizeUI(sf::View& viewUI) {
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

void SplashScreen::DrawContext(sf::RenderWindow& win) { }

void SplashScreen::DrawUIContext(sf::RenderWindow& win) {
    win.draw(this->splashImage);
    for (const auto& button : this->actionButtons) {
        win.draw(button.displayText);
    }
}
