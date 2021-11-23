add_executable(ut
    ${CMAKE_CURRENT_SOURCE_DIR}/ut.cpp
)

set_target_properties(ut PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

target_link_libraries(ut
PRIVATE
    translator
    runtime
    types
)