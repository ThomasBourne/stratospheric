#ifndef ENGINE_SETTINGS_KEYBINDS_HPP
#define ENGINE_SETTINGS_KEYBINDS_HPP

#include <SFML/Window/Keyboard.hpp>

#include "../../utility/utility.hpp"

namespace engine {
    using Key = sf::Keyboard::Key;

    class Keybinds {
    public:
        Keybinds() = default;

        utility::StratErrorCodes LoadFromFile(const std::string&);

    public:
        Key playerUp;
        Key playerDown;
        Key playerLeft;
        Key playerRight;

        Key menuOpen;
        Key menuClose;


    };
}

#endif
