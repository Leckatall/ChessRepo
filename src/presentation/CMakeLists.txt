# Presentation Layer Library
add_library(chess_presentation STATIC
    # Utils
    utils.h

    # Models
    models/tablemodel.h
    models/tablemodel.cpp
    models/chessboard/board_tblmodel.h
    models/chessboard/board_tblmodel.cpp
    models/chessboard/board_wrapper.cpp
    models/chessboard/board_wrapper.h
    models/chessboard/board_proxytblmodel.cpp
    models/chessboard/board_proxytblmodel.h
    models/explorer_tblmodel.cpp
    models/explorer_tblmodel.h
#    models/repertoires/repotreemodel.cpp
#    models/repertoires/repotreemodel.h

    # ViewModels
    viewmodels/board_viewmodel.cpp
    viewmodels/board_viewmodel.h
    viewmodels/explorer_viewmodel.cpp
    viewmodels/explorer_viewmodel.h
        viewmodels/repertoire_viewmodel.cpp
        viewmodels/repertoire_viewmodel.h
        viewmodels/board_table_viewmodel.cpp
        viewmodels/board_table_viewmodel.h
        viewmodels/repertoire_selection_viewmodel.cpp
        viewmodels/repertoire_selection_viewmodel.h
)

target_link_libraries(chess_presentation PUBLIC
    Qt6::Core
    Qt6::Widgets
    chess_domain
    chess_infrastructure
)

target_include_directories(chess_presentation PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)


