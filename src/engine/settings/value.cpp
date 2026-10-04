#include "settings.hpp"

#include <iostream>

using namespace engine;

// Value base class
Settings::Value::Value(sf::Font& font) :
    renderedOutput(font),
    lText(""),
    rText("")
    {
        renderedOutput.setPosition({ 100.f, 50.f });
    }

void Settings::Value::SetLText(const std::string text) {
    this->lText = text;
    this->ComputeText();
}
void Settings::Value::SetRText(const std::string text) {
    this->rText = text;
    this->ComputeText();
}
void Settings::Value::ChangeValue() { }

void Settings::Value::ComputeText() {
    this->fullText = lText + ": " + rText;
    this->renderedOutput.setString(this->fullText);
}


// Toggle Value child class
Settings::ToggleValue::ToggleValue(sf::Font& font, std::string lString, bool* initialValue) :
    Value(font)
    {
        this->SetLText(lString);
        this->value = initialValue;
        SetRText(ToggleValue::BoolToString(*this->value));
    }

void Settings::ToggleValue::ChangeValue() {
    *this->value = !*this->value;
    this->SetRText(Settings::ToggleValue::BoolToString(*this->value));
}

std::string Settings::ToggleValue::BoolToString(bool& bVal) {
    if (bVal) {
        return "True";
    }
    return "False";
}
