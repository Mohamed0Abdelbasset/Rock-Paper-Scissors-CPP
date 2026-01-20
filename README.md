# Rock-Paper-Scissors Game (C++)

A robust, console-based implementation of Rock-Paper-Scissors built using C++. This project focuses on clean code principles, modular function design, and structured data management.

## 🛠 Features
- **Input Validation:** Ensures the user enters a valid choice (1-3) and a valid number of rounds.
- **Dynamic Visuals:** Uses Windows API system calls to change console colors based on round outcomes (Win/Loss/Draw).
- **Comprehensive Statistics:** Tracks player wins, computer wins, and draws across a multi-round session.
- **Clean Architecture:** Utilizes `struct` for data grouping and `enum` for state management.

## 💻 Technical Highlights
This project demonstrates proficiency in:
- **Enums:** Defining game choices and winner states to eliminate magic numbers.
- **Structs:** Passing complex data packages between functions.
- **Loops & Logic:** Implementing game loops and conditional win-logic.
- **Randomization:** Seeding the random number generator with system time for unpredictable AI moves.

## 🚀 How to Run
1. Download the `main.cpp` file.
2. Open your terminal or command prompt.
3. Compile using a C++ compiler:
   ```bash
   g++ main.cpp -o RPS_Game
