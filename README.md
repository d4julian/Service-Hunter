
# Service Hunter

A booking system for a service marketplace that connects customers with local service providers such as plumbers, makeup artists, AC repair technicians, and more.

### Prerequisites

- PostgreSQL
- C++ compiler (e.g., `clang++` or `g++`)
- CMake
- SFML library

### Clone the Repository

```sh
git clone https://github.com/yourusername/Service-Hunter.git
cd Service-Hunter
```

### Build the Project

1. Create a build directory:

    ```sh
    mkdir build
    cd build
    ```

2. Run CMake to generate the build files:

    ```sh
    cmake ..
    ```

3. Build the project:

    ```sh
    make
    ```

### Database Setup

1. Ensure your `db_password.txt` file contains the database credentials.

### Run the Application

```sh
./ServiceHunter
```

## Project Structure

```
Service-Hunter/
│
├── assets/                   # Assets like fonts and images
│   ├── Arial.ttf
│   └── ...
│
├── build/                    # Build directory (created after running CMake)
│   └── ...
│
├── src/                      # Source files
│   ├── MainWindow.cpp        # Main application window implementation
│   ├── MainWindow.h          # Header for MainWindow
│   ├── Database.cpp          # Database interaction implementation
│   ├── Database.h            # Header for Database
│   └── ...
│
├── CMakeLists.txt            # CMake build configuration
└── README.md                 # This README file
```