#pragma once
#include <string>

struct Resistor {
    std::string name;
    double resistance_ohms;

    Resistor(const std::string& name, double ohms)
        : name(name), resistance_ohms(ohms) {}
};
