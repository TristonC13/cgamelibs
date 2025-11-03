cmake_minimum_required(VERSION 3.10)

# Set project name and version
project(cgamelibs C)

# Specify the source files
set(SOURCES
    src/cgamelibs.c
)

# Specify the header files (if any)
set(HEADERS
    include/cgamelibs.h
)

# Create the library
add_library(cgamelibs STATIC ${SOURCES} ${HEADERS})

# Specify the include directory for this library
target_include_directories(cgamelibs PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

# Optionally, set the C standard
set_target_properties(cgamelibs PROPERTIES
    C_STANDARD 99        # Set to C11 if needed
    C_STANDARD_REQUIRED True
)

enable_testing()

# Add the tests subdirectory
add_subdirectory(tests)
