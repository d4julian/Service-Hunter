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

    std::string currentUser;

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
    void Services();
    void checkFiles();
    std::string wrapText(const std::string &text, float width, const sf::Font &font, unsigned int characterSize);
};

#endif //SERVICEHUNTER_MAINWINDOW_H
