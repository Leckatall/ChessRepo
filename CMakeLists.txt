
cmake_minimum_required(VERSION 3.16)
project(ChessRepo)


set(CMAKE_CXX_STANDARD 20)       # Use C++20
set(CMAKE_CXX_STANDARD_REQUIRED ON)  # Ensure the standard is used
set(CMAKE_CXX_EXTENSIONS OFF) # Use only standard C++, no compiler-specific extensions
#set(CMAKE_TOOLCHAIN_FILE "C:\\Users\\Lecka\\.vcpkg-clion\\vcpkg\\scripts\\buildsystems\\vcpkg.cmake" CACHE STRING "Vcpkg toolchain file")
set(CMAKE_TOOLCHAIN_FILE "")

# Ensure Qt6 automatically handles MOC (Meta-Object Compiler) for QObject-based classes
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_PREFIX_PATH "C:/Qt/6.8.2/mingw_64/lib/cmake")
set(QML2_IMPORT_PATH "C:/Qt/6.8.2/mingw_64/bin")

include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/libs/chess-library/include)


# Import Qt6
set(Qt6_DIR "C:\\Qt\\6.8.2\\mingw_64\\lib\\cmake\\Qt6")
find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets Network Quick Qml)

# Building the executable

set(MODELS
        src/models/table_model.h
        src/models/table_model.cpp
        src/models/board_model.h
        src/models/board_model.cpp
)
#set(VIEWS
#        src/views/board_view.h
#        src/views/board_view.cpp
#)
set(CONTROLLERS
        src/controllers/board_controller.h
        src/controllers/board_controller.cpp
)


# Add the QML files to the resource system
qt_add_resources(RESOURCES resources.qrc)

#add_executable(main ${SOURCES} ${HEADERS} ${RESOURCES})

add_executable(main
        src/main.cpp
        ${MODELS}
        ${VIEWS}
        ${CONTROLLERS}
        ${RESOURCES}
        src/controllers/board_controller.cpp
        src/controllers/board_controller.h
)

#qt_add_qml_module(main
#    URI main
#    VERSION 1.0
#    QML_FILES
#        qml/main.qml
#    RESOURCES
#        resources.qrc
#)

# Specify the QML directory for deployment
#set_target_properties(main PROPERTIES
#        QT_QML_MODULES_DIR "${CMAKE_SOURCE_DIR}/qml"
#)

# Link Qt6 libraries
target_link_libraries(main PRIVATE Qt6::Core Qt6::Gui Qt6::Widgets Qt6::Network Qt6::Quick Qt6::Qml)
#target_link_libraries(main PRIVATE cpr::cpr)

target_include_directories(main PRIVATE ${CMAKE_SOURCE_DIR}/src)
#target_link_libraries(main PRIVATE nlohmann_json::nlohmann_json)



