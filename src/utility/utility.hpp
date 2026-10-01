#ifndef UTILITY_UTILITY_HPP
#define UTILITY_UTILITY_HPP

#include <string>
#include <SFML/System/Vector2.hpp>
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
    extern sf::Vector2u windowSize;
    extern sf::Vector2u windowSize;
    extern unsigned int stepRate;

    namespace assets {
        extern std::string assetFolderPath;
        extern const std::string splashScreen;
    }

    std::string GetCWD();
}

#endif