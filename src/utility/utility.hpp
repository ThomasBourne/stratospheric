#ifndef UTILITY_UTILITY_HPP
#define UTILITY_UTILITY_HPP

#include <string>
#include <SFML/Graphics.hpp>
#include <filesystem>

// Error codes
	/// SFML Errors
#define ERROR_CODE_SFML_FAILED_FILE_READ 1001

// SFML File Open Wrapper
#define SFML_FILE_OPEN(load_file_command) if (!load_file_command) exit(ERROR_CODE_SFML_FAILED_FILE_READ)

// Asset filepath
#define ASSET_FILE(asset) std::string(utility::GetCWD() + utility::assets::assetFolderPath + asset)

namespace utility {
    extern const std::string windowName;
    extern const sf::Vector2u defaultWindowSize;
    extern unsigned int stepRate;

    namespace assets {
        extern std::string assetFolderPath;
        extern const std::string splashScreen;
        extern const std::string tilemap;
        extern const std::string defaultFont;
    }

    extern const int tilemapDefinition;

    std::string GetCWD();

    namespace logic {
        void ResizeSpriteToWin(sf::Sprite&, sf::View&);
    }
}

#endif