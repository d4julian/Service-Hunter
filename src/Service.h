#pragma once
#include <iostream>

using namespace std;

class Service {
public:
    int id, rating;
    string title, description, provider;
    float cost;
    Service(int id, string provider, const string& title, const string& description, int rating, float cost) : 
        id(id), provider(provider), title(title), description(description), rating(rating), cost(cost) {}
};