
cmake_minimum_required(VERSION 3.10)
project(ChessRepo)



set(CMAKE_CXX_STANDARD 20)       # Use C++20
set(CMAKE_CXX_STANDARD_REQUIRED ON)  # Ensure the standard is used
set(CMAKE_CXX_EXTENSIONS OFF) # Use only standard C++, no compiler-specific extensions

include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/libs/chess-library/include)

# Ensure Qt6 automatically handles MOC (Meta-Object Compiler) for QObject-based classes
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# Import Qt6
set(Qt6_DIR "C:\\Qt\\6.8.2\\mingw_64\\lib\\cmake\\Qt6")
find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)

# Building the execuatble
## Building source list
set(SOURCES
    src/main.cpp
    src/MainWindow.cpp
        src/ChessCanvas.cpp
)

## Building headers list
set(HEADERS
    include/MainWindow.h
        include/ChessCanvas.h
)

add_executable(myapp ${SOURCES} ${HEADERS})

# Link Qt6 libraries
target_link_libraries(myapp PRIVATE Qt6::Core Qt6::Gui Qt6::Widgets)

target_include_directories(myapp PRIVATE ${CMAKE_SOURCE_DIR}/include)