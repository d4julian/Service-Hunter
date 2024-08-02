#include "MainWindow.h"
#include "Database.h"
#include <filesystem>
#include <sstream>
#include <algorithm> // Include algorithm for transform

Database database;

MainWindow::MainWindow()
{
    checkFiles();

    auto future = std::async(std::launch::async, []() { return database.getServices(); });

    bool full = true;

    int widt;
    int heigh;
    if (full)
    {
        widt = sf::VideoMode::getDesktopMode().width;
        heigh = sf::VideoMode::getDesktopMode().height;
    }
    else
    {
        widt = 1200;
        heigh = 800;
    }

    Window.create(sf::VideoMode(widt, heigh), "Service Hunter");

    std::string fontPath = "assets/Arial.ttf";
    if (!Font.loadFromFile(fontPath)) {
        std::cerr << "Failed to load font " << fontPath << std::endl;
        exit(1);
    } else {
        std::cout << "Successfully loaded font " << fontPath << std::endl;
    }

    page = 1;
    state = "Main";
    BuildUI();

    services = future.get();
    for (int i = 0; i < services.size(); i++) {
        std::string fileName = services[i].category;
        std::transform(fileName.begin(), fileName.end(), fileName.begin(), ::tolower);
        std::replace(fileName.begin(), fileName.end(), ' ', '_');

        if (!services[i].texture.loadFromFile("assets/" + fileName + ".png")) {
            std::cerr << "Could not load texture: " << fileName << std::endl;
        } else {
            sf::Sprite iconSprite;
            iconSprite.setTexture(services[i].texture);
            sf::Vector2f targetSize(70.0f, 70.0f);
            sf::Vector2f textureSize = static_cast<sf::Vector2f>(iconSprite.getTexture()->getSize());
            iconSprite.setScale(targetSize.x / textureSize.x, targetSize.y / textureSize.y);
            services[i].icon = iconSprite;
        }
    }

    // Display first 12 services initially
    std::vector<std::reference_wrapper<Service>> servicesReference;
    for (int i = 0; i < 12; i++) {
        servicesReference.push_back(std::ref(services[i]));
    }
    Services(servicesReference);
}

