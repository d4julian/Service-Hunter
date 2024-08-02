#ifndef SERVICEHUNTER_MAINWINDOW_H
#define SERVICEHUNTER_MAINWINDOW_H

#include <SFML/Graphics.hpp>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <future>
#include "Service.h"

class MainWindow {
public:
    MainWindow();
    void run();

private:
    std::vector<Service> services;
    std::string state;
    int page;

    sf::Vector2u WindowSize;
    int height;
    int width;

    std::string currentUser, currentPass;

    bool first;

    sf::RenderWindow Window;
    sf::Font Font;
    sf::RectangleShape ServiceNodes;

    std::vector<sf::RectangleShape> Login;
    std::vector<sf::Text> LoginText;

    std::vector<sf::RectangleShape> LoginView;
    std::vector<sf::Text> LoginViewText;
    bool loggedin = false;

    sf::Text *Selection;

    std::vector<sf::RectangleShape> UI;
    std::vector<sf::Text> UIText;
    std::vector<sf::RectangleShape> Objects;
    std::vector<sf::Text> Texts;
    std::vector<sf::Sprite> Icons; // For icons
    std::vector<sf::RectangleShape> ServiceView;
    std::vector<sf::Text> ServiceText;

    void login();
    void OpenService(int index);
    void BuildUI();
    void Events();
    void Draw();
    void Services(std::vector<std::reference_wrapper<Service>>& servicesToShow);
    void checkFiles();
    std::string wrapText(const std::string &text, float width, const sf::Font &font, unsigned int characterSize);

    std::string ltrim(const std::string& s) {
        size_t start = s.find_first_not_of(" \t\n\r\f\v");
        return (start == std::string::npos) ? "" : s.substr(start);
    }
    std::string rtrim(const std::string& s) {
        size_t end = s.find_last_not_of(" \t\n\r\f\v");
        return (end == std::string::npos) ? "" : s.substr(0, end + 1);
    }
    std::string trim(const std::string& s) {
        return rtrim(ltrim(s));
    }

    void PerformSearch(const std::string& query);

};

#endif //SERVICEHUNTER_MAINWINDOW_H
