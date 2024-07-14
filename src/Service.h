#pragma once
#include <iostream>

using namespace std;

class Service {
    int id, rating, provider;
    string title, description;
    float rating, cost;
    Service(int id, int provider, const string& title, const string& description, float rating, float cost) : 
        id(id), provider(provider), title(title), description(description), rating(rating), cost(cost) {}
};