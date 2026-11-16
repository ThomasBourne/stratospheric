#include "keybinds.hpp"

#include <fstream>
#include <vector>
#include <sstream>

// Utility Macros
#define CONCAT(a, b) CONCAT_(a, b)
#define CONCAT_(a, b) a ## b

// Macros
#define EXIT_LOAD_FROM_FILE_BAD_OPEN_STREAM fileStream.close(); return utility::StratErrorCodes::KeybindFileLoadFailed

#define MEMBER_VALUE_ASSIGNMENT(index, value, text)                                                 \
    constexpr int CONCAT(value, Index){ index };                                                    \
    const std::string CONCAT(value, LString){ #text };                                              \
    this->value = (engine::Key)std::stoi(lineSegListBooleans[CONCAT(value, Index)]);                \
    // this->booleanValues.push_back(ToggleValue(this->fontRef, CONCAT(value, LString), &this->value));\


// Utility Functions (TODO: to move to engine/abstract/serialisable)
// TODO: settings.cpp uses a boolean finder, move that too
bool isNumber(const std::string& s) {
    return !s.empty() && std::find_if(s.begin(), 
        s.end(), [](unsigned char c) { return !std::isdigit(c); }) == s.end();
}

utility::StratErrorCodes engine::Keybinds::LoadFromFile(const std::string& keybindsPath) {
    std::ifstream fileStream{ keybindsPath };
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
            if (fileLine != utility::settings::compatibleKeybindVersion) {
                EXIT_LOAD_FROM_FILE_BAD_OPEN_STREAM;
            }
            break;
        }

        case (1): {
            std::stringstream lineStream{ fileLine };
            std::string segment;

            while(std::getline(lineStream, segment, ',')) {
                
                if (!isNumber(segment)) {
                    EXIT_LOAD_FROM_FILE_BAD_OPEN_STREAM;
                }
                lineSegListBooleans.push_back(segment);
            }

            if (lineSegListBooleans.size() != 6) {
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
    MEMBER_VALUE_ASSIGNMENT(0, playerUp, Player Up);
    MEMBER_VALUE_ASSIGNMENT(1, playerDown, Player Down);
    MEMBER_VALUE_ASSIGNMENT(2, playerLeft, Player Left);
    MEMBER_VALUE_ASSIGNMENT(3, playerRight, Player Right);

    MEMBER_VALUE_ASSIGNMENT(4, menuOpen, Menu Open);
    MEMBER_VALUE_ASSIGNMENT(5, menuClose, Menu Close);
    
    return utility::StratErrorCodes::OK;
}