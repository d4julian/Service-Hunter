#ifndef SERVICEHUNTER_MAINWINDOW_H
#define SERVICEHUNTER_MAINWINDOW_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "Service.h"

class MainWindow {
public:
        MainWindow();
        void run();
private:
    std::vector<Service> services;

    std::string state;

    int page;

    sf::RenderWindow Window;

    sf::Font Font;

    sf::RectangleShape ServiceNodes;

    std::vector<sf::RectangleShape> UI;
    std::vector<sf::Text> UIText;

    std::vector<sf::RectangleShape> Objects;
    std::vector<sf::Text> Texts;

    std::vector<sf::RectangleShape> ServiceView;
    std::vector<sf::Text> ServiceText;

    void OpenService(int index);
    void Events();
    void Draw();
    void Services();
    //void LoadServices();

};


#endif //SERVICEHUNTER_MAINWINDOW_H
