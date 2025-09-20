add_library(chess_domain STATIC
    # Types
    types/stats.cpp
    types/stats.h
    types/fen.cpp
    types/fen.h
    types/uci_move.cpp
    types/uci_move.h
    types/value_objects.h

    # Position
    types/position/position_key.cpp
    types/position/position_key.h
    types/position/position_graph.cpp
    types/position/position_graph.h
    types/position/position_stats.h
    types/position/position_record.h

    # Chess
    chess/primitives.h
    chess/board.cpp
    chess/board.h

    # Repertoire
    repertoire/repertoire.cpp
    repertoire/repertoire.h

        # Explorer
    explorer/iexplorer_service.cpp
    explorer/iexplorer_service.h
        types/collections.cpp
        types/collections.h
)

target_link_libraries(chess_domain PUBLIC
    Qt6::Core
)

# Export include directories for other targets
target_include_directories(chess_domain PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)