void MainWindow::BuildUI()
{
    sf::Vector2u size = Window.getSize();
    int w = size.x;
    int h = size.y;
    std::cout << w << " " << h << std::endl;
    if (w == width && h == height)
    {
        return;
    }

    width = w;
    height = h;

    std::string search = "Search Services";

    if (UIText.size() > 0)
    {
        int x = WindowSize.x;
        int y = WindowSize.y;
        float widthRatio = width / x;
        float heightRatio = height / y;
        for (auto item : UIText)
        {
            item.setCharacterSize(item.getCharacterSize() * std::min(heightRatio, widthRatio));
            item.setPosition(sf::Vector2f(x * widthRatio, y * heightRatio));
        }
        for (auto item : UI)
        {
            item.setSize(sf::Vector2f(x * widthRatio, y * heightRatio));
            item.setPosition(sf::Vector2f(x * widthRatio, y * heightRatio));
        }
        return;
    }

    sf::Vector2u baseSize(1200.0f, 800.0f);
    sf::Vector2u currentSize = Window.getSize();

    float widthScale = static_cast<float>(currentSize.x) / baseSize.x;
    float heightScale = static_cast<float>(currentSize.y) / baseSize.y;

    sf::Text Header;
    sf::RectangleShape HeaderBackground;

    sf::RectangleShape SearchButton;
    sf::Text SearchText;

    sf::Text Explore;

    Header.setFont(Font);
    Header.setString("Service Hunter");
    Header.setCharacterSize(48 * std::min(widthScale, heightScale));
    Header.setPosition(20 * widthScale, 10 * heightScale);
    Header.setFillColor(sf::Color::White);
    Header.setOutlineColor(sf::Color::Black);
    Header.setOutlineThickness(1);
    UIText.push_back(Header);

    sf::Color Logo(137, 207, 240);
    HeaderBackground.setSize(sf::Vector2f(1200 * widthScale, 80 * heightScale));
    HeaderBackground.setPosition(0, 0);
    HeaderBackground.setFillColor(Logo);
    UI.push_back(HeaderBackground);

    SearchButton.setSize(sf::Vector2f(500 * widthScale, 40 * heightScale));
    SearchButton.setPosition(400 * widthScale, 20 * heightScale);
    SearchButton.setFillColor(sf::Color::White);
    SearchButton.setOutlineColor(sf::Color::Black);
    SearchButton.setOutlineThickness(2);
    UI.push_back(SearchButton);

    sf::Color Search(105, 105, 105);
    SearchText.setFont(Font);
    SearchText.setString("Search Services");
    SearchText.setCharacterSize(24 * std::min(widthScale, heightScale));
    SearchText.setPosition(410 * widthScale, 25 * heightScale);
    SearchText.setFillColor(Search);
    UIText.push_back(SearchText);

    Explore.setFont(Font);
    Explore.setString("Explore Our Quality Services");
    Explore.setCharacterSize(36 * std::min(widthScale, heightScale));
    Explore.setPosition(20 * widthScale, 100 * heightScale);
    Explore.setFillColor(sf::Color::Black);
    UIText.push_back(Explore);

    sf::RectangleShape LoginButton;
    LoginButton.setSize(sf::Vector2f(100 * widthScale, 40 * heightScale));
    LoginButton.setPosition(1000 * widthScale, 20 * heightScale);
    LoginButton.setFillColor(sf::Color::White);
    LoginButton.setOutlineColor(sf::Color::Black);
    LoginButton.setOutlineThickness(2);
    Login.push_back(LoginButton);

    sf::Text LoginTex;
    LoginTex.setFont(Font);
    LoginTex.setString("Sign in");
    LoginTex.setCharacterSize(24 * std::min(widthScale, heightScale));
    LoginTex.setPosition(1015 * widthScale, 25 * heightScale);
    LoginTex.setFillColor(sf::Color::Black);
    LoginText.push_back(LoginTex);

    WindowSize = currentSize;
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


void MainWindow::run()
{
    while (Window.isOpen()) {
        Events();
        Draw();
    }
}

void MainWindow::Events() {
    sf::Event Event;
    if (state == "Main") {
        while (Window.pollEvent(Event)) {
            if (Event.type == sf::Event::Closed) {
                Window.close();
            } else if (Event.type == sf::Event::MouseButtonPressed) {
                if (Event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2i clickPosition = sf::Mouse::getPosition(Window);
                    sf::Vector2u windowSize = Window.getSize();
                    if (clickPosition.x >= 0 && clickPosition.x < windowSize.x
                        && clickPosition.y >= 0 && clickPosition.y < windowSize.y) {
                        Window.setActive(true);
                    }

                    for (unsigned int i = 0; i < Objects.size(); ++i) {
                        if (Objects[i].getGlobalBounds().contains(clickPosition.x, clickPosition.y)) {
                            OpenService(i);
                            break;
                        }
                    }
                    if (Login[0].getGlobalBounds().contains(clickPosition.x, clickPosition.y) && !loggedin) {
                        login();
                        break;
                    }
                    if (UI[1].getGlobalBounds().contains(clickPosition.x, clickPosition.y) &&
                        UIText[1].getString() == "Search Services") {
                        UIText[1].setString("");
                    }
                }
            } else if (Event.type == sf::Event::TextEntered) {
                if (Event.text.unicode < 128) {
                    if (Event.text.unicode != 8) {
                        UIText[1].setString(UIText[1].getString() + Event.text.unicode);
                    }
                }

            } else if (Event.type == sf::Event::KeyPressed) {
                if (Event.key.code == sf::Keyboard::BackSpace) {
                    std::string text = UIText[1].getString();
                    if (!text.empty()) {
                        text.erase(text.size() - 1, 1);
                        UIText[1].setString(text);
                    }
                }
                if (Event.key.code == sf::Keyboard::Enter) {
                    std::string query = UIText[1].getString();
                    PerformSearch(query); // Call a function to handle the search
                }
            } else if (Event.type == sf::Event::MouseMoved) {
                sf::Vector2i mousePosition = sf::Mouse::getPosition(Window);
                for (unsigned int i = 0; i < Objects.size(); ++i) {
                    if (Objects[i].getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
                        Objects[i].setOutlineColor(sf::Color::Red);
                        Window.draw(Objects[i]);
                    } else {
                        Objects[i].setOutlineColor(sf::Color::Black);
                        Window.draw(Objects[i]);
                    }
                }
                for (unsigned int i = 0; i < UI.size(); ++i) {
                    if (UI[i].getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
                        UI[i].setOutlineColor(sf::Color::Red);
                    } else {
                        UI[i].setOutlineColor(sf::Color::Black);
                    }
                }
                if (Login[0].getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
                    Login[0].setOutlineColor(sf::Color::Red);
                } else {
                    Login[0].setOutlineColor(sf::Color::Black);
                }
            }
        }
    } else if (state == "Service") {
        while (Window.pollEvent(Event)) {
            if (Event.type == sf::Event::Closed) {
                Window.close();
            } else if (Event.type == sf::Event::MouseButtonPressed) {
                if (Event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2i clickPosition = sf::Mouse::getPosition(Window);
                    for (unsigned int i = 0; i < ServiceView.size(); ++i) {
                        if (ServiceView[i].getGlobalBounds().contains(clickPosition.x, clickPosition.y)) {
                            if (i == 1) {
                                state = "Main";
                                ServiceView.clear();
                                ServiceText.clear();
                            }
                            break;
                        }
                    }
                }
            } else if (Event.type == sf::Event::MouseMoved) {
                sf::Vector2i mousePosition = sf::Mouse::getPosition(Window);
                for (unsigned int i = 0; i < ServiceView.size(); ++i) {
                    if (ServiceView[i].getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
                        ServiceView[i].setOutlineColor(sf::Color::Red);
                    } else {
                        ServiceView[i].setOutlineColor(sf::Color::Black);
                    }
                }
            }
        }
    } else if (state == "Login") {
        while (Window.pollEvent(Event)) {
            if (Event.type == sf::Event::Closed) {
                Window.close();
            } else if (Event.type == sf::Event::MouseButtonPressed) {
                if (Event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2i clickPosition = sf::Mouse::getPosition(Window);
                    if (LoginView[1].getGlobalBounds().contains(clickPosition.x, clickPosition.y))
                        state = "Main";
                    else if (LoginView[2].getGlobalBounds().contains(clickPosition.x, clickPosition.y)) {
                        Selection = &LoginViewText[2];
                        LoginView[2].setOutlineColor(sf::Color::Red);
                        LoginView[2].setOutlineThickness(3);
                        LoginView[3].setOutlineColor(sf::Color::Black);
                        LoginView[3].setOutlineThickness(1);
                    } else if (LoginView[3].getGlobalBounds().contains(clickPosition.x, clickPosition.y)) {
                        Selection = &LoginViewText[3];
                        LoginView[3].setOutlineColor(sf::Color::Red);
                        LoginView[3].setOutlineThickness(3);
                        LoginView[2].setOutlineColor(sf::Color::Black);
                        LoginView[2].setOutlineThickness(1);
                    }
                    else if (LoginView[4].getGlobalBounds().contains(clickPosition.x, clickPosition.y)) {
                        currentUser = LoginViewText[2].getString();
                        currentPass = LoginViewText[3].getString();
                        loggedin = database.loginUser(trim(currentUser), trim(currentPass));
                        std::cout << "User was able to be logged in? " << loggedin << std::endl;
                        if (!loggedin) {
                            return;
                        }

                        state = "Main";
                        LoginText[0].setString("Welcome " + currentUser + "!");
                        LoginView.clear();
                        LoginViewText.clear();
                    }
                }
            } else if (Event.type == sf::Event::TextEntered) {
                if (Event.text.unicode < 128) {
                    if (Event.text.unicode != 8) {
                        Selection->setString(Selection->getString() + Event.text.unicode);
                    }
                }

            } else if (Event.type == sf::Event::KeyPressed) {
                if (Event.key.code == sf::Keyboard::BackSpace) {
                    std::string text = Selection->getString();
                    if (!text.empty()) {
                        text.erase(text.size() - 1, 1);
                        Selection->setString(text);
                    }
                }
            }
            else if (Event.type == sf::Event::MouseMoved) {
                sf::Vector2i mousePosition = sf::Mouse::getPosition(Window);
                for (unsigned int i = 0; i < LoginView.size(); ++i) {
                    if (LoginView[i].getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
                        LoginView[i].setOutlineColor(sf::Color::Red);
                    } else {
                        LoginView[i].setOutlineColor(sf::Color::Black);
                    }
                }
            }
        }
    }
}

void MainWindow::Draw()
{
    sf::Color backgroundColor(231, 231, 231);
    Window.clear(backgroundColor);

    if (state == "Main")
    {
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
        for (const auto& service : services)
        {
            if (service.visible) Window.draw(service.icon);
        }
        if (loggedin)
        {
            Window.draw(LoginText[0]);
        }
        else
        {
            Window.draw(Login[0]);
            Window.draw(LoginText[0]);
        }
        Window.display();
    }
    else if (state == "Service")
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
    else if (state == "Login")
    {
        for (sf::RectangleShape Shape : LoginView)
        {
            Window.draw(Shape);
        }
        for (sf::Text Text : LoginViewText)
        {
            Window.draw(Text);
        }
        Window.display();
    }
}

void MainWindow::Services(std::vector<std::reference_wrapper<Service>>& servicesToShow)
{
    Objects.clear();
    Texts.clear();

    sf::Color backgroundColor(231, 231, 231);

    sf::Vector2u baseSize(1200.0f, 800.0f);
    sf::Vector2u currentSize = Window.getSize();

    float widthScale = static_cast<float>(currentSize.x) / baseSize.x;
    float heightScale = static_cast<float>(currentSize.y) / baseSize.y;

    int serviceCount = servicesToShow.size();
    int index = 0;

    for (int i = 1; i < 4 && index < serviceCount; i++)
    {
        for (int j = 0; j < 4 && index < serviceCount; j++, index++)
        {
            sf::RectangleShape ServiceNode;
            ServiceNode.setSize(sf::Vector2f(250 * widthScale, 150 * heightScale));
            ServiceNode.setPosition(widthScale * (25 + (j * 300)), heightScale * (i * 180));
            ServiceNode.setFillColor(backgroundColor);
            ServiceNode.setOutlineColor(sf::Color::Black);
            ServiceNode.setOutlineThickness(2);
            Objects.push_back(ServiceNode);

            sf::Text ServiceName;
            ServiceName.setFont(Font);
            ServiceName.setCharacterSize(18 * std::min(widthScale, heightScale));
            ServiceName.setPosition(widthScale * (30 + (j * 300)), heightScale * (i * 180));
            ServiceName.setFillColor(sf::Color::Black);
            std::string title = servicesToShow[index].get().title;
            if (title.length() > 20) {
                title = title.substr(0, 17) + "...";
            }
            ServiceName.setString(title);
            Texts.push_back(ServiceName);

            sf::Text ServiceDescription;
            ServiceDescription.setFont(Font);
            ServiceDescription.setCharacterSize(14 * std::min(widthScale, heightScale));
            ServiceDescription.setPosition(widthScale * (30 + (j * 300)), heightScale * (i * 180) + 30);
            ServiceDescription.setFillColor(sf::Color::Black);
            std::string description = servicesToShow[index].get().description;
            ServiceDescription.setString(wrapText(description, 240, Font, 14));
            Texts.push_back(ServiceDescription);

            sf::Text ServiceRating;
            ServiceRating.setFont(Font);
            ServiceRating.setCharacterSize(14 * std::min(widthScale, heightScale));
            ServiceRating.setPosition(widthScale * (225 + (j * 300)), heightScale * (i * 180));
            ServiceRating.setFillColor(sf::Color::Black);
            ServiceRating.setString(std::to_string(servicesToShow[index].get().rating) + "/5 Stars");
            Texts.push_back(ServiceRating);

            servicesToShow[index].get().visible = true;

            sf::Sprite& icon = servicesToShow[index].get().icon;
            sf::Vector2f targetSize(70.0f, 70.0f);
            float iconX = widthScale * (25 + (j * 300) + (250 - targetSize.x) / 2);
            float iconY = heightScale * ((i * 180) + 70);
            icon.setPosition(iconX, iconY);
            
        }
    }
}

void MainWindow::login()
{
    LoginView.clear();
    LoginViewText.clear();

    sf::Vector2u baseSize(1200.0f, 800.0f);
    sf::Vector2u currentSize = Window.getSize();

    float widthScale = static_cast<float>(currentSize.x) / baseSize.x;
    float heightScale = static_cast<float>(currentSize.y) / baseSize.y;

    state = "Login";
    sf::Text Header;
    sf::RectangleShape HeaderBackground;

    Header.setFont(Font);

    Header.setString("Sign In to Service Hunter");
    Header.setCharacterSize(48 * std::min(widthScale, heightScale));
    Header.setPosition(20 * widthScale, 10 * heightScale);
    Header.setFillColor(sf::Color::White);
    Header.setOutlineColor(sf::Color::Black);
    Header.setOutlineThickness(1);
    LoginViewText.push_back(Header);

    sf::Color Logo(137, 207, 240);
    HeaderBackground.setSize(sf::Vector2f(1200 * widthScale, 80 * heightScale));
    HeaderBackground.setPosition(0, 0);
    HeaderBackground.setFillColor(Logo);
    LoginView.push_back(HeaderBackground);

    sf::RectangleShape BackButton;
    BackButton.setSize(sf::Vector2f(200 * widthScale, 40 * heightScale));
    BackButton.setPosition(20 * widthScale, 700 * heightScale);
    BackButton.setFillColor(sf::Color::White);
    BackButton.setOutlineColor(sf::Color::Black);
    BackButton.setOutlineThickness(2);
    LoginView.push_back(BackButton);

    sf::Text BackText;
    BackText.setFont(Font);
    BackText.setString("Back");
    BackText.setCharacterSize(24 * std::min(widthScale, heightScale));
    BackText.setPosition(30 * widthScale, 705 * heightScale);
    BackText.setFillColor(sf::Color::Black);
    LoginViewText.push_back(BackText);

    float Center = currentSize.x / 2.0f;
    float CenterVert = currentSize.y / 2.0f;
    float BoxHeight = 40 * heightScale;
    float TotalHeight = 2 * BoxHeight + 200;

    float Box1 = CenterVert - (TotalHeight / 2.0f);
    float Box2 = Box1 + BoxHeight + 150;
    sf::Color User(105, 105, 105);

    sf::RectangleShape Username;

    Username.setSize(sf::Vector2f(500 * widthScale, 40 * heightScale));
    Username.setPosition(Center - (500 * widthScale / 2.0f), Box1);
    Username.setFillColor(sf::Color::White);
    Username.setOutlineColor(sf::Color::Black);
    Username.setOutlineThickness(2);
    LoginView.push_back(Username);

    sf::Text UsernameText;

    UsernameText.setFont(Font);
    UsernameText.setString("");
    UsernameText.setCharacterSize(24 * std::min(widthScale, heightScale));
    UsernameText.setPosition(Center + 5 - (500 * widthScale / 2.0f), Box1 + 5);
    UsernameText.setFillColor(User);
    LoginViewText.push_back(UsernameText);

    sf::RectangleShape Password;

    Password.setSize(sf::Vector2f(500 * widthScale, 40 * heightScale));
    Password.setPosition(Center - (500 * widthScale / 2.0f), Box2);
    Password.setFillColor(sf::Color::White);
    Password.setOutlineColor(sf::Color::Black);
    Password.setOutlineThickness(2);
    LoginView.push_back(Password);

    sf::Text PasswordText;

    PasswordText.setFont(Font);
    PasswordText.setString("");
    PasswordText.setCharacterSize(24 * std::min(widthScale, heightScale));
    PasswordText.setPosition(Center + 5 - (500 * widthScale / 2.0f), Box2 + 5);
    PasswordText.setFillColor(User);
    LoginViewText.push_back(PasswordText);

    sf::Text EnterUsername;

    EnterUsername.setFont(Font);
    EnterUsername.setString("Username");
    EnterUsername.setCharacterSize(24 * std::min(widthScale, heightScale));
    EnterUsername.setPosition(Center + 5 - (500 * widthScale / 2.0f), Box1 - 50);
    EnterUsername.setFillColor(sf::Color::Black);
    LoginViewText.push_back(EnterUsername);

    sf::Text EnterPassword;

    EnterPassword.setFont(Font);
    EnterPassword.setString("Password");
    EnterPassword.setCharacterSize(24 * std::min(widthScale, heightScale));
    EnterPassword.setPosition(Center + 5 - (500 * widthScale / 2.0f), Box2 - 50);
    EnterPassword.setFillColor(sf::Color::Black);
    LoginViewText.push_back(EnterPassword);

    sf::RectangleShape SignInButton;

    SignInButton.setSize(sf::Vector2f(150 * widthScale, 40 * heightScale));
    SignInButton.setPosition(Center - (100 * widthScale / 2.0f), Box2 + 100);
    SignInButton.setFillColor(sf::Color::White);
    SignInButton.setOutlineColor(sf::Color::Black);
    SignInButton.setOutlineThickness(2);
    LoginView.push_back(SignInButton);

    sf::Text SignIn;

    SignIn.setFont(Font);
    SignIn.setString("Register/Sign In");
    SignIn.setCharacterSize(24 * std::min(widthScale, heightScale));
    SignIn.setPosition(Center + 20 - (100 * widthScale / 2.0f), Box2 + 105);
    SignIn.setFillColor(sf::Color::Black);
    LoginViewText.push_back(SignIn);
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
    sf::Vector2u baseSize(1200.0f, 800.0f);
    sf::Vector2u currentSize = Window.getSize();

    float widthScale = static_cast<float>(currentSize.x) / baseSize.x;
    float heightScale = static_cast<float>(currentSize.y) / baseSize.y;

    state = "Service";
    sf::Text Header;
    sf::RectangleShape HeaderBackground;

    Header.setFont(Font);

    Header.setString(services[index].title);
    Header.setCharacterSize(48 * std::min(widthScale, heightScale));
    Header.setPosition(20 * widthScale, 10 * heightScale);
    Header.setFillColor(sf::Color::White);
    Header.setOutlineColor(sf::Color::Black);
    Header.setOutlineThickness(1);
    ServiceText.push_back(Header);

    sf::Color Logo(137, 207, 240);
    HeaderBackground.setSize(sf::Vector2f(1200 * widthScale, 80 * heightScale));
    HeaderBackground.setPosition(0, 0);
    HeaderBackground.setFillColor(Logo);
    ServiceView.push_back(HeaderBackground);

    sf::Text Description;
    Description.setFont(Font);
    Description.setString(wrapText(services[index].longDescription, 280, Font, 14));
    Description.setCharacterSize(36 * std::min(widthScale, heightScale));
    Description.setPosition(20 * widthScale, 100 * heightScale);
    Description.setFillColor(sf::Color::Black);
    ServiceText.push_back(Description);

    sf::Text Rating;
    Rating.setFont(Font);
    Rating.setString(std::to_string(services[index].rating) + "/5 Stars");
    Rating.setCharacterSize(48 * std::min(widthScale, heightScale));
    Rating.setPosition(975 * widthScale, 10 * heightScale);
    Rating.setFillColor(sf::Color::White);
    Rating.setOutlineColor(sf::Color::Black);
    Rating.setOutlineThickness(1);
    ServiceText.push_back(Rating);

    sf::RectangleShape BackButton;
    BackButton.setSize(sf::Vector2f(200 * widthScale, 40 * heightScale));
    BackButton.setPosition(20 * widthScale, 700 * heightScale);
    BackButton.setFillColor(sf::Color::White);
    BackButton.setOutlineColor(sf::Color::Black);
    BackButton.setOutlineThickness(2);
    ServiceView.push_back(BackButton);

    sf::Text BackText;
    BackText.setFont(Font);
    BackText.setString("Back");
    BackText.setCharacterSize(24 * std::min(widthScale, heightScale));
    BackText.setPosition(30 * widthScale, 705 * heightScale);
    BackText.setFillColor(sf::Color::Black);
    ServiceText.push_back(BackText);
}

void MainWindow::PerformSearch(const std::string& query) {
    std::vector<std::reference_wrapper<Service>> results;
    std::string lowerQuery = query;
    std::transform(lowerQuery.begin(), lowerQuery.end(), lowerQuery.begin(), ::tolower); // Convert query to lowercase
    for (auto& service : services) {
        service.visible = false;
        std::string lowerTitle = service.title;
        std::transform(lowerTitle.begin(), lowerTitle.end(), lowerTitle.begin(), ::tolower); // Convert service title to lowercase
        
        if (lowerTitle.find(lowerQuery) != std::string::npos) {
            results.push_back(service);
        }
    }

    Services(results);
    if (results.empty()) {
        std::cout << "No related services found.\n";
    }
}
