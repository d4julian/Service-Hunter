#include "MainWindow.h"
#include "Database.h"

vector<Service> services;

MainWindow::MainWindow()
{
 
    auto future = std::async(std::launch::async, []() {
        Database database;
        return database.getServices();
    });
    // the window function will serve all of the UI functionality for the application

    Window.create(sf::VideoMode(1200, 800), "Service Hunter");
    Font.loadFromFile("assets/Arial.ttf");

    // the important part is making sure the state is correct for which operation, which is the main page

    page = 1;
    state = "Main";

    sf::Text Header;
    sf::RectangleShape HeaderBackground;

    sf::RectangleShape SearchButton;
    sf::Text SearchText;

    sf::Text Explore;

    Header.setFont(Font);

    // creating these objects is very time consuming and rather ugly, but here it all is

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

    // for the future implementation where we actually store all the services we have

    services = future.get();
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
    if (state == "Main")
    {
        while (Window.pollEvent(Event))
        {
            if (Event.type == sf::Event::Closed)
            {
                Window.close();
            }
            else if (Event.type == sf::Event::MouseButtonPressed)
            {
                if (Event.mouseButton.button == sf::Mouse::Left)
                {
                    // First we want to get the position of the click
                    sf::Vector2i clickPosition = sf::Mouse::getPosition(Window);

                    // And now we are going to check if the click was inside any of the objects
                    for (unsigned int i = 0; i < Objects.size(); ++i)
                    {
                        if (Objects[i].getGlobalBounds().contains(clickPosition.x, clickPosition.y))
                        {
                            OpenService(i);
                            break;
                        }
                    }
                    if (UI[1].getGlobalBounds().contains(clickPosition.x, clickPosition.y) && UIText[1].getString() == "Search Services")
                    {
                        UIText[1].setString("");
                    }
                }
            }
            else if (Event.type == sf::Event::TextEntered)
            {
                if (Event.text.unicode < 128)
                {
                    if (Event.text.unicode != 8)
                    {
                        UIText[1].setString(UIText[1].getString() + Event.text.unicode);
                    }
                }

            }
            else if (Event.type == sf::Event::KeyPressed)
            {
                if (Event.key.code == sf::Keyboard::BackSpace)
                {
                    std::string text = UIText[1].getString();
                    if (!text.empty())
                    {
                        text.erase(text.size() - 1, 1);
                        UIText[1].setString(text);
                    }
                }
                if (Event.key.code == sf::Keyboard::Enter)
                {
                    // Implementation for the search yet to be done
                }
            }
        }
    }
    else if (state == "Service")
    {
        while (Window.pollEvent(Event))
        {
            if (Event.type == sf::Event::Closed)
            {
                Window.close();
            }
            else if (Event.type == sf::Event::MouseButtonPressed)
            {
                if (Event.mouseButton.button == sf::Mouse::Left)
                {
                    sf::Vector2i clickPosition = sf::Mouse::getPosition(Window);
                    for (unsigned int i = 0; i < ServiceView.size(); ++i)
                    {
                        if (ServiceView[i].getGlobalBounds().contains(clickPosition.x, clickPosition.y))
                        {
                            if (i == 1)
                            {
                                state = "Main";
                                ServiceView.clear();
                                ServiceText.clear();
                            }
                            break;
                        }
                    }
                }
            }
        }
    }
}

void MainWindow::Draw()
{
    Window.clear(sf::Color::White);
    if (state == "Main")
    {
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
    if (state == "Service")
    {
        for (sf::RectangleShape Shape : ServiceView)
        {
            Window.draw(Shape);
        }
        for (sf::Text Text : ServiceText)
        {
            Window.draw(Text);
        }
        Window.display();
    }
}

void MainWindow::Services()
{
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
            ServiceName.setString(services[page*(4*(i-1)+j)].title);
            ServiceName.setCharacterSize(24);
            ServiceName.setPosition(30 + (j * 300), (i * 180));
            ServiceName.setFillColor(sf::Color::Black);
            Texts.push_back(ServiceName);

            sf::Text ServiceDescription;
            ServiceDescription.setFont(Font);
            ServiceDescription.setString(services[page*(4*(i-1)+j)].description);
            ServiceDescription.setCharacterSize(20);
            ServiceDescription.setPosition(30 + (j * 300), (i * 180) + 30);
            ServiceDescription.setFillColor(sf::Color::Black);
            Texts.push_back(ServiceDescription);

            sf::Text ServiceRating;
            ServiceRating.setFont(Font);
            ServiceRating.setString("Rating: " + std::to_string(services[page*(4*(i-1)+j)].rating));
            ServiceRating.setCharacterSize(20);
            ServiceRating.setPosition(190 + (j * 300), (i * 180));
            ServiceRating.setFillColor(sf::Color::Black);
            Texts.push_back(ServiceRating);
        }
    }
}

void MainWindow::OpenService(int index)
{
    state = "Service";
    sf::Text Header;
    sf::RectangleShape HeaderBackground;

    Header.setFont(Font);

    Header.setString(services[index].title);
    Header.setCharacterSize(48);
    Header.setPosition(20, 10);
    Header.setFillColor(sf::Color::White);
    Header.setOutlineColor(sf::Color::Black);
    Header.setOutlineThickness(1);
    ServiceText.push_back(Header);

    sf::Color Logo(137, 207, 240);
    HeaderBackground.setSize(sf::Vector2f(1200, 80));
    HeaderBackground.setPosition(0, 0);
    HeaderBackground.setFillColor(Logo);
    ServiceView.push_back(HeaderBackground);

    sf::Text Description;
    Description.setFont(Font);
    Description.setString(services[index].description);
    Description.setCharacterSize(36);
    Description.setPosition(20, 100);
    Description.setFillColor(sf::Color::Black);
    ServiceText.push_back(Description);

    sf::Text Rating;
    Rating.setFont(Font);
    Rating.setString("Rating: " + std::to_string(services[index].rating));
    Rating.setCharacterSize(36);
    Rating.setPosition(20, 200);
    Rating.setFillColor(sf::Color::Black);
    ServiceText.push_back(Rating);

    sf::RectangleShape BackButton;
    BackButton.setSize(sf::Vector2f(200, 40));
    BackButton.setPosition(20, 700);
    BackButton.setFillColor(sf::Color::White);
    BackButton.setOutlineColor(sf::Color::Black);
    BackButton.setOutlineThickness(2);
    ServiceView.push_back(BackButton);

    sf::Text BackText;
    BackText.setFont(Font);
    BackText.setString("Back");
    BackText.setCharacterSize(24);
    BackText.setPosition(30, 705);
    BackText.setFillColor(sf::Color::Black);
    ServiceText.push_back(BackText);
}