#include "utility.hpp"

#include <algorithm>

const std::string utility::windowName{ "Hello Window!" };
const sf::Vector2u utility::defaultWindowSize{ 1920U, 1080U };
const unsigned int utility::stepRate{ 200 };
const unsigned int utility::frameStepInfoUpdate{ 200 };
bool utility::_window::isWindowFullscreen{ false }; // False by default, see todo

std::string utility::assets::assetFolderPath{ "/assets/" };
const std::string utility::assets::splashScreen{ "splash_screen.png" };
const std::string utility::assets::tilemap{ "tilemap.png" };
const std::string utility::assets::defaultFont{ "fc.ttf" };
const std::string utility::assets::sheepTexture{ "sheep.png" };

const std::string utility::game::tilemapFileName{ "map.save" };
const int utility::game::tilemapDefinition{ 100 };
const sf::Vector2i utility::game::tileSize{ utility::game::tilemapDefinition, utility::game::tilemapDefinition };
const sf::Vector2<sf::Vector2f> utility::game::viewBounds{ {150.f, 150.f}, {100.f, 100.f} };

const std::string utility::settings::settingsFile{ "settings.strat" };
const std::string utility::settings::compatibleConfigVersion{ "0.0.1" };
const std::string utility::settings::compatibleLevelVersion{ "0.0.1" };
const char utility::settings::globalDelimiter{ ',' };

const size_t utility::animate::player::framesPerAnimationFrame{ 25ULL };

std::string utility::GetCWD() {
    std::string cwd = std::filesystem::current_path().string();
    // In Windows, current_path uses \ for folder structure, remove these for SFML
    std::replace(cwd.begin(), cwd.end(), '\\', '/');
    return cwd;
}

void utility::ReloadWindow(sf::RenderWindow& win, bool fullscreen) {
    win.create(
        utility::GetCorrectVideoMode(fullscreen),
		utility::windowName,
		sf::Style::Default,
		utility::GetCorrectWinState(fullscreen)
    );
	win.setVerticalSyncEnabled(false);
	win.setFramerateLimit(utility::stepRate);
    utility::_window::isWindowFullscreen = fullscreen;
}

sf::VideoMode utility::GetCorrectVideoMode(bool isRequestingFullscreen) {
    if (isRequestingFullscreen) {
        return sf::VideoMode( sf::Vector2u(sf::VideoMode::getDesktopMode().size) );
    }
    return sf::VideoMode( utility::defaultWindowSize );
}

sf::State utility::GetCorrectWinState(bool isRequestingFullscreen) {
    return isRequestingFullscreen ? sf::State::Fullscreen : sf::State::Windowed;
}

utility::StratErrorCodes utility::SafeExit(int exitCode, StratErrorCodes (*WriteConfigToFile)(const std::string&)) {
    const StratErrorCodes configWrite = WriteConfigToFile(ASSET_FILE(utility::settings::settingsFile));
    bool safeExitAchieved = (
        configWrite == StratErrorCodes::OK
    );
    int finalExitCode = exitCode != 0 ? exitCode : (int)!safeExitAchieved;
    exit(finalExitCode);
}

void utility::logic::ResizeSpriteToWin(sf::Sprite& sprite, const sf::View& view) {
    sprite.setScale(sf::Vector2f(1.f, 1.f));
    sprite.setScale(
        sf::Vector2f(
            view.getSize().x / sprite.getGlobalBounds().size.x,
            view.getSize().y / sprite.getGlobalBounds().size.y
        )
    );
}
