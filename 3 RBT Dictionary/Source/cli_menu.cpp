#include "../Headers/cli_menu.hpp"
#include <iostream>
#include <string>
#include <vector>
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

// Internal helper to print the dynamic, perfectly aligned boilerplate with target UI colors
void Menu::printBoilerplate() const {
    // Build the Left Column texts and colors
    std::vector<std::string> leftLines = {
        "<Mohsen Amr - 9655>",
        subjectName
    };
    std::vector<std::string> leftColors = {
        "\x1b[96m", // Turquoise
        "\x1b[94m"  // Blue
    };

    // Build the Right Column texts and colors
    std::vector<std::string> rightLines;
    std::vector<std::string> rightColors;

    for (const auto& member : teamMembers) {
        rightLines.push_back("<" + member + ">");
        rightColors.push_back("\x1b[96m"); // Turquoise for names
    }

    // Align project name with subjectName
    if (rightLines.empty()) {
        rightLines.push_back("");
        rightColors.push_back("");
    }

    rightLines.push_back("[" + projectName + "]");
    rightColors.push_back("\x1b[94m"); // Blue for project name

    size_t maxLines = std::max(leftLines.size(), rightLines.size());

    std::cout << "\n";
    for (size_t i = 0; i < maxLines; ++i) {
        std::string lText = (i < leftLines.size()) ? leftLines[i] : "";
        std::string lColor = (i < leftColors.size()) ? leftColors[i] : "";

        std::string rText = (i < rightLines.size()) ? rightLines[i] : "";
        std::string rColor = (i < rightColors.size()) ? rightColors[i] : "";

        // Print left side with color
        std::cout << lColor << lText << "\x1b[0m";

        // Manual spacing calculation (fixes std::setw bugs with ANSI codes)
        int spaces = 40 - lText.length();
        if (spaces > 0) {
            std::cout << std::string(spaces, ' ');
        }

        // Print right side with color
        std::cout << rColor << rText << "\x1b[0m\n";
    }
    std::cout << "\n";
}

// Internal helper to display the menu options
void Menu::display() const {
    system("cls"); // Clear screen to redraw cleanly

    printBoilerplate();

    // Only print the title if it isn't empty (useful for entirely custom sub-menus)
    if (!title.empty()) {
        std::cout << "\x1b[33m --- " << title << " ---\x1b[0m\n\n"; // Yellow title
    }

    for (size_t i = 0; i < items.size(); ++i) {
        if (static_cast<int>(i) == currentSelection) {
            // Highlighted item (White Background, Black Text)
            std::cout << "\x1b[47;30m" << items[i].text << "\x1b[0m\n";
        } else {
            // Normal item (Unselected)
            std::cout << items[i].text << "\n";
        }
    }
}

// Confirm Exit logic perfectly mirroring HW5 exit animation
bool Menu::confirmExit() const {
    system("cls");
    printBoilerplate();

    std::cout << "\x1b[33mAre you sure you want to exit the program? (Y/N)\n\x1b[31m>>\x1b[0m ";

    while (true) {
        char ch = std::toupper(_getch());
        if (ch == 'Y') {
            // Exact 3-loop exit animation from HW5
            for (int k = 0; k < 3; k++) {
                system("cls");
                std::cout << "\x1b[94mGoodbye!\x1b[0m\n\n";
                std::cout << "\x1b[31mExiting program";
                for (int i = 0; i < 3; i++) {
                    std::cout << ".";
                    Sleep(300);
                }
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
                if (selectedItem.action) {
                    system("cls");
                    printBoilerplate(); // Inject boilerplate into every sub-page!

                    // Print a header for the specific action being performed
                    std::cout << "\x1b[33m --- " << selectedItem.text << " ---\x1b[0m\n\n";

                    selectedItem.action();
                }
            }
        } else if (ch >= '1' && ch <= '0' + static_cast<int>(items.size())) {
            // Numeric shortcut keys
            currentSelection = ch - '1';
        }
    }
}

// Cross-platform pause function
void Menu::pause() const {
    std::cout << "\n\x1b[33mPress any key to return to the menu...\x1b[0m";
    _getch();
}

void enableWindowsColors() {
#ifdef _WIN32
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hOut != INVALID_HANDLE_VALUE) {
        DWORD dwMode = 0;
        if (GetConsoleMode(hOut, &dwMode)) {
            dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
            SetConsoleMode(hOut, dwMode);
        }
    }
#endif
}