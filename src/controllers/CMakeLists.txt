# Intend to make this library DEPRECATED in the future
# Controllers Layer Library
add_library(chess_controllers STATIC
    board_controller.cpp
    board_controller.h
    # Add other controllers as they're uncommented/created
)

target_link_libraries(chess_controllers PUBLIC
    Qt6::Core
    Qt6::Widgets
    chess_domain
    chess_infrastructure
    chess_presentation
    chess_ui
)

target_include_directories(chess_controllers PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)