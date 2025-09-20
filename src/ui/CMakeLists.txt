# UI Layer Library
add_library(chess_ui STATIC
    # Chessboard Components
    components/chessboard/square_delegate.cpp
    components/chessboard/square_delegate.h
    components/chessboard/board_tblview.cpp
    components/chessboard/board_tblview.h
    components/chessboard/arrowoverlay.cpp
    components/chessboard/arrowoverlay.h
    components/chessboard/board_view.cpp
    components/chessboard/board_view.h
    components/chessboard/board_graphics_view.cpp
    components/chessboard/board_graphics_view.h
    components/chessboard/board_graphics_scene.cpp
    components/chessboard/board_graphics_scene.h
    components/chessboard/piece_graphics_item.cpp
    components/chessboard/piece_graphics_item.h
    components/chessboard/square_graphics_item.cpp
    components/chessboard/square_graphics_item.h

    # Explorer Components
    components/explorer/explorer_tblview.cpp
    components/explorer/explorer_tblview.h
    components/explorer/winrate_delegate.cpp
    components/explorer/winrate_delegate.h
    components/explorer/explorer_view.cpp
    components/explorer/explorer_view.h

    # Other Components
    components/createrepomodal.cpp
    components/createrepomodal.h
    components/repertoire_tree.cpp
    components/repertoire_tree.h
#    components/move_card.cpp
#    components/move_card.h
    components/repertoire/move_card.cpp
    components/repertoire/move_card.h
    components/repertoire/moves_deck.cpp
    components/repertoire/moves_deck.h

    # Common Components
    components/common/stats_painter.cpp
    components/common/stats_painter.h

    # Pages
    pages/list/repocard.cpp
    pages/list/repocard.h
        #    pages/edit/moves_deck.cpp
#    pages/edit/moves_deck.h
)

target_link_libraries(chess_ui PUBLIC
    Qt6::Core
    Qt6::Widgets
    Qt6::Gui
    Qt6::Svg
    chess_domain
    chess_presentation
)

target_include_directories(chess_ui PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

