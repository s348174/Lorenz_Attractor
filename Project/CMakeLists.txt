cmake_minimum_required(VERSION 3.9)

project(LorenzAttractor LANGUAGES CXX C VERSION 1.0.0)

# Set C++ Standard
################################################################################
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# IMPOSE WARNINGS ON DEBUG
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -Wextra -pedantic-errors")

# IMPOSE CXX FLAGS FOR WINDOWS
if (WIN32)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wa,-mbig-obj")
endif (WIN32)

# Add dependencies
################################################################################
set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH};${CMAKE_CURRENT_SOURCE_DIR}/../externals/Main_Install/eigen3)
set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH};${CMAKE_CURRENT_SOURCE_DIR}/../externals/Main_Install/googletest)

## Eigen3
find_package(Eigen3 CONFIG REQUIRED)
list(APPEND ${CMAKE_PROJECT_NAME}_LINKED_LIBRARIES PUBLIC Eigen3::Eigen)

## Threads
find_package(Threads REQUIRED)
list(APPEND ${CMAKE_PROJECT_NAME}_LINKED_LIBRARIES PRIVATE Threads::Threads)

## GTest
find_package(GTest REQUIRED)

list(APPEND ${CMAKE_PROJECT_NAME}_LINKED_LIBRARIES PRIVATE GTest::gtest)
list(APPEND ${CMAKE_PROJECT_NAME}_LINKED_LIBRARIES PRIVATE GTest::gtest_main)
list(APPEND ${CMAKE_PROJECT_NAME}_LINKED_LIBRARIES PRIVATE GTest::gmock)
list(APPEND ${CMAKE_PROJECT_NAME}_LINKED_LIBRARIES PRIVATE GTest::gmock_main)

# Insert Sources
################################################################################
add_subdirectory(src)

list(APPEND ${CMAKE_PROJECT_NAME}_SOURCES ${${CMAKE_PROJECT_NAME}_sources})
list(APPEND ${CMAKE_PROJECT_NAME}_HEADERS ${${CMAKE_PROJECT_NAME}_headers})
list(APPEND ${CMAKE_PROJECT_NAME}_INCLUDE ${${CMAKE_PROJECT_NAME}_includes})

# Create executable
################################################################################
add_executable(${PROJECT_NAME}
	main.cpp
        ${${CMAKE_PROJECT_NAME}_SOURCES}
    ${${CMAKE_PROJECT_NAME}_HEADERS})
    
#file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/PolygonalMesh
#     DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

target_link_libraries(${CMAKE_PROJECT_NAME} ${${CMAKE_PROJECT_NAME}_LINKED_LIBRARIES})
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE ${${CMAKE_PROJECT_NAME}_INCLUDE})
target_compile_options(${CMAKE_PROJECT_NAME} PUBLIC -fPIC)
