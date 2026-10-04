#ifndef ENGINE_RENDER_UTILITY_FPSDISPLAY_HPP
#define ENGINE_RENDER_UTILITY_FPSDISPLAY_HPP

#include <SFML/Graphics.hpp>

#include "../../utility/utility.hpp"

namespace engine {
    class FPSCounter {
        // Public Functions
    public:
        FPSCounter(sf::Font&);
        void UpdateFPSStep();
        void DrawFPS(sf::RenderWindow&);

        // Private members
    private:
        sf::Clock fpsClock;
        sf::Text renderFPS;
        sf::RectangleShape fpsBackground;
        bool fpsRedraw;
        float currentTime;
        float lastTime;
        unsigned short fps;
        unsigned short fpsRefreshPause;
    };
}

#endif