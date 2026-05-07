#ifndef CLI_MENU_HPP
#define CLI_MENU_HPP

#include <string>
#include <vector>
#include <functional>

// Define the type for our menu actions
using MenuAction = std::function<void()>;

// Structure to hold each menu item's data
struct MenuItem {
    std::string text;
    MenuAction action;
    bool isExit;
    bool showRepeatPrompt; // New flag to control the loop behavior
};

class Menu {
private:
    std::string title;
    std::string projectName;
    std::string subjectName;
    std::vector<MenuItem> items;
    std::vector<std::string> teamMembers;
    int currentSelection;

    void printBoilerplate() const;
    void display() const;
    bool confirmExit() const;

public:
    Menu(const std::string& title, const std::string& projectName, const std::string& subjectName);

    void clearItems();
    void setTitle(const std::string& newTitle);
    void setProjectName(const std::string& newProjectName);

    // Updated to accept the showRepeatPrompt flag (defaults to true for backwards compatibility)
    void addItem(const std::string& text, MenuAction action, bool showRepeatPrompt = true);

    void addExitItem(const std::string& text);
    void addTeamMember(const std::string& memberInfo);

    void run();
    void pause() const;
};

// Global helper function
void enableWindowsColors();

#endif // CLI_MENU_HPP