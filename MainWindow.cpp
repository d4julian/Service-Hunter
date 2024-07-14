#include "MainWindow.h"

MainWindow::MainWindow()
{
    Window.create(sf::VideoMode(1200, 800), "Service Hunter");
    Font.loadFromFile("Arial.ttf");

    page = 0;

    sf::Text Header;
    sf::RectangleShape HeaderBackground;

    sf::RectangleShape SearchButton;
    sf::Text SearchText;

    sf::Text Explore;

    Header.setFont(Font);

    Header.setString("Service Hunter");
    Header.setCharacterSize(48);
    Header.setPosition(20, 10);
    Header.setFillColor(sf::Color::White);
    Header.setOutlineColor(sf::Color::Black);
    Header.setOutlineThickness(1);
    UIText.push_back(Header);

    sf::Color Logo(137, 207, 240);
    HeaderBackground.setSize(sf::Vector2f(1200, 80));
    HeaderBackground.setPosition(0, 0);
    HeaderBackground.setFillColor(Logo);
    UI.push_back(HeaderBackground);

    SearchButton.setSize(sf::Vector2f(500, 40));
    SearchButton.setPosition(400, 20);
    SearchButton.setFillColor(sf::Color::White);
    SearchButton.setOutlineColor(sf::Color::Black);
    SearchButton.setOutlineThickness(2);
    UI.push_back(SearchButton);

    sf::Color Search(105, 105, 105);
    SearchText.setFont(Font);
    SearchText.setString("Search Services");
    SearchText.setCharacterSize(24);
    SearchText.setPosition(410, 25);
    SearchText.setFillColor(Search);
    UIText.push_back(SearchText);

    Explore.setFont(Font);
    Explore.setString("Explore Our Quality Services");
    Explore.setCharacterSize(36);
    Explore.setPosition(20, 100);
    Explore.setFillColor(sf::Color::Black);
    UIText.push_back(Explore);

    //LoadServices();
}

void MainWindow::run() {
    while (Window.isOpen()) {
        Events();
        Draw();
    }
}

void MainWindow::Events()
{
    sf::Event Event;
    while (Window.pollEvent(Event))
    {
        if (Event.type == sf::Event::Closed)
        {
            Window.close();
        }
    }
}

void MainWindow::Draw()
{
    Window.clear(sf::Color::White);
    Services();
    for (sf::RectangleShape Shape : UI)
    {
        Window.draw(Shape);
    }
    for (sf::Text Text : UIText)
    {
        Window.draw(Text);
    }
    for (sf::RectangleShape Shape : Objects)
    {
        Window.draw(Shape);
    }
    for (sf::Text Text : Texts)
    {
        Window.draw(Text);
    }
    Window.display();
}

void MainWindow::Services()
{
    for (int i = 1; i < 13; i++)
    {
        struct MainWindow::Services Service;
        Service.Name = "Service " + std::to_string(i);
        Service.Description = "Description " + std::to_string(i);
        Service.rating = i%5;
        ServicesList.push_back(Service);
    }
    int starting = page*12;
    for (int i = 1; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            sf::RectangleShape ServiceNode;
            ServiceNode.setSize(sf::Vector2f(250, 150));
            ServiceNode.setPosition(25 + (j * 300), (i * 180));
            ServiceNode.setFillColor(sf::Color::White);
            ServiceNode.setOutlineColor(sf::Color::Black);
            ServiceNode.setOutlineThickness(2);
            Objects.push_back(ServiceNode);

            sf::Text ServiceName;
            ServiceName.setFont(Font);
            ServiceName.setString(ServicesList[4*(i-1)+j].Name);
            ServiceName.setCharacterSize(24);
            ServiceName.setPosition(30 + (j * 300), (i * 180));
            ServiceName.setFillColor(sf::Color::Black);
            Texts.push_back(ServiceName);

            sf::Text ServiceDescription;
            ServiceDescription.setFont(Font);
            ServiceDescription.setString(ServicesList[4*(i-1)+j].Description);
            ServiceDescription.setCharacterSize(20);
            ServiceDescription.setPosition(30 + (j * 300), (i * 180) + 30);
            ServiceDescription.setFillColor(sf::Color::Black);
            Texts.push_back(ServiceDescription);

            sf::Text ServiceRating;
            ServiceRating.setFont(Font);
            ServiceRating.setString("Rating: " + std::to_string(ServicesList[4*(i-1)+j].rating));
            ServiceRating.setCharacterSize(20);
            ServiceRating.setPosition(190 + (j * 300), (i * 180));
            ServiceRating.setFillColor(sf::Color::Black);
            Texts.push_back(ServiceRating);
        }
    }
}