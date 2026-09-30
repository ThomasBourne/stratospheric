#include "contexts.hpp"

#include "SFML/System/Vector2.hpp"

using namespace game::contexts;

SplashScreen::SplashScreen() : engine::Context()
    { }

void SplashScreen::Init() {
    this->testShape.setSize(sf::Vector2f(50.f, 50.f));
    this->testShape.setFillColor(sf::Color::Red);
}

void SplashScreen::Reload() {
    testShape.setPosition(sf::Vector2f(500.f, 500.f));
}

void SplashScreen::Poll() {

}

void SplashScreen::Physics() {

}

void SplashScreen::UIPhysics() {

}

void SplashScreen::DrawContext(sf::RenderWindow& win) {
    win.draw(this->testShape);
}

void SplashScreen::DrawUIContext() {

}
