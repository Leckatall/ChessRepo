
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
        src/models/chessboard/board_tblmodel.h
        src/models/chessboard/board_tblmodel.cpp
        src/models/chessboard/board_wrapper.cpp
        src/models/chessboard/board_wrapper.h
        src/models/chessboard/board_proxytblmodel.cpp
        src/models/chessboard/board_proxytblmodel.h
        src/models/datatypes.h
        src/models/explorer_tblmodel.cpp
        src/models/explorer_tblmodel.h
        src/models/repertoires/repotreemodel.cpp
        src/models/repertoires/repotreemodel.h
        src/services/repertoire_navigator.cpp
        src/services/repertoire_navigator.h
)
set(VIEWS
        src/ui/components/chessboard/square_delegate.cpp
        src/ui/components/chessboard/square_delegate.h
        src/ui/components/chessboard/board_tblview.cpp
        src/ui/components/chessboard/board_tblview.h
        src/ui/components/explorer/explorer_tblview.cpp
        src/ui/components/explorer/explorer_tblview.h
        src/ui/components/explorer/winrate_delegate.cpp
        src/ui/components/explorer/winrate_delegate.h
        src/ui/components/chessboard/arrowoverlay.cpp
        src/ui/components/chessboard/arrowoverlay.h
        src/ui/components/createrepomodal.cpp
        src/ui/components/createrepomodal.h
        src/ui/pages/list/repocard.cpp
        src/ui/pages/list/repocard.h
        src/app/router.cpp
        src/app/router.h
        src/ui/pages/edit/edit_page.cpp
        src/ui/pages/edit/edit_page.h
        src/ui/components/repertoire_tree.cpp
        src/ui/components/repertoire_tree.h
        src/ui/components/move_card.cpp
        src/ui/components/move_card.h
        src/ui/components/common/stats_painter.cpp
        src/ui/components/common/stats_painter.h
        src/ui/pages/edit/moves_deck.cpp
        src/ui/pages/edit/moves_deck.h
        src/ui/components/chessboard/board_view.cpp
        src/ui/components/chessboard/board_view.h
)


set(CONTROLLERS
        src/controllers/boardcontroller.h
        src/controllers/boardcontroller.cpp
        src/controllers/explorer_controller.cpp
        src/controllers/explorer_controller.h
        src/controllers/openingcontroller.cpp
        src/controllers/openingcontroller.h
        src/ui/pages/list/list_page.cpp
        src/ui/pages/list/list_page.h
        src/controllers/repertoire_list_controller.cpp
        src/controllers/repertoire_list_controller.h
        src/controllers/Controller.h
        src/controllers/Controller.cpp
        src/controllers/edit_controller.cpp
        src/controllers/edit_controller.h
        src/controllers/board_controller.cpp
        src/controllers/board_controller.h
        src/ui/components/explorer/explorer_view.cpp
        src/ui/components/explorer/explorer_view.h
)

add_executable(myapp
        src/main.cpp
        ${MODELS}
        ${VIEWS}
        ${CONTROLLERS}
        src/services/LichessService.cpp
        src/services/LichessService.h
        src/services/repertoire_service.cpp
        src/services/repertoire_service.h
        src/app/application.cpp
        src/app/application.h
        src/ui/pages/page.cpp
        src/ui/pages/page.h
        src/services/session.cpp
        src/services/session.h
        src/app/models.h
        src/services/repertoire_repository.cpp
        src/services/repertoire_repository.h
)

# Link Qt6 libraries
target_link_libraries(myapp PRIVATE Qt6::Core Qt6::Gui Qt6::Widgets Qt6::Network)



