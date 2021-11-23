add_executable(challenge
    ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
)

set_target_properties(challenge PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

target_link_libraries(challenge
PRIVATE
    types
    translator
    runtime
)