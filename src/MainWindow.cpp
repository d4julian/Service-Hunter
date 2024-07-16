#include "MainWindow.h"
#include "Database.h"
#include <filesystem>
#include <sstream>

MainWindow::MainWindow()
{
    checkFiles();

    auto future = std::async(std::launch::async, []() {
        Database database;
        return database.getServices();
    });

    Window.create(sf::VideoMode(1200, 800), "Service Hunter");

    // Use the absolute path for the font file
    std::string fontPath = "assets/Arial.ttf";
    if (!Font.loadFromFile(fontPath)) {
        std::cerr << "Failed to load font " << fontPath << std::endl;
        exit(1);
    } else {
        std::cout << "Successfully loaded font " << fontPath << std::endl;
    }

    page = 1;
    state = "Main";

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

    services = future.get();
    for (int i = 0; i < services.size(); i++) {
        string fileName = services[i].title;
        std::transform(fileName.begin(), fileName.end(), fileName.begin(), ::tolower);
        std::replace(fileName.begin(), fileName.end(), ' ', '_');
        
        if (!services[i].texture.loadFromFile("assets/" + fileName + ".png")) std::cerr << "Could not load texture: " << fileName << endl;
    }
}

void MainWindow::checkFiles() {
    // Print the current working directory
    std::cout << "Current working directory: " << std::filesystem::current_path() << std::endl;

    // Use the absolute path for the font file
    //IMPORTANT : MAKE SURE YOU PUT YOUR OWN PATH
    std::string fontPath = "assets/Arial.ttf";
    if (!Font.loadFromFile(fontPath)) {
        std::cerr << "Failed to load font " << fontPath << std::endl;
        exit(1);
    } else {
        std::cout << "Successfully loaded font " << fontPath << std::endl;
    }

    // Absolute path for the password file
    //IMPORTANT : MAKE SURE YOU PUT YOUR OWN PATH
    std::string passwordPath = "./db_password.txt";
    std::cout << "Absolute path for password file: " << passwordPath << std::endl;

    std::ifstream passwordFile(passwordPath);
    if (!passwordFile.is_open()) {
        std::cerr << "Unable to open password file " << passwordPath << std::endl;
        exit(1);
    } else {
        std::cout << "Successfully opened password file " << passwordPath << std::endl;
    }
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
    sf::Color backgroundColor(231, 231, 231); // Set the background color to match the icon background
    Window.clear(backgroundColor);

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
        for (auto& icon : Icons)
        {
            Window.draw(icon);
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
    // Clear previous objects and texts
    Objects.clear();
    Texts.clear();
    Icons.clear();

    // Set the background color to match the icon background
    sf::Color backgroundColor(231, 231, 231);

    for (int i = 1; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            int index = page*(4*(i-1)+j);

            sf::RectangleShape ServiceNode;
            ServiceNode.setSize(sf::Vector2f(250, 150));
            ServiceNode.setPosition(25 + (j * 300), (i * 180));
            ServiceNode.setFillColor(backgroundColor); // Set the fill color to match the background color
            ServiceNode.setOutlineColor(sf::Color::Black);
            ServiceNode.setOutlineThickness(2);
            Objects.push_back(ServiceNode);

            sf::Text ServiceName;
            ServiceName.setFont(Font);
            ServiceName.setCharacterSize(18);
            ServiceName.setPosition(30 + (j * 300), (i * 180));
            ServiceName.setFillColor(sf::Color::Black);
            // Wrap the text if it exceeds a certain length
            std::string title = services[index].title;
            if (title.length() > 20) {
                title = title.substr(0, 17) + "...";
            }
            ServiceName.setString(title);
            Texts.push_back(ServiceName);

            sf::Text ServiceDescription;
            ServiceDescription.setFont(Font);
            ServiceDescription.setCharacterSize(14);
            ServiceDescription.setPosition(30 + (j * 300), (i * 180) + 30);
            ServiceDescription.setFillColor(sf::Color::Black);
            // Wrap the text if it exceeds a certain length
            std::string description = services[index].description;
            ServiceDescription.setString(wrapText(description, 240, Font, 14));
            Texts.push_back(ServiceDescription);

            sf::Text ServiceRating;
            ServiceRating.setFont(Font);
            ServiceRating.setCharacterSize(14);
            ServiceRating.setPosition(190 + (j * 300), (i * 180));
            ServiceRating.setFillColor(sf::Color::Black);
            ServiceRating.setString("Rating: " + std::to_string(services[index].rating));
            Texts.push_back(ServiceRating);

            // Set icon position and add to icons vector
            sf::Sprite iconSprite;
            iconSprite.setTexture(services[index].texture);

            // Adjust these values to make the icons larger and positioned slightly lower
            sf::Vector2f targetSize(70.0f, 70.0f); // Slightly larger size for the icons
            sf::Vector2f textureSize = static_cast<sf::Vector2f>(iconSprite.getTexture()->getSize());
            iconSprite.setScale(targetSize.x / textureSize.x, targetSize.y / textureSize.y);

            // Center the icon within the box and position it slightly lower
            float iconX = 25 + (j * 300) + (250 - targetSize.x) / 2;
            float iconY = (i * 180) + 70; // Increase this value to move the icon lower within the box
            iconSprite.setPosition(iconX, iconY);

            Icons.push_back(iconSprite);
        }
    }
}


std::string MainWindow::wrapText(const std::string &text, float width, const sf::Font &font, unsigned int characterSize)
{
    std::istringstream words(text);
    std::string word;
    std::string wrappedText;
    std::string line;

    while (words >> word)
    {
        sf::Text temp(line + " " + word, font, characterSize);
        if (temp.getLocalBounds().width > width)
        {
            if (!line.empty())
            {
                wrappedText += line + "\n";
                line.clear();
            }
        }
        if (!line.empty())
        {
            line += " ";
        }
        line += word;
    }
    if (!line.empty())
    {
        wrappedText += line;
    }
    return wrappedText;
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
