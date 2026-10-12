#include "settings.hpp"

#include <fstream>
#include <vector>
#include <sstream>

// Utility Macros
#define CONCAT(a, b) CONCAT_(a, b)
#define CONCAT_(a, b) a ## b

// Macros
#define EXIT_LOAD_FROM_FILE_BAD_OPEN_STREAM fileStream.close(); return utility::StratErrorCodes::SettingsFileLoadFailed

#define MEMBER_VALUE_ASSIGNMENT(index, item, value, text)                                           \
    constexpr int CONCAT(item, Index){ index };                                                     \
    const std::string CONCAT(item, LString){ #text };                                               \
    this->value = (bool)std::stoi(lineSegListBooleans[CONCAT(item, Index)]);                        \
    this->booleanValues.push_back(ToggleValue(this->fontRef, CONCAT(item, LString), &this->value)); \

using namespace engine;

Settings::Settings(sf::Font& font) : fontRef(font), selectedValue(nullptr) {
    this->selectedHighlight.setFillColor(sf::Color::Green);
}

utility::StratErrorCodes Settings::LoadFromFile(const std::string& settingsPath) {
    std::ifstream fileStream{ settingsPath };
    std::string fileLine;
    unsigned int lineCount{ 0U };

    std::vector<std::string> lineSegListBooleans;

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

            while(std::getline(lineStream, segment, ',')) {
                if (segment != "1" && segment != "0") {
                    EXIT_LOAD_FROM_FILE_BAD_OPEN_STREAM;
                }
                lineSegListBooleans.push_back(segment);
            }

            if (lineSegListBooleans.size() != 2) {
                EXIT_LOAD_FROM_FILE_BAD_OPEN_STREAM;
            }

            break;
        }
        
        default: {
            EXIT_LOAD_FROM_FILE_BAD_OPEN_STREAM;
        }
        }

        lineCount++;
    }

    fileStream.close();

    // Assignments
    MEMBER_VALUE_ASSIGNMENT(0, fps, fpsEnabled, Enable FPS Display);
    MEMBER_VALUE_ASSIGNMENT(1, fullscreen, fullscreenEnabled, Enable Fullscreen);

    for (size_t i = 0; i < booleanValues.size(); i++) {
        booleanValues[i].renderedOutput.setPosition({
            100.f,
            70.f + (50.f * i)
        });
    }

    return utility::StratErrorCodes::OK;
}

utility::StratErrorCodes Settings::WriteToFile(const std::string& settingsPath) {
    std::string fileOutput;
    std::ofstream fileStream{ settingsPath };

    if (fileStream.bad() || !fileStream.is_open()) {
        return utility::StratErrorCodes::SettingsileWriteFailed;
    }

    fileOutput = utility::settings::compatibleConfigVersion + '\n';
    for (auto& toggle : this->booleanValues) {
        fileOutput += std::to_string(*toggle.value) + ',';
    }
    (void)fileOutput.pop_back();

    fileStream << fileOutput;

    fileStream.close();

    return utility::StratErrorCodes::OK;
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
    win.draw(this->selectedHighlight);
    for (ToggleValue& booleanToggle : this->booleanValues) {
        win.draw(booleanToggle.renderedOutput);
    }
}

void Settings::SetToggleValue(Value* newSetToggleValue) {
    if (newSetToggleValue == this->selectedValue || newSetToggleValue == nullptr) {
        this->selectedValue = nullptr;
        this->selectedHighlight.setPosition({ -100.f, -100.f });
    }
    else if (newSetToggleValue != nullptr) {
        this->selectedValue = newSetToggleValue;
        this->selectedHighlight.setPosition(this->selectedValue->renderedOutput.getPosition());
        this->selectedHighlight.setSize(this->selectedValue->renderedOutput.getGlobalBounds().size);
    }
}

const Settings::Value * const Settings::GetToggledValueRef() {
    return (const Value * const)this->selectedValue;
}
