list(APPEND LorenzAttractor_headers ${CMAKE_CURRENT_SOURCE_DIR}/Utils.hpp)
list(APPEND LorenzAttractor_sources ${CMAKE_CURRENT_SOURCE_DIR}/Utils.cpp)

list(APPEND LorenzAttractor_includes ${CMAKE_CURRENT_SOURCE_DIR})

set(LorenzAttractor_sources ${${CMAKE_PROJECT_NAME}_sources} PARENT_SCOPE)
set(LorenzAttractor_headers ${${CMAKE_PROJECT_NAME}_headers} PARENT_SCOPE)
set(LorenzAttractor_includes ${${CMAKE_PROJECT_NAME}_includes} PARENT_SCOPE)
