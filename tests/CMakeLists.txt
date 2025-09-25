find_package(Qt6 REQUIRED COMPONENTS Test)

# Function to create test executables
function(create_test test_name test_source)
    add_executable(${test_name} ${test_source} test_utils.cpp test_utils.h ../resources.qrc)
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
create_test(test_moves_deck_widget
        unit/ui/test_moves_deck_widget.cpp
        unit/ui/test_moves_deck_widget.h
)
create_test(test_board_widget
        unit/ui/test_board_widget.cpp
        unit/ui/test_board_widget.h
)
create_test(test_repertoire_viewmodel
        unit/presentation/test_repertoire_viewmodel.cpp
        unit/presentation/test_repertoire_viewmodel.h
)

create_test(test_resources
        unit/test_resources.cpp
        unit/test_resources.h)

create_test(test_square_primitive
        unit/domain/test_square_primitive.cpp
        unit/domain/test_square_primitive.h)

create_test(test_repertoire_selection_viewmodel
        unit/presentation/test_repertoire_selection_viewmodel.cpp
        unit/presentation/test_repertoire_selection_viewmodel.h)
#
## Integration Tests
#create_test(test_integration
#    integration/test_board_viewmodel.cpp
#    integration/test_explorer_integration.cpp
#)