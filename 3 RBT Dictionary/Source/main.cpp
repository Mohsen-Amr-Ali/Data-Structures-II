#include <iostream>
#include <fstream>
#include <string>
#include <conio.h> // Required for _getch()

// Include Windows API for color support
#ifdef _WIN32
#include <windows.h>
#endif

#include "../Headers/RBT.hpp"
#include "../Headers/cli_menu.hpp"

// ANSI Color Macros mirroring HW4 & HW5
#define COLOR_GREEN "\x1b[32m"
#define COLOR_YELLOW "\x1b[33m"
#define COLOR_RED "\x1b[31m"
#define COLOR_ORANGE "\x1b[38;2;255;103;0m"
#define COLOR_CYAN "\x1b[96m"
#define COLOR_BLUE "\x1b[94m"
#define COLOR_RESET "\x1b[0m"

// Forward declarations for our menu actions
bool loadDictionary(RBT& tree, const std::string& filename);
void insertWordMenu(RBT& tree, const std::string& filename, Menu& menu);
void lookupWordMenu(RBT& tree, Menu& menu);
void updateMenuHeader(Menu& menu, RBT& tree, bool isLoaded);

int main() {
    // Enable colors before printing anything!
    enableWindowsColors();

    RBT tree;
    const std::string dictionaryFile = "Dictionary.txt"; // Adjusted to match your usual naming

    // Initialize the UI Menu - Note: Mohsen Amr is hardcoded on the left in cli_menu.cpp
    Menu mainMenu("Main Menu", "Red-Black Tree Dictionary", "Assignment 3");

    // Adding Ahmed Yasser to match the screenshot (Add 3rd member here if needed per assignment rules)
    mainMenu.addTeamMember("Ahmed Yasser - 9604");
    mainMenu.addTeamMember("Malak Hisham - 9560");

    // Load the dictionary right away on startup
    bool isLoaded = loadDictionary(tree, dictionaryFile);

    std::cout << "\n" << COLOR_YELLOW << "Press any key to enter the menu..." << COLOR_RESET << "\n";
    _getch(); // Using _getch directly for the startup pause

    // Update the menu header dynamically with the size and heights
    updateMenuHeader(mainMenu, tree, isLoaded);

    // Hook up the menu options using C++ lambda functions to pass parameters
    mainMenu.addItem("1] Insert a Word", [&]() { insertWordMenu(tree, dictionaryFile, mainMenu); });
    mainMenu.addItem("2] Look-up a Word", [&]() { lookupWordMenu(tree, mainMenu); });
    mainMenu.addItem("3] Print Tree Size", [&]() {
        std::cout << COLOR_ORANGE << "Current Dictionary Size: " << COLOR_RESET << tree.getSize() << "\n";
        mainMenu.pause();
    });
    mainMenu.addItem("4] Print Tree Height", [&]() {
        std::cout << COLOR_ORANGE << "Current Tree Height: " << COLOR_RESET << tree.getTreeHeight() << "\n";
        mainMenu.pause();
    });
    mainMenu.addItem("5] Print Black Height", [&]() {
        std::cout << COLOR_ORANGE << "Current Black Height: " << COLOR_RESET << tree.checkValidity() << "\n";
        mainMenu.pause();
    });
    mainMenu.addExitItem("6] Exit Program");

    // Start the application loop
    mainMenu.run();

    return 0;
}

// --- Application Functions ---

void updateMenuHeader(Menu& menu, RBT& tree, bool isLoaded) {
    // We use \r and \x1b[K to erase the default " --- " printed by the menu library
    // and seamlessly inject the dictionary stats exactly as shown in the HW5 screenshot.

    std::string statusColor = isLoaded ? COLOR_GREEN : COLOR_RED;
    std::string statusText = isLoaded ? "Dictionary loaded successfully" : "Dictionary is empty";

    std::string newTitle = "\r\x1b[K" + statusColor + statusText + COLOR_RESET
                         + "    " + COLOR_BLUE + "|" + COLOR_RESET + "    "
                         + COLOR_ORANGE + "Size = " + std::to_string(tree.getSize())
                         + "    Height = " + std::to_string(tree.getTreeHeight())
                         + "    Black Height = " + std::to_string(tree.checkValidity()) + COLOR_RESET
                         + "\n\n\x1b[33m Main Menu"; // The library automatically appends the closing " ---"

    menu.setTitle(newTitle);
}

bool loadDictionary(RBT& tree, const std::string& filename) {
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cout << COLOR_RED << "Warning: Could not open '" << filename << "'.\n" << COLOR_RESET;
        std::cout << "Starting with an empty dictionary.\n";
        return false;
    }

    std::string word;
    int count = 0;
    while (std::getline(file, word)) {
        // Remove potential carriage returns from Windows text files
        if (!word.empty() && word.back() == '\r') {
            word.pop_back();
        }

        if (!word.empty()) {
            tree.insert(word);
            count++;
        }
    }

    std::cout << COLOR_GREEN << "Dictionary loaded successfully!\n" << COLOR_RESET;
    std::cout << COLOR_ORANGE << "Loaded " << count << " words.\n" << COLOR_RESET;
    return count > 0;
}

void insertWordMenu(RBT& tree, const std::string& filename, Menu& menu) {
    std::cout << COLOR_YELLOW << "Enter a word to insert: " << COLOR_RESET;
    std::string word;
    std::cin >> word;

    // Requirement: Check if it already exists
    if (tree.search(word)) {
        std::cout << "\n" << COLOR_RED << "ERROR: Word already in the dictionary!\n" << COLOR_RESET;
    } else {
        // Insert into tree
        tree.insert(word);

        // Append to the actual dictionary text file
        std::ofstream file(filename, std::ios::app);
        if (file.is_open()) {
            file << word << "\n";
        } else {
            std::cout << COLOR_RED << "Warning: Could not save word to file.\n" << COLOR_RESET;
        }

        std::cout << "\n" << COLOR_GREEN << "Word inserted successfully!\n\n" << COLOR_RESET;

        // Requirement: Print size, height, and black height after insertion
        std::cout << COLOR_CYAN << "--- Tree Statistics After Insertion ---\n" << COLOR_RESET;
        std::cout << COLOR_ORANGE << "Dictionary Size: " << COLOR_RESET << tree.getSize() << "\n";
        std::cout << COLOR_ORANGE << "Tree Height:     " << COLOR_RESET << tree.getTreeHeight() << "\n";
        std::cout << COLOR_ORANGE << "Black Height:    " << COLOR_RESET << tree.checkValidity() << "\n";

        // Update the main menu header so the changes are visible when we return!
        updateMenuHeader(menu, tree, true);
    }

    menu.pause();
}

void lookupWordMenu(RBT& tree, Menu& menu) {
    std::cout << COLOR_YELLOW << "Enter a word to look up: " << COLOR_RESET;
    std::string word;
    std::cin >> word;

    // Requirement: Print YES or NO
    if (tree.search(word)) {
        std::cout << "\n" << COLOR_GREEN << "YES\n" << COLOR_RESET;
    } else {
        std::cout << "\n" << COLOR_RED << "NO\n" << COLOR_RESET;
    }

    menu.pause();
}