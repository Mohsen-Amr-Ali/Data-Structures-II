#include <iostream>
#include <string>
#include <fstream>
#include <conio.h> // Required for _getch()

// Include Windows API for color support
#ifdef _WIN32
#include <windows.h>
#endif

// Include our new Graph and Algorithm headers
#include "Graph.h"
#include "TopologicalSort.h"
#include "PrimAlgorithm.h"

// Assuming cli_menu.hpp is accessible. Adjust path if necessary (e.g., "header/cli_menu.hpp")
#include "cli_menu.hpp"

// ANSI Color Macros mirroring HW4 & HW5
#define COLOR_GREEN "\x1b[32m"
#define COLOR_YELLOW "\x1b[33m"
#define COLOR_RED "\x1b[31m"
#define COLOR_ORANGE "\x1b[38;2;255;103;0m"
#define COLOR_CYAN "\x1b[96m"
#define COLOR_BLUE "\x1b[94m"
#define COLOR_RESET "\x1b[0m"

// Forward declarations for our menu actions
void runTopologicalSort();
void runPrimsAlgorithm();
void runCustomTopologicalSort();
void runCustomPrimsAlgorithm();

int main() {
    // Enable colors before printing anything!
    enableWindowsColors();

    // Initialize the UI Menu - Updated for Assignment 4
    Menu mainMenu("\n\x1b[33mPlease select an algorithm to run:\x1b[0m", "Graphs", "Assignment 4");

    // Add your team members (Mohsen is already in the cli_menu boilerplate)
    mainMenu.addTeamMember("Ahmed Yasser - 9604");
    mainMenu.addTeamMember("Malak Hisham - 9560");

    // Add the functional options for the new assignment.
    // The "false" flag tells the new menu NOT to ask "Do you want to run again?"
    mainMenu.addItem("1) Run Topological Sort (Assignment Graph)", []() { runTopologicalSort(); }, false);
    mainMenu.addItem("2) Run Minimum Spanning Tree (Assignment Graph)", []() { runPrimsAlgorithm(); }, false);
    mainMenu.addItem("3) Run Topological Sort (Custom Graph)", []() { runCustomTopologicalSort(); }, true);
    mainMenu.addItem("4) Run Minimum Spanning Tree (Custom Graph)", []() { runCustomPrimsAlgorithm(); }, true);

    // Exit option
    mainMenu.addExitItem("\x1b[31mExit Program\x1b[0m");

    // Start the application loop
    mainMenu.run();

    return 0;
}

// --- Application Functions ---

void runTopologicalSort() {
    std::cout << "  " << COLOR_CYAN << "--- Topological Sort (Kahn's Algorithm) ---\n" << COLOR_RESET;

    // Instantiate a Graph with 8 vertices (0 through 7)
    Graph g(8);

    // Recreating the Directed Acyclic Graph from Assignment Image 1
    g.addEdge(7, 5, 0, true);
    g.addEdge(7, 6, 0, true);
    g.addEdge(5, 4, 0, true);
    g.addEdge(5, 2, 0, true);
    g.addEdge(6, 4, 0, true);
    g.addEdge(6, 3, 0, true);
    g.addEdge(4, 1, 0, true);
    g.addEdge(2, 1, 0, true);
    g.addEdge(3, 1, 0, true);
    g.addEdge(1, 0, 0, true);

    std::cout << "  " << COLOR_YELLOW << "Graph successfully created with 8 vertices and 10 directed edges.\n\n" << COLOR_RESET;
    std::cout << "  " << COLOR_ORANGE << "Result:\n  " << COLOR_RESET;

    // Execute Malak's Topological Sort
    TopologicalSort::execute(g);

    std::cout << "\n  " << COLOR_YELLOW << "Press any key to go back to the main menu..." << COLOR_RESET;
    _getch();
}

void runPrimsAlgorithm() {
    std::cout << "  " << COLOR_CYAN << "--- Minimum Spanning Tree (Prim's Algorithm) ---\n" << COLOR_RESET;

    // Instantiate a Graph with 9 vertices (a through i)
    // Mapping: a=0, b=1, c=2, d=3, e=4, f=5, g=6, h=7, i=8
    Graph g(9);

    // Recreating the Undirected Weighted Graph from Assignment Image 2
    g.addEdge(0, 1, 4, false);  // a - b
    g.addEdge(0, 7, 8, false);  // a - h
    g.addEdge(1, 2, 8, false);  // b - c
    g.addEdge(1, 7, 11, false); // b - h
    g.addEdge(2, 8, 2, false);  // c - i
    g.addEdge(2, 5, 4, false);  // c - f
    g.addEdge(2, 3, 7, false);  // c - d
    g.addEdge(7, 8, 7, false);  // h - i
    g.addEdge(7, 6, 1, false);  // h - g
    g.addEdge(8, 6, 6, false);  // i - g
    g.addEdge(6, 5, 2, false);  // g - f
    g.addEdge(5, 4, 10, false); // f - e
    g.addEdge(5, 3, 14, false); // f - d
    g.addEdge(3, 4, 9, false);  // d - e

    std::cout << "  " << COLOR_YELLOW << "Graph successfully created with 9 vertices and 14 undirected edges.\n\n" << COLOR_RESET;

    int start_node = 0;
    mst_result result = PrimAlgorithm::execute(g, start_node);

    std::cout << "  " << COLOR_GREEN << "Total Minimum Spanning Tree Weight: " << COLOR_RESET << result.total_weight << "\n\n";
    std::cout << "  " << COLOR_ORANGE << "Edges included in the MST:\n" << COLOR_RESET;

    std::ofstream outFile("mst_output.txt");
    bool fileSaved = outFile.is_open();

    for (const auto& edge : result.edges) {
        char u_char = 'a' + edge.u;
        char v_char = 'a' + edge.v;
        std::cout << "    " << u_char << " - " << v_char << " \t(Weight: " << edge.weight << ")\n";

        // Save the raw integers for the Python visualizer
        if (fileSaved) {
            outFile << edge.u << " " << edge.v << " " << edge.weight << "\n";
        }
    }

    if (fileSaved) {
        outFile.close();
        std::cout << "\n  " << COLOR_BLUE << "Launching visualization..." << COLOR_RESET << "\n";
        // Launch python asynchronously
        system("start ..\\venv\\Scripts\\python.exe ..\\visualizer.py mst_output.txt");
    } else {
        std::cout << "\n  " << COLOR_RED << "Failed to save MST output for visualization." << COLOR_RESET << "\n";
    }

    std::cout << "\n  " << COLOR_YELLOW << "Press any key to go back to the main menu..." << COLOR_RESET;
    _getch();
}

void runCustomTopologicalSort() {
    std::cout << "  " << COLOR_CYAN << "--- Custom Topological Sort ---\n" << COLOR_RESET;

    int v, e;
    std::cout << "  " << COLOR_YELLOW << "Enter the number of vertices: " << COLOR_RESET;
    std::cin >> v;
    std::cout << "  " << COLOR_YELLOW << "Enter the number of edges: " << COLOR_RESET;
    std::cin >> e;

    if (v <= 0) {
        std::cout << "  " << COLOR_RED << "Invalid number of vertices.\n" << COLOR_RESET;
        return;
    }

    Graph g(v);

    std::cout << "  " << COLOR_YELLOW << "Enter " << e << " directed edges (u v) [using 0 to " << v - 1 << "]:\n" << COLOR_RESET;
    for (int i = 0; i < e; i++) {
        int u, dest;
        std::cout << "  " << COLOR_ORANGE << "Edge " << i + 1 << ": " << COLOR_RESET;
        std::cin >> u >> dest;

        if (u >= 0 && u < v && dest >= 0 && dest < v) {
            g.addEdge(u, dest, 0, true);
        } else {
            std::cout << "  " << COLOR_RED << "Invalid vertices! Must be between 0 and " << v - 1 << ". Try again.\n" << COLOR_RESET;
            i--;
        }
    }

    std::cout << "\n  " << COLOR_YELLOW << "Custom graph created successfully.\n\n" << COLOR_RESET;
    std::cout << "  " << COLOR_ORANGE << "Result:\n  " << COLOR_RESET;

    TopologicalSort::execute(g);
}

void runCustomPrimsAlgorithm() {
    std::cout << "  " << COLOR_CYAN << "--- Custom Minimum Spanning Tree (Prim's) ---\n" << COLOR_RESET;

    int v, e;
    std::cout << "  " << COLOR_YELLOW << "Enter the number of vertices: " << COLOR_RESET;
    std::cin >> v;
    std::cout << "  " << COLOR_YELLOW << "Enter the number of edges: " << COLOR_RESET;
    std::cin >> e;

    if (v <= 0) {
        std::cout << "  " << COLOR_RED << "Invalid number of vertices.\n" << COLOR_RESET;
        return;
    }

    Graph g(v);

    std::cout << "  " << COLOR_YELLOW << "Enter " << e << " undirected edges (u v weight) [using 0 to " << v - 1 << "]:\n" << COLOR_RESET;
    for (int i = 0; i < e; i++) {
        int u, dest, w;
        std::cout << "  " << COLOR_ORANGE << "Edge " << i + 1 << ": " << COLOR_RESET;
        std::cin >> u >> dest >> w;

        if (u >= 0 && u < v && dest >= 0 && dest < v) {
            g.addEdge(u, dest, w, false);
        } else {
            std::cout << "  " << COLOR_RED << "Invalid vertices! Must be between 0 and " << v - 1 << ". Try again.\n" << COLOR_RESET;
            i--;
        }
    }

    int start_node;
    std::cout << "\n  " << COLOR_YELLOW << "Enter the starting node [0 to " << v - 1 << "]: " << COLOR_RESET;
    std::cin >> start_node;

    if (start_node < 0 || start_node >= v) {
        std::cout << "  " << COLOR_RED << "Invalid starting node. Defaulting to 0.\n" << COLOR_RESET;
        start_node = 0;
    }

    std::cout << "\n  " << COLOR_YELLOW << "Custom graph created successfully.\n\n" << COLOR_RESET;

    mst_result result = PrimAlgorithm::execute(g, start_node);

    std::cout << "  " << COLOR_GREEN << "Total Minimum Spanning Tree Weight: " << COLOR_RESET << result.total_weight << "\n\n";
    std::cout << "  " << COLOR_ORANGE << "Edges included in the MST:\n" << COLOR_RESET;

    std::ofstream outFile("mst_output.txt");
    bool fileSaved = outFile.is_open();

    for (const auto& edge : result.edges) {
        std::cout << "    " << edge.u << " - " << edge.v << " \t(Weight: " << edge.weight << ")\n";
        if (fileSaved) {
            outFile << edge.u << " " << edge.v << " " << edge.weight << "\n";
        }
    }

    if (fileSaved) {
        outFile.close();
        std::cout << "\n  " << COLOR_BLUE << "Launching visualization..." << COLOR_RESET << "\n";
        // Launch python asynchronously
        system("start ..\\venv\\Scripts\\python.exe ..\\visualizer.py mst_output.txt");
    } else {
        std::cout << "\n  " << COLOR_RED << "Failed to save MST output for visualization." << COLOR_RESET << "\n";
    }
}