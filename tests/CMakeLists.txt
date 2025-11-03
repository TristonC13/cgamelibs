# Add the test executable
add_executable(test_cgamelibs test_cgamelibs.c)

# Link the library
target_link_libraries(test_cgamelibs PRIVATE cgamelibs)

# Specify the include directories for the test
target_include_directories(test_cgamelibs PRIVATE ../include)

# Enable testing
enable_testing()

# Optionally, add custom target to run tests
add_test(NAME test_cgamelibs COMMAND test_cgamelibs)
