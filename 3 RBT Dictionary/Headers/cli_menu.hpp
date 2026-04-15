#ifndef CLI_MENU
#define CLI_MENU

#include <string>
#include <vector>
#include <functional>

// Modern cross-platform ANSI Color Codes matching the C CLI
namespace Color {
    const std::string RESET   = "\033[0m";
    const std::string BOLD    = "\033[1m";
    const std::string RED     = "\033[31m";
    const std::string GREEN   = "\033[32m";
    const std::string YELLOW  = "\033[33m";
    const std::string BLUE    = "\033[34m";
    const std::string MAGENTA = "\033[35m";
    const std::string CYAN    = "\033[36m";
    const std::string WHITE   = "\033[37m";
    const std::string ORANGE  = "\033[38;2;255;103;0m"; // Custom RGB orange matching your original C files
}

/**
 * Type definition for a menu action using C++ std::function.
 * This allows passing regular functions, class methods, or inline lambdas.
 */
typedef std::function<void()> MenuAction;

/**
 * Represents a single selectable item in the menu.
 */
struct MenuItem {
    std::string text;
    MenuAction action;
    bool isExit;
};

/**
 * The main Menu class that handles rendering, input, and execution.
 */
class Menu {
private:
    std::string title;
    std::string projectName;
    std::string subjectName;
    int currentSelection;

    std::vector<MenuItem> items;
    std::vector<std::string> teamMembers;

    // Internal helpers
    void printBoilerplate() const;
    void display() const;
    bool confirmExit() const;

public:
    // Constructor
    Menu(const std::string& title, const std::string& projectName, const std::string& subjectName);

    // --- Modularity Functions ---
    void clearItems();
    void setTitle(const std::string& newTitle);
    void setProjectName(const std::string& newProjectName);

    // Add options to the menu
    void addItem(const std::string& text, MenuAction action);
    void addExitItem(const std::string& text);

    // Add a team member dynamically to the right column
    void addTeamMember(const std::string& memberInfo);

    // Starts the interactive menu loop
    void run();

    // Cross-platform pause utility
    void pause() const;
};

void enableWindowsColors();

#endif // CLI_MENU