
# Infrastructure Layer Library
add_library(chess_infrastructure STATIC
        # Explorer
        explorer/lichess_explorer_service.cpp
        explorer/lichess_explorer_service.h
        explorer/lichess_explorer_parser.cpp
        explorer/lichess_explorer_parser.h
        explorer/lichess_request_builder.cpp
        explorer/lichess_request_builder.h

        # Persistence
        persistence/QJson_parser.cpp
        persistence/QJson_parser.h
        persistence/repertoire_service.cpp
        persistence/repertoire_service.h
        persistence/repertoire_persistence.cpp
        persistence/repertoire_persistence.h
        persistence/qt_serialization.cpp
        persistence/qt_serialization.h
)

target_link_libraries(chess_infrastructure PUBLIC
        Qt6::Core
        Qt6::Network
        chess_domain  # Infrastructure depends on domain
)

target_include_directories(chess_infrastructure PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)