#include "fpsdisplay.hpp"

using namespace engine;

FPSCounter::FPSCounter(sf::Font& fpsFont) :
    renderFPS(fpsFont)
    {
        renderFPS.setPosition({ 0.f, 0.f });
        renderFPS.setFillColor(sf::Color::Green);

        fpsBackground.setPosition({ 0.f, 0.f });
        fpsBackground.setSize({ 60.f, 40.f });
        fpsBackground.setFillColor(sf::Color::Black);
    }

void FPSCounter::UpdateFPSStep() {
    currentTime = fpsClock.restart().asSeconds();
    fps = (unsigned short)(1.f / currentTime);
    lastTime = currentTime;
    if (fpsRefreshPause == 0) {
        renderFPS.setString(std::to_string(fps));
    }
    fpsRefreshPause++;
    fpsRefreshPause %= utility::frameStepInfoUpdate;
}

void FPSCounter::DrawFPS(sf::RenderWindow& win) {
    win.draw(fpsBackground);
    win.draw(renderFPS);
}

