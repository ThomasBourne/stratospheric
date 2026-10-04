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
    extern const unsigned int stepRate;
    extern const unsigned int frameStepInfoUpdate;

    namespace assets {
        extern std::string assetFolderPath;
        extern const std::string splashScreen;
        extern const std::string tilemap;
        extern const std::string defaultFont;
    }

    extern const int tilemapDefinition;

    namespace settings {
        extern const std::string settingsFile;
        extern const std::string compatibleConfigVersion;
        extern const std::string compatibleLevelVersion;
        extern const char globalDelimiter;
    }

    std::string GetCWD();

    namespace logic {
        void ResizeSpriteToWin(sf::Sprite&, sf::View&);
    }

    enum class StratErrorCodes {
        // 0 No Error
        OK=0,
        // 1XX File Error Codes
            // 10X File Read Errors
        FileLoadFailed = 100,
        AssetFileLoadFailed = 101,
        SettingsFileLoadFailed = 102,
            // 11X File Write Errors
        fileWriteFailed = 110,
        SettingsileWriteFailed = 111
    };
}

#endif