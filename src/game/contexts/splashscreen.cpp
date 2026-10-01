#include "contexts.hpp"
#include "../../utility/utility.hpp"

#include "SFML/System/Vector2.hpp"

using namespace game::contexts;

SplashScreen::SplashScreen(sf::Texture& splashTexture) : engine::Context(),
    splashImage(splashTexture)
    { }

void SplashScreen::Init() { }

void SplashScreen::Reload() {
    this->splashImage.setPosition({0.f, 0.f});;
    this->splashImage.setScale({1, 1});
    this->splashImage.setScale(
        sf::Vector2f(
            utility::windowSize.x / this->splashImage.getGlobalBounds().size.x,
            utility::windowSize.y / this->splashImage.getGlobalBounds().size.y
        )
    );
}

void SplashScreen::Poll() {

}

void SplashScreen::Physics() { }

void SplashScreen::PhysicsUI() {

}

void SplashScreen::ResizeUI(sf::View& viewUI) {
    this->splashImage.setScale(sf::Vector2f(1.f, 1.f));
    this->splashImage.setScale(
        sf::Vector2f(
            viewUI.getSize().x / this->splashImage.getGlobalBounds().size.x,
            viewUI.getSize().y / this->splashImage.getGlobalBounds().size.y
        )
    );
    // for (size_t i = 0; i < items.buttons.size(); i++) {
    //     items.buttons[i].setPosition(
    //         sf::Vector2f(
    //             (70 * items.backgroundImage.getScale().x) - items.buttons[i].getGlobalBounds().size.x / 2,
    //             ((30 * items.backgroundImage.getScale().y) * i) + (60 * items.backgroundImage.getScale().y)
    //         )
    //     );
    // }
}

void SplashScreen::DrawContext(sf::RenderWindow& win) { }

void SplashScreen::DrawUIContext(sf::RenderWindow& win) {
    win.draw(this->splashImage);

}
