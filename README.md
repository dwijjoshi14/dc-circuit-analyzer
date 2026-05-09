# DC Circuit Analyzer

A command-line C++ tool that applies **Ohm's Law** and **Kirchhoff's Laws** to analyze series and parallel DC resistive circuits. Given a supply voltage and a set of resistors, it calculates total resistance, current, per-component voltage drops, and power dissipation — then verifies results against KVL/KCL.

---

## Sample Output
==========================================================
DC CIRCUIT ANALYSIS  -  SERIES CIRCUIT
Supply Voltage    : 12.0000 V
Total Resistance  : 790.0000 ohms
Total Current     : 0.0152 A
Total Power       : 0.1823 W
Name    R (ohms)   V-drop (V)    I (A)       P (W)
R1      100.0000    1.5190        0.0152      0.0231
R2      220.0000    3.3418        0.0152      0.0508
R3      470.0000    7.1392        0.0152      0.1084
KVL check: sum of voltage drops = 12.0000 V  (supply = 12.0000 V)

---

## Physics Behind It

**Series circuits** (KVL + KCL):
- Total resistance: `R_total = R1 + R2 + ... + Rn`
- Same current flows through every component: `I = V / R_total`
- Voltage divides across components: `V_n = I x R_n`
- KVL verification: sum of voltage drops = supply voltage

**Parallel circuits** (KVL + KCL):
- Total resistance: `1/R_total = 1/R1 + 1/R2 + ... + 1/Rn`
- Same voltage across every branch: `V_n = V_supply`
- Current divides across branches: `I_n = V_supply / R_n`
- KCL verification: sum of branch currents = total current

**Power per component:** `P = V x I`

---

## Build & Run

**Requirements:** g++ with C++17 support (standard on Linux/macOS/WSL)

```bash
# Clone and build
git clone https://github.com/dwijjoshi14/dc-circuit-analyzer.git
cd dc-circuit-analyzer
make

# Run demo (preset series + parallel examples)
make demo

# Run interactive mode
./circuit_analyzer
```

**Interactive mode example:**
Circuit type - enter S for Series, P for Parallel: S
Supply voltage (V): 9
R1 resistance in ohms (0 to finish): 330
R2 resistance in ohms (0 to finish): 470
R3 resistance in ohms (0 to finish): 0

---

## Project Structure
dc-circuit-analyzer/
├── src/
│   ├── main.cpp        # Entry point, interactive + demo modes
│   ├── circuit.h       # Circuit class interface
│   ├── circuit.cpp     # Series/parallel analysis logic
│   └── resistor.h      # Resistor data structure
├── Makefile
├── .gitignore
└── README.md

---

## Why I Built This

My physics labs involved calculating voltage drops, branch currents, and power dissipation by hand. This tool automates that workflow in C++ — applying the same Kirchhoff's Laws from the lab, structured into a class-based design with input validation and automatic KVL/KCL verification.

**Next steps:**
- Series-parallel (mixed) circuit support
- CSV output for plotting voltage/current profiles
- Node-voltage method for arbitrary topologies

---

## Built With

`C++17` · `Ohm's Law` · `KVL` · `KCL` · `OOP` · `Make`
