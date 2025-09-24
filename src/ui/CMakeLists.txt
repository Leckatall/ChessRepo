# UI Layer Library
set(CHESSBOARD_COMPONENTS
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
)
set(EXPLORER_COMPONENTS
        components/explorer/explorer_tblview.cpp
        components/explorer/explorer_tblview.h
        components/explorer/winrate_delegate.cpp
        components/explorer/winrate_delegate.h
        components/explorer/explorer_view.cpp
        components/explorer/explorer_view.h
)
set(OTHER_COMPONENTS
        components/createrepomodal.cpp
        components/createrepomodal.h
        components/repertoire_tree.cpp
        components/repertoire_tree.h
        components/repertoire/move_card.cpp
        components/repertoire/move_card.h
        components/repertoire/moves_deck.cpp
        components/mainwindow/menu_bar.h
)
set(COMMON_COMPONENTS
        components/common/stats_painter.cpp
        components/common/stats_painter.h)

set(COMPONENTS
        ${CHESSBOARD_COMPONENTS}
        ${EXPLORER_COMPONENTS}
        ${OTHER_COMPONENTS}
        ${COMMON_COMPONENTS})
set(WIDGETS
        compound_widgets/chessboard_table.cpp
        compound_widgets/chessboard_table.h
        compound_widgets/explorer_table.cpp
        compound_widgets/explorer_table.h
        compound_widgets/repertoire_manager_widget.cpp
        compound_widgets/repertoire_manager_widget.h
        compound_widgets/repertoire_selection_widget.cpp
        compound_widgets/repertoire_selection_widget.h)

add_library(chess_ui STATIC
        ${COMPONENTS}
        ${WIDGETS}
        pages/list/repocard.cpp
        pages/list/repocard.h)

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

