
# Add source to this project's executable.
add_executable (learning 
  main.cpp
  vk_engine.cpp
  vk_engine.h
 )

 set_property(TARGET learning PROPERTY CXX_STANDARD 20)
set_property(TARGET learning PROPERTY VS_DEBUGGER_WORKING_DIRECTORY $<TARGET_FILE_DIR:learning>)

target_include_directories(learning PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")

target_link_libraries(learning vkguide_shared  vkbootstrap)

add_custom_command(TARGET learning POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:learning> $<TARGET_FILE_DIR:learning>
  COMMAND_EXPAND_LISTS
  )
