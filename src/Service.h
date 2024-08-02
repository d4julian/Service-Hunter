#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;

class Service {
public:
    int id, rating;
    string title, description, longDescription, provider;
    float cost;
    sf::Texture texture;
    sf::Sprite icon;
    bool visible = false;
    Service(int id, string provider, const string& title, const string& description, const string& longDescription, int rating, float cost) : 
        id(id), provider(provider), title(title), description(description), longDescription(longDescription), rating(rating), cost(cost) {}
};