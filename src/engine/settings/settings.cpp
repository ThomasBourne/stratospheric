#include "settings.hpp"

#include <fstream>
#include <vector>
#include <sstream>

#define EXIT_LOAD_FROM_FILE_BAD_OPEN_STREAM fileStream.close(); return utility::StratErrorCodes::SettingsFileLoadFailed

// TODO: To simplify code, make this to generate the chunk of code required to assign a variable
// #define MEMBER_VALUE_ASSIGNMENT(index, item, value)

using namespace engine;

Settings::Settings(sf::Font& font) : fontRef(font) { }

utility::StratErrorCodes Settings::LoadFromFile(const std::string& settingsPath) {
    std::ifstream fileStream{ settingsPath };
    std::string fileLine;
    unsigned int lineCount{ 0U };

    if (fileStream.bad() || !fileStream.is_open()) {
        return utility::StratErrorCodes::FileLoadFailed;
    }

    while(std::getline(fileStream, fileLine)) {
        switch (lineCount)
        {
        case (0): {
            if (fileLine != utility::settings::compatibleConfigVersion) {
                EXIT_LOAD_FROM_FILE_BAD_OPEN_STREAM;
            }
            break;
        }

        case (1): {
            std::stringstream lineStream{ fileLine };
            std::string segment;
            std::vector<std::string> lineSegList;

            while(std::getline(lineStream, segment, ',')) {
                if (segment != "1" && segment != "0") {
                    EXIT_LOAD_FROM_FILE_BAD_OPEN_STREAM;
                }
                lineSegList.push_back(segment);
            }

            if (lineSegList.size() != 1) {
                EXIT_LOAD_FROM_FILE_BAD_OPEN_STREAM;
            }
            
            // Assignments
            constexpr int fpsIndex{ 0 };
            const std::string fpsLString{ "Enable FPS Display" };
            this->fpsEnabled = (bool)std::stoi(lineSegList[fpsIndex]);
            this->booleanValues.push_back(ToggleValue(this->fontRef, fpsLString, &this->fpsEnabled));
            
            break;
        }
        
        default: {
            EXIT_LOAD_FROM_FILE_BAD_OPEN_STREAM;
        }
        }

        lineCount++;
    }

    fileStream.close();

    return utility::StratErrorCodes::OK;
}

utility::StratErrorCodes Settings::WriteToFile(const std::string& settingsPath) {
    return utility::StratErrorCodes::SettingsileWriteFailed;
}

Settings::Value* Settings::GetSelectedValue(sf::Vector2f mousePos) {
    for (ToggleValue& booleanToggle : this->booleanValues) {
        if (booleanToggle.renderedOutput.getGlobalBounds().contains(mousePos)) {
            return &booleanToggle;
        }
    }

    return nullptr;
}

void Settings::DrawBooleanValues(sf::RenderWindow& win) {
    for (ToggleValue& booleanToggle : this->booleanValues) {
        win.draw(booleanToggle.renderedOutput);
    }
}
