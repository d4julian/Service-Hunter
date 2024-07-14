#ifndef SERVICEHUNTER_MAINWINDOW_H
#define SERVICEHUNTER_MAINWINDOW_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

class MainWindow {
public:
        MainWindow();
        void run();
        struct Services
                {
            std::string Name;
            std::string Description;
            int rating;
                };
private:

    int page;

    sf::RenderWindow Window;

    sf::Font Font;

    sf::RectangleShape ServiceNodes;

    std::vector<Services> ServicesList;

    std::vector<sf::RectangleShape> UI;
    std::vector<sf::Text> UIText;

    std::vector<sf::RectangleShape> Objects;
    std::vector<sf::Text> Texts;

    void Events();
    void Draw();
    void Services();
    //void LoadServices();

};


#endif //SERVICEHUNTER_MAINWINDOW_H
