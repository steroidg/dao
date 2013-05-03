cmake_minimum_required(VERSION 2.8)

# Set the name of the prank project
project(dao)

# setup version numbers
set(VERSION_MAJOR 0)
set(VERSION_MINOR 0)
set(VERSION_PATCH 1)

# find the libraries we want
find_package(SDL REQUIRED)

# use the constants defined for packages to setup compiler options
include_directories(${SDL_INCLUDE_DIR})

# easy way to just grab all files named .hpp and .cpp
FILE( GLOB allHeaders *.hpp )
FILE( GLOB allSrcs *.cpp )

# define the target executable
add_executable( dao
    ${allHeaders}
    ${allSrcs}
    )

# link against the sdl libraries
target_link_libraries( dao ${SDL_LIBRARY})


# set any compiler options
set_target_properties( dao PROPERTIES LINKER_LANGUAGE CXX)
