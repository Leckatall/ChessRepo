
cmake_minimum_required(VERSION 3.10)
project(ChessRepo)



set(CMAKE_CXX_STANDARD 20)       # Use C++20
set(CMAKE_CXX_STANDARD_REQUIRED ON)  # Ensure the standard is used
set(CMAKE_CXX_EXTENSIONS OFF) # Use only standard C++, no compiler-specific extensions
set(CMAKE_TOOLCHAIN_FILE "C:\\Users\\Lecka\\.vcpkg-clion\\vcpkg\\scripts\\buildsystems\\vcpkg.cmake" CACHE STRING "Vcpkg toolchain file")

#set(CMAKE_PREFIX_PATH "C:/Users/Lecka/.vcpkg-clion/vcpkg/installed/x64-mingw-dynamic/share")

include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/libs/chess-library/include)

# Ensure Qt6 automatically handles MOC (Meta-Object Compiler) for QObject-based classes
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# Import Qt6
set(Qt6_DIR "C:\\Qt\\6.8.2\\mingw_64\\lib\\cmake\\Qt6")
find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets Network Quick Qml)
#
#find_package(curlcpp CONFIG REQUIRED)
#target_link_libraries(myapp PRIVATE curlcpp::curlcpp)
# Import cpr
find_package(cpr CONFIG REQUIRED)

# Import JSON
find_package(nlohmann_json CONFIG REQUIRED)

# Building the execuatble
## Building source list
set(SOURCES
    src/main.cpp
    src/MainWindow.cpp
        src/views/ChessDisplay.cpp
        src/models/chess_board.cpp
        src/models/explorer.cpp
        src/models/table_model.cpp
        src/controllers/opening_controller.cpp
        src/controllers/opening_controller.h
)

## Building headers list
set(HEADERS
        src/mainwindow.h
        src/views/ChessDisplay.h
        src/models/chess_board.h
        src/views/BuildRepoFrame.h
        src/models/explorer.h
        include/ExplorerMovesTable.h
        src/models/table_model.h
)

# Add the QML files to the resource system
qt_add_resources(RESOURCES resources.qrc)

add_executable(myapp ${SOURCES} ${HEADERS})


# Specify the QML directory for deployment
set_target_properties(${PROJECT_NAME} PROPERTIES
    QT_QML_MODULES_DIR "${CMAKE_SOURCE_DIR}/qml"
)

# Link Qt6 libraries
target_link_libraries(myapp PRIVATE Qt6::Core Qt6::Gui Qt6::Widgets Qt6::Network Qt6::Quick Qt6::Qml)
target_link_libraries(myapp PRIVATE cpr::cpr)

target_include_directories(myapp PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(myapp PRIVATE nlohmann_json::nlohmann_json)


