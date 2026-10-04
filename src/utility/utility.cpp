#include "utility.hpp"

#include <algorithm>

const std::string utility::windowName{ "Hello Window!" };
const sf::Vector2u utility::defaultWindowSize{ 1920U, 1080U };
const unsigned int utility::stepRate{ 200 };
const unsigned int utility::frameStepInfoUpdate{ 200 };

std::string utility::assets::assetFolderPath{ "/assets/" };
const std::string utility::assets::splashScreen{ "splash_screen.png" };
const std::string utility::assets::tilemap{ "tilemap.png" };
const std::string utility::assets::defaultFont{ "fc.ttf" };

const int utility::tilemapDefinition{ 100 };

const std::string utility::settings::settingsFile = "settings.strat";
const std::string utility::settings::compatibleConfigVersion = "0.0.1";
const std::string utility::settings::compatibleLevelVersion = "0.0.1";
const char utility::settings::globalDelimiter = ',';

std::string utility::GetCWD() {
    std::string cwd = std::filesystem::current_path().string();
    // In Windows, current_path uses \ for folder structure, remove these for SFML
    std::replace(cwd.begin(), cwd.end(), '\\', '/');
    return cwd;
}

void utility::logic::ResizeSpriteToWin(sf::Sprite& sprite, sf::View& view) {
    sprite.setScale(sf::Vector2f(1.f, 1.f));
    sprite.setScale(
        sf::Vector2f(
            view.getSize().x / sprite.getGlobalBounds().size.x,
            view.getSize().y / sprite.getGlobalBounds().size.y
        )
    );
}
