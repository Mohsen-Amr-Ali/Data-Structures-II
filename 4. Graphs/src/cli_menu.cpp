#include "cli_menu.hpp"
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

// Add a standard functional option (Updated with showRepeatPrompt)
void Menu::addItem(const std::string& text, MenuAction action, bool showRepeatPrompt) {
    items.push_back({text, action, false, showRepeatPrompt});
}

// Add an exit option - intercepts and enforces the 91m (bright red) color!
void Menu::addExitItem(const std::string& text) {
    std::string modifiedText = text;
    size_t pos = modifiedText.find("\x1b[31m");
    if (pos != std::string::npos) {
        modifiedText.replace(pos, 5, "\x1b[91m");
    }
    items.push_back({modifiedText, nullptr, true, false});
}

// Add a team member dynamically
void Menu::addTeamMember(const std::string& memberInfo) {
    teamMembers.push_back(memberInfo);
}

// Internal helper to print the dynamic, perfectly aligned boilerplate with margins
void Menu::printBoilerplate() const {
    std::string m = "  "; // 2-space margin to prevent hugging the left border
    int col_width = 35;   // Fixed column width for perfect vertical alignment

    // First Row: Names (3 columns)
    std::cout << "\n" << m << "\x1b[96m<Mohsen Amr - 9655>";
    int space1 = col_width - 19; // 19 is length of "<Mohsen Amr - 9655>"
    if (space1 > 0) std::cout << std::string(space1, ' ');

    if (teamMembers.size() > 0) {
        std::string member1 = "<" + teamMembers[0] + ">";
        std::cout << member1;
        if (teamMembers.size() > 1) {
            int space2 = col_width - member1.length();
            if (space2 > 0) std::cout << std::string(space2, ' ');
            std::cout << "<" << teamMembers[1] << ">";
        }
    }
    std::cout << "\x1b[0m\n";

    // Second Row: Subject and Project Name perfectly aligned under Student 1 & 2
    std::cout << m << "\x1b[94m" << subjectName;
    int space3 = col_width - subjectName.length();
    if (space3 > 0) std::cout << std::string(space3, ' ');
    std::cout << "[" << projectName << "]\x1b[0m\n\n";
}

// Internal helper to display the menu options
void Menu::display() const {
    system("cls"); // Clear screen to redraw cleanly

    printBoilerplate();
    std::string m = "  ";

    if (!title.empty()) {
        std::string displayTitle = title;

        // Inject margin into the title string cleanly, respecting the \r reset
        size_t pos = displayTitle.find("\r\x1b[K");
        if (pos != std::string::npos) {
            displayTitle.insert(pos + 4, m);
        } else {
            displayTitle = m + displayTitle;
        }

        // Add margin to subsequent lines in the title
        pos = 0;
        while ((pos = displayTitle.find('\n', pos)) != std::string::npos) {
            if (pos + 1 < displayTitle.length() && displayTitle[pos + 1] != '\n') {
                displayTitle.insert(pos + 1, m);
                pos += m.length();
            }
            pos++;
        }

        std::cout << displayTitle << "\n\n";
    }

    for (size_t i = 0; i < items.size(); ++i) {
        if (static_cast<int>(i) == currentSelection) {
            // Highlighted item (White Background, Black Text)
            std::cout << m << "\x1b[47;30m" << items[i].text << "\x1b[0m\n";
        } else {
            // Normal item (Unselected)
            std::cout << m << items[i].text << "\n";
        }
    }
}

// Confirm Exit logic perfectly mirroring HW5 exit animation (using 91m red)
bool Menu::confirmExit() const {
    system("cls");
    printBoilerplate();
    std::string m = "  ";

    std::cout << m << "\x1b[33mAre you sure you want to exit the program? (Y/N)\n" << m << "\x1b[91m>>\x1b[0m ";

    while (true) {
        char ch = std::toupper(_getch());
        if (ch == 'Y') {
            // Exact 3-loop exit animation
            for (int k = 0; k < 3; k++) {
                system("cls");
                std::cout << "\n" << m << "\x1b[94mGoodbye!\x1b[0m\n\n";
                std::cout << m << "\x1b[91mExiting program";
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
    std::string m = "  ";

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
                    bool repeatAction = false;
                    do {
                        system("cls");
                        printBoilerplate(); // Inject boilerplate into every sub-page!

                        std::string header = selectedItem.text;
                        size_t pos = header.find(") ");
                        if (pos != std::string::npos) {
                            header = header.substr(pos + 2);
                        }
                        std::cout << m << "\x1b[33m" << header << "\x1b[0m\n\n";

                        selectedItem.action();

                        // Only show the repeat prompt if the flag is true
                        if (selectedItem.showRepeatPrompt) {
                            std::string activity = header;
                            for (char& c : activity) c = std::tolower(c);
                            size_t a_pos = activity.find("a ");
                            if (a_pos != std::string::npos) {
                                activity.replace(a_pos, 2, "another ");
                            } else {
                                activity += " again";
                            }

                            std::cout << "\n" << m << "\x1b[33mDo you want to " << activity << "? (Y for yes)\x1b[0m ";
                            char chRepeat = std::toupper(_getch());
                            if (chRepeat == 'Y') {
                                repeatAction = true;
                            } else {
                                repeatAction = false;
                            }
                        } else {
                            repeatAction = false; // Exit loop automatically if flag is false
                        }

                    } while (repeatAction);
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
    // Intentionally left blank.
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