#ifndef UTILITY_UTILITY_HPP
#define UTILITY_UTILITY_HPP

#include <string>
#include <SFML/Graphics.hpp>
#include <filesystem>

// Asset filepath
#define ASSET_FILE(asset) std::string(utility::GetCWD() + utility::assets::assetFolderPath + asset)

namespace utility {
    enum class StratErrorCodes {
        // 0 No Error
        OK=0,
        // 1XX File Error Codes
            // 10X File Read Errors
        FileLoadFailed = 100,
        AssetFileLoadFailed = 101,
        SettingsFileLoadFailed = 102,
        TilemapFileLoadFailed = 103,
            // 11X File Write Errors
        fileWriteFailed = 110,
        SettingsileWriteFailed = 112,
        TilemapWriteFailed = 113
    };

    extern const std::string windowName;
    extern const sf::Vector2u defaultWindowSize;
    extern const unsigned int stepRate;
    extern const unsigned int frameStepInfoUpdate;

    namespace _window {
        extern bool isWindowFullscreen; // TODO: This is dangerous as external code can rewrite, change later to make this protected somehow
    }

    namespace assets {
        extern std::string assetFolderPath;
        extern const std::string splashScreen;
        extern const std::string tilemap;
        extern const std::string defaultFont;
        extern const std::string sheepTexture;
    }

    namespace game {
        extern const std::string tilemapFileName;
        extern const int tilemapDefinition;
        extern const sf::Vector2i tileSize;
        extern const sf::Vector2<sf::Vector2f> viewBounds;
    }

    namespace settings {
        extern const std::string settingsFile;
        extern const std::string compatibleConfigVersion;
        extern const std::string compatibleLevelVersion;
        extern const char globalDelimiter;
    }

    namespace animate {
        namespace player {
            extern const size_t framesPerAnimationFrame;
        }
    }

    std::string GetCWD();

    // TODO: Eventually enable custom resolution
    void ReloadWindow(sf::RenderWindow&, bool);
    sf::VideoMode GetCorrectVideoMode(bool isRequestingFullscreen);
    sf::State GetCorrectWinState(bool isRequestingFullscreen);

    StratErrorCodes SafeExit(int exitCode, StratErrorCodes (*WriteConfigToFile)(const std::string&));

    namespace logic {
        void ResizeSpriteToWin(sf::Sprite&, const sf::View&);
    }
}

#endif