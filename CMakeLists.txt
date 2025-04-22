
cmake_minimum_required(VERSION 3.10)
project(ChessRepo)


set(CMAKE_CXX_STANDARD 20)       # Use C++20
set(CMAKE_CXX_STANDARD_REQUIRED ON)  # Ensure the standard is used
set(CMAKE_CXX_EXTENSIONS OFF) # Use only standard C++, no compiler-specific extensions
#set(CMAKE_TOOLCHAIN_FILE "C:\\Users\\Lecka\\.vcpkg-clion\\vcpkg\\scripts\\buildsystems\\vcpkg.cmake" CACHE STRING "Vcpkg toolchain file")

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


set(MODELS
        src/models/tablemodel.h
        src/models/tablemodel.cpp
        src/models/chessboard/boardtblmodel.h
        src/models/chessboard/boardtblmodel.cpp
        src/models/chessboard/boardwrapper.cpp
        src/models/chessboard/boardwrapper.h
        src/models/chessboard/boardtblproxymodel.cpp
        src/models/chessboard/boardtblproxymodel.h
        src/models/moveModel.cpp
        src/models/moveModel.h
        src/models/datatypes.h
        src/models/explorerTblModel.cpp
        src/models/explorerTblModel.h
        src/models/openingrepertoiremodel.cpp
        src/models/openingrepertoiremodel.h
)
set(VIEWS
        src/views/mainwindow.h
        src/views/mainwindow.cpp
        src/views/chessboard/squaredelegate.cpp
        src/views/chessboard/squaredelegate.h
        src/views/chessboard/boardtblview.cpp
        src/views/chessboard/boardtblview.h
        src/views/explorer/explorertblview.cpp
        src/views/explorer/winratedelegate.cpp
        src/views/explorer/winratedelegate.h
        src/views/chessboard/arrowoverlay.cpp
        src/views/chessboard/arrowoverlay.h
        src/views/repository/createrepomodal.cpp
        src/views/repository/createrepomodal.h
)


set(CONTROLLERS
        src/controllers/boardcontroller.h
        src/controllers/boardcontroller.cpp
        src/controllers/explorercontroller.cpp
        src/controllers/explorercontroller.h
        src/controllers/contentcontroller.h
        src/controllers/openingcontroller.cpp
        src/controllers/openingcontroller.h
)

add_executable(myapp
        src/main.cpp
        ${MODELS}
        ${VIEWS}
        ${CONTROLLERS}
        src/services/LichessService.cpp
        src/services/LichessService.h
        src/services/OpeningService.cpp
        src/services/OpeningService.h
)

# Link Qt6 libraries
target_link_libraries(myapp PRIVATE Qt6::Core Qt6::Gui Qt6::Widgets Qt6::Network)



