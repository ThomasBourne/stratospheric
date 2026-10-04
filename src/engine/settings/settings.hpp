#ifndef ENGINE_SETTINGS_SETTINGS_HPP
#define ENGINE_SETTINGS_SETTINGS_HPP

#include <vector>

#include "../../utility/utility.hpp"

namespace engine {
    class Settings {
        // Public Classes
    public:
        struct Value {
            sf::Text renderedOutput;
            std::string lText;
            std::string rText;
            std::string fullText;
            Value(sf::Font&);
            void SetLText(const std::string);
            void SetRText(const std::string);
            virtual void ChangeValue();
        private:
            void ComputeText();
        };
        struct ToggleValue : public Value {
            bool* value;
            ToggleValue(sf::Font&, std::string, bool*);
            void ChangeValue();

        private:
            static std::string BoolToString(bool&);
        };

        // Public Members
    public:
        bool fpsEnabled;

        // Public Functions
    public:
        Settings(sf::Font&); // Does not deserialise by default to return error code
        utility::StratErrorCodes LoadFromFile(const std::string& settingsPath);
        utility::StratErrorCodes WriteToFile(const std::string& settingsPath);

        Value* GetSelectedValue(sf::Vector2f);

        void DrawBooleanValues(sf::RenderWindow&);

        // Private Members
    private:
        sf::Font& fontRef;
        std::vector<ToggleValue> booleanValues;

        // Private Functions
    private:
    };
}

#endif