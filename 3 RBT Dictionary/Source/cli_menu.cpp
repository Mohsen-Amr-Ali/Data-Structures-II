#include "../Headers/cli_menu.hpp"
#include <iostream>
#include <iomanip>    // For std::setw and std::left
#include <algorithm>  // For std::max
#include <conio.h>    // For _getch()
#include <windows.h>  // For Sleep() and system("cls")
#include <cctype>

// Key bindings perfectly matched from the C files
#define KEY_UP 72
#define KEY_DOWN 80
#define ENTER 13
#define ESC 27

// Constructor
Menu::Menu(const std::string& title, const std::string& projectName, const std::string& subjectName)
    : title(title), projectName(projectName), subjectName(subjectName), currentSelection(0) {}

// --- Modularity Functions ---
// Allows you to completely change the UI on the fly (e.g., for the Dictionary menu)
void Menu::clearItems() {
    items.clear();
    currentSelection = 0;
}

void Menu::setTitle(const std::string& newTitle) {
    title = newTitle;
}

void Menu::setProjectName(const std::string& newProjectName) {
    projectName = newProjectName;
}

// Add a standard functional option
void Menu::addItem(const std::string& text, MenuAction action) {
    items.push_back({text, action, false});
}

// Add an exit option
void Menu::addExitItem(const std::string& text) {
    items.push_back({text, nullptr, true});
}

// Add a team member dynamically
void Menu::addTeamMember(const std::string& memberInfo) {
    teamMembers.push_back(memberInfo);
}

// Internal helper to print the dynamic, perfectly aligned boilerplate
void Menu::printBoilerplate() const {
    // Build the Left Column
    std::vector<std::string> leftLines = {
        "<Mohsen Amr - 9655>",
        subjectName
    };

    // Build the Right Column
    std::vector<std::string> rightLines;
    for (const auto& member : teamMembers) {
        rightLines.push_back("<" + member + ">");
    }
    // If there are no extra members, insert an empty line so the project name aligns with subjectName
    if (rightLines.empty()) {
        rightLines.push_back("");
    }
    rightLines.push_back("[" + projectName + "]");

    size_t maxLines = std::max(leftLines.size(), rightLines.size());

    std::cout << "\n";
    for (size_t i = 0; i < maxLines; ++i) {
        std::string leftStr = (i < leftLines.size()) ? leftLines[i] : "";
        std::string rightStr = (i < rightLines.size()) ? rightLines[i] : "";

        // std::setw(40) guarantees the right column stays perfectly locked in place
        std::cout << std::left << std::setw(40) << leftStr << rightStr << "\n";
    }
    std::cout << "\n";
}

// Internal helper to display the menu options exactly like the C code
void Menu::display() const {
    system("cls"); // Clear screen to redraw cleanly

    printBoilerplate();

    // Only print the title if it isn't empty (useful for entirely custom sub-menus)
    if (!title.empty()) {
        std::cout << " --- " << title << " ---\n\n";
    }

    for (size_t i = 0; i < items.size(); ++i) {
        if (static_cast<int>(i) == currentSelection) {
            // Highlighted item perfectly matching your C projects (White Background, Black Text)
            std::cout << "\x1b[47;30m" << items[i].text << "\x1b[0m\n";
        } else {
            // Normal item
            std::cout << items[i].text << "\n";
        }
    }
}

// Confirm Exit logic perfectly mirroring HW5 - 9655.c
bool Menu::confirmExit() const {
    system("cls");
    // Exact colors and prompt from your C files (\x1b[33m for yellow, \x1b[31m for red)
    std::cout << "\x1b[33mAre you sure you want to exit the program? (Y/N)\n\x1b[31m>>\x1b[0m ";

    while (true) {
        char ch = std::toupper(_getch());
        if (ch == 'Y') {
            std::cout << "\n\x1b[31mExiting program";
            for (int i = 0; i < 3; i++) {
                std::cout << ".";
                Sleep(300); // The exact animated delay
            }
            std::cout << "\x1b[0m\n";
            return false; // Stop the main loop
        } else if (ch == 'N') {
            return true; // Continue the main loop
        }
    }
}

// The main interactive loop
void Menu::run() {
    bool running = true;
    while (running) {
        display();

        int ch = _getch();

        if (ch == 0xE0 || ch == 224) {
            // Arrow key prefix detected
            ch = _getch();
            if (ch == KEY_UP) {
                currentSelection = (currentSelection - 1 + items.size()) % items.size();
            } else if (ch == KEY_DOWN) {
                currentSelection = (currentSelection + 1) % items.size();
            }
        } else if (ch == ENTER) {
            const MenuItem& selectedItem = items[currentSelection];

            if (selectedItem.isExit) {
                running = confirmExit();
            } else {
                system("cls"); // Clear screen for the function's output

                if (selectedItem.action) {
                    selectedItem.action();
                }
            }
        } else if (ch >= '1' && ch <= '0' + static_cast<int>(items.size())) {
            // Numeric shortcut keys (matches your C logic)
            currentSelection = ch - '1';
        }
    }
}

// Cross-platform pause function
void Menu::pause() const {
    std::cout << "\n\x1b[33mPress any key to return to the menu...\x1b[0m";
    _getch();
}