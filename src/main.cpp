#include "circuit.h"
#include <iostream>
#include <iomanip>
#include <stdexcept>

static void printSeparator(char c = '-', int width = 58) {
    std::cout << std::string(width, c) << "\n";
}

static void printResult(const CircuitResult& res) {
    std::string typeStr = (res.type == CircuitType::SERIES) ? "SERIES" : "PARALLEL";

    printSeparator('=');
    std::cout << "  DC CIRCUIT ANALYSIS  -  " << typeStr << " CIRCUIT\n";
    printSeparator('=');

    std::cout << std::fixed << std::setprecision(4);
    std::cout << "  Supply Voltage    : " << res.supply_voltage_V      << " V\n";
    std::cout << "  Total Resistance  : " << res.total_resistance_ohms << " ohms\n";
    std::cout << "  Total Current     : " << res.total_current_A       << " A\n";
    std::cout << "  Total Power       : " << res.total_power_W         << " W\n";
    printSeparator();

    std::cout << std::left
              << std::setw(10) << "  Name"
              << std::setw(12) << "R (ohms)"
              << std::setw(14) << "V-drop (V)"
              << std::setw(12) << "I (A)"
              << std::setw(10) << "P (W)"
              << "\n";
    printSeparator();

    for (const auto& c : res.components) {
        std::cout << "  "
                  << std::setw(8)  << c.name
                  << std::setw(12) << c.resistance_ohms
                  << std::setw(14) << c.voltage_drop_V
                  << std::setw(12) << c.current_A
                  << std::setw(10) << c.power_W
                  << "\n";
    }

    printSeparator();

    if (res.type == CircuitType::SERIES) {
        double vsum = 0;
        for (const auto& c : res.components) vsum += c.voltage_drop_V;
        std::cout << "  KVL check: sum of voltage drops = "
                  << vsum << " V  (supply = " << res.supply_voltage_V << " V)\n";
    } else {
        double isum = 0;
        for (const auto& c : res.components) isum += c.current_A;
        std::cout << "  KCL check: sum of branch currents = "
                  << isum << " A  (total = " << res.total_current_A << " A)\n";
    }
    printSeparator('=');
}

static void runInteractive() {
    std::cout << "\n========================================\n";
    std::cout << "   DC Circuit Analyzer - Interactive\n";
    std::cout << "========================================\n\n";

    std::cout << "Circuit type - enter S for Series, P for Parallel: ";
    char typeChar;
    std::cin >> typeChar;
    CircuitType ctype = (toupper(typeChar) == 'S') ? CircuitType::SERIES : CircuitType::PARALLEL;

    std::cout << "Supply voltage (V): ";
    double voltage;
    std::cin >> voltage;

    Circuit circuit(voltage, ctype);

    std::cout << "\nAdd resistors (enter 0 to finish):\n";
    int count = 1;
    while (true) {
        std::cout << "  R" << count << " resistance in ohms (0 to finish): ";
        double r;
        std::cin >> r;
        if (r <= 0) break;
        circuit.addResistor("R" + std::to_string(count), r);
        ++count;
    }

    std::cout << "\n";
    printResult(circuit.analyze());
}

static void runDemo() {
    std::cout << "\n=== DEMO: Series Circuit (12V, R1=100, R2=220, R3=470 ohms) ===\n\n";
    {
        Circuit c(12.0, CircuitType::SERIES);
        c.addResistor("R1", 100);
        c.addResistor("R2", 220);
        c.addResistor("R3", 470);
        printResult(c.analyze());
    }

    std::cout << "\n=== DEMO: Parallel Circuit (5V, R1=1000, R2=2200, R3=4700 ohms) ===\n\n";
    {
        Circuit c(5.0, CircuitType::PARALLEL);
        c.addResistor("R1", 1000);
        c.addResistor("R2", 2200);
        c.addResistor("R3", 4700);
        printResult(c.analyze());
    }
}

int main(int argc, char* argv[]) {
    try {
        if (argc > 1 && std::string(argv[1]) == "--demo") {
            runDemo();
        } else {
            runInteractive();
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }
    return 0;
}
