
cmake_minimum_required(VERSION 3.10)
project(ChessRepo)


set(CMAKE_CXX_STANDARD 20)       # Use C++20
set(CMAKE_CXX_STANDARD_REQUIRED ON)  # Ensure the standard is used
set(CMAKE_CXX_EXTENSIONS OFF) # Use only standard C++, no compiler-specific extensions
#set(CMAKE_TOOLCHAIN_FILE "C:\\Users\\Lecka\\.vcpkg-clion\\vcpkg\\scripts\\buildsystems\\vcpkg.cmake" CACHE STRING "Vcpkg toolchain file")
set(CMAKE_TOOLCHAIN_FILE "")

#set(CMAKE_PREFIX_PATH "C:/Users/Lecka/.vcpkg-clion/vcpkg/installed/x64-mingw-dynamic/share")

include_directories(${PROJECT_SOURCE_DIR}/src)
include_directories(${PROJECT_SOURCE_DIR}/libs/chess-library/include)

# Ensure Qt6 automatically handles MOC (Meta-Object Compiler) for QObject-based classes
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# Import Qt6
set(Qt6_DIR "C:\\Qt\\6.8.2\\mingw_64\\lib\\cmake\\Qt6")
find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets Network)

# Building the execuatble
## Building source list
#set(SOURCES
#        src/main.cpp
#        src/controllers/opening_controller.cpp
#        src/controllers/opening_controller.h
#)

set(MODELS
        src/models/tablemodel.h
        src/models/tablemodel.cpp

        src/models/boardtblmodel.h
        src/models/boardtblmodel.cpp
        src/models/boardwrapper.cpp
        src/models/boardwrapper.h
)
set(VIEWS
        src/views/mainwindow.h
        src/views/mainwindow.cpp
        src/views/squaredelegate.cpp
        src/views/squaredelegate.h
        src/views/boardtblview.cpp
        src/views/boardtblview.h
        src/views/boardview.cpp
        src/views/boardview.h
)


set(CONTROLLERS
        src/controllers/boardcontroller.h
        src/controllers/boardcontroller.cpp
        src/controllers/boardcontroller.cpp
        src/controllers/boardcontroller.h
        src/controllers/squarecontroller.cpp
        src/controllers/squarecontroller.h
        src/models/boardmodel.cpp
        src/models/boardmodel.h
        src/models/squaremodel.cpp
        src/models/squaremodel.h
)
## Building headers list
#set(HEADERS
#        src/mainwindow.h
#        src/views/ChessDisplay.h
#        src/models/chess_board.h
#        src/views/BuildRepoFrame.h
#        src/models/explorer.h
#        include/ExplorerMovesTable.h
#        src/models/table_model.h
#)

# Add the QML files to the resource system
#qt_add_resources(RESOURCES resources.qrc)

add_executable(myapp
        src/main.cpp
        ${MODELS}
        ${VIEWS}
        ${CONTROLLERS}
)

# Link Qt6 libraries
target_link_libraries(myapp PRIVATE Qt6::Core Qt6::Gui Qt6::Widgets Qt6::Network)



