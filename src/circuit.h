#pragma once
#include "resistor.h"
#include <vector>
#include <string>

enum class CircuitType { SERIES, PARALLEL };

struct ComponentResult {
    std::string name;
    double resistance_ohms;
    double voltage_drop_V;
    double current_A;
    double power_W;
};

struct CircuitResult {
    CircuitType type;
    double supply_voltage_V;
    double total_resistance_ohms;
    double total_current_A;
    double total_power_W;
    std::vector<ComponentResult> components;
};

class Circuit {
public:
    Circuit(double supply_voltage, CircuitType type);
    void addResistor(const std::string& name, double ohms);
    CircuitResult analyze() const;

private:
    double supply_voltage_;
    CircuitType type_;
    std::vector<Resistor> resistors_;

    double calcSeriesTotal() const;
    double calcParallelTotal() const;
};
