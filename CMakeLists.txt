cmake_minimum_required(VERSION 3.21)
project(ChessRepo VERSION 1.0.0)

# C++ Standard Configuration
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Qt Configuration
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# Find Qt6
find_package(Qt6 REQUIRED COMPONENTS
    Core 
    Gui 
    Widgets 
    Network 
    Svg
    Test  # Add for testing
)
# Include directories
include_directories(${PROJECT_SOURCE_DIR}/src)
include_directories(${PROJECT_SOURCE_DIR}/libs/chess-library/include)

# Add subdirectories for modular libraries
add_subdirectory(src/domain)
add_subdirectory(src/infrastructure) 
add_subdirectory(src/presentation)
add_subdirectory(src/ui)
add_subdirectory(src/controllers)

# Main executable
add_executable(myapp
    src/main.cpp
    src/app/app.cpp
    src/app/app.h
    src/app/models.h
    src/utils/chess.h
        src/infrastructure/persistence/QJson_parser.cpp
        src/infrastructure/persistence/QJson_parser.h
        resources.qrc
)

# Link libraries to main executable
target_link_libraries(myapp PRIVATE
    Qt6::Core
    Qt6::Gui 
    Qt6::Widgets
    Qt6::Network
    Qt6::Svg
    chess_domain
    chess_infrastructure  
    chess_presentation
    chess_ui
    chess_controllers
)

# Enable testing
enable_testing()
add_subdirectory(tests)