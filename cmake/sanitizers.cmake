# Various sanitizers (runtime checks) for debugging
# Available with GCC and Clang on Linux and macOS (not on Windows yet)

option(SSP "Stack Smashing Protector" OFF) # Available on Windows too
option(UBSAN "Undefined Behavior Sanitizer" OFF)
option(ASAN "Address Sanitizer" OFF)
option(TSAN "Thread Sanitizer" OFF)

if (SSP)
    add_compile_options(-fstack-protector)
    add_link_options(-fstack-protector)
    message(STATUS "Enable Stack Smashing Protector")
endif(SSP)

if (ASAN OR UBSAN OR TSAN)
    add_compile_options(-fno-omit-frame-pointer)
    add_link_options(-fno-omit-frame-pointer)
endif()

if (UBSAN)
    add_compile_options(-fsanitize=undefined)
    add_link_options(-fsanitize=undefined)
    message(STATUS "Enabled Undefined Behavior Sanitizer")
endif(UBSAN)

if (ASAN)
    add_compile_options(-fsanitize=address)
    add_link_options(-fsanitize=address)
    message(STATUS "Enabled Address Sanitizer")
endif(ASAN)

if (TSAN)
    add_compile_options(-fsanitize=thread)
    add_link_options(-fsanitize=thread)
    message(STATUS "Enabled Thread Sanitizer")
endif(TSAN)
