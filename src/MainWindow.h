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
    sf::RenderWindow Window;
    sf::Font Font;
    sf::RectangleShape ServiceNodes;

    std::vector<sf::RectangleShape> UI;
    std::vector<sf::Text> UIText;
    std::vector<sf::RectangleShape> Objects;
    std::vector<sf::Text> Texts;
    std::vector<sf::Sprite> Icons; // For icons
    std::vector<sf::RectangleShape> ServiceView;
    std::vector<sf::Text> ServiceText;

    // Textures and sprites for icons
    sf::Texture plumbingTexture, haircutTexture, acRepairTexture, houseCleaningTexture;
    sf::Texture makeupArtistTexture, electricianTexture, gardeningTexture, carRepairTexture;
    sf::Texture dogWalkingTexture, yogaInstructorTexture, personalTrainerTexture, computerRepairTexture;
    sf::Sprite plumbingSprite, haircutSprite, acRepairSprite, houseCleaningSprite;
    sf::Sprite makeupArtistSprite, electricianSprite, gardeningSprite, carRepairSprite;
    sf::Sprite dogWalkingSprite, yogaInstructorSprite, personalTrainerSprite, computerRepairSprite;

    void OpenService(int index);
    void Events();
    void Draw();
    void Services();
    void checkFiles();
    std::string wrapText(const std::string &text, float width, const sf::Font &font, unsigned int characterSize);
};

#endif //SERVICEHUNTER_MAINWINDOW_H
