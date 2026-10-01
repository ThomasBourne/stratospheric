#include "utility.hpp"

#include <algorithm>

const std::string utility::windowName{ "Hello Window!" };
sf::Vector2u utility::windowSize{ 1920U, 1080U };
unsigned int utility::stepRate{ 200 };

std::string utility::assets::assetFolderPath{ "/assets/" };
const std::string utility::assets::splashScreen{ "splash_screen.png" };

std::string utility::GetCWD() {
    std::string cwd = std::filesystem::current_path().string();
    // In Windows, current_path uses \ for folder structure, remove these for SFML
    std::replace(cwd.begin(), cwd.end(), '\\', '/');
    return cwd;
}