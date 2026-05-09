#include "circuit.h"
#include <stdexcept>

Circuit::Circuit(double supply_voltage, CircuitType type)
    : supply_voltage_(supply_voltage), type_(type) {
    if (supply_voltage <= 0)
        throw std::invalid_argument("Supply voltage must be positive.");
}

void Circuit::addResistor(const std::string& name, double ohms) {
    if (ohms <= 0)
        throw std::invalid_argument("Resistance must be positive: " + name);
    resistors_.emplace_back(name, ohms);
}

double Circuit::calcSeriesTotal() const {
    double total = 0.0;
    for (const auto& r : resistors_)
        total += r.resistance_ohms;
    return total;
}

double Circuit::calcParallelTotal() const {
    double reciprocal = 0.0;
    for (const auto& r : resistors_)
        reciprocal += 1.0 / r.resistance_ohms;
    return 1.0 / reciprocal;
}

CircuitResult Circuit::analyze() const {
    if (resistors_.empty())
        throw std::runtime_error("No resistors in circuit.");

    CircuitResult result;
    result.type = type_;
    result.supply_voltage_V = supply_voltage_;

    if (type_ == CircuitType::SERIES) {
        result.total_resistance_ohms = calcSeriesTotal();
        result.total_current_A = supply_voltage_ / result.total_resistance_ohms;

        for (const auto& r : resistors_) {
            ComponentResult cr;
            cr.name = r.name;
            cr.resistance_ohms = r.resistance_ohms;
            cr.current_A = result.total_current_A;
            cr.voltage_drop_V = cr.current_A * r.resistance_ohms;
            cr.power_W = cr.voltage_drop_V * cr.current_A;
            result.components.push_back(cr);
        }
    } else {
        result.total_resistance_ohms = calcParallelTotal();
        result.total_current_A = supply_voltage_ / result.total_resistance_ohms;

        for (const auto& r : resistors_) {
            ComponentResult cr;
            cr.name = r.name;
            cr.resistance_ohms = r.resistance_ohms;
            cr.voltage_drop_V = supply_voltage_;
            cr.current_A = supply_voltage_ / r.resistance_ohms;
            cr.power_W = cr.voltage_drop_V * cr.current_A;
            result.components.push_back(cr);
        }
    }

    result.total_power_W = supply_voltage_ * result.total_current_A;
    return result;
}
