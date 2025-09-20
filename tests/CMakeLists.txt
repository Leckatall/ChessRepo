find_package(Qt6 REQUIRED COMPONENTS Test)

# Function to create test executables
function(create_test test_name test_source)
    add_executable(${test_name} ${test_source})
    target_link_libraries(${test_name}
        Qt6::Test
        Qt6::Core
        Qt6::Widgets
        chess_domain
        chess_infrastructure
        chess_presentation
        chess_ui
        chess_controllers
    )
    add_test(NAME ${test_name} COMMAND ${test_name})
endfunction()

# Domain Tests
#create_test(test_domain
#    domain/test_board.cpp
#    domain/test_position_key.cpp
#    domain/test_repertoire.cpp
#)
#
# Infrastructure Tests
create_test(test_persistence
    unit/test_repertoire_persistence.cpp
    unit/test_repertoire_persistence.h
)
create_test(moves_deck_widget_test
    unit/ui/test_moves_deck_widget.cpp
    unit/ui/test_moves_deck_widget.h
)
#
## Integration Tests
#create_test(test_integration
#    integration/test_board_viewmodel.cpp
#    integration/test_explorer_integration.cpp
#)