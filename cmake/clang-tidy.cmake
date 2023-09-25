find_program(CLANG_TIDY_PROGRAM clang-tidy-14 clang-tidy)
if(CLANG_TIDY_PROGRAM)
    execute_process(COMMAND ${CLANG_TIDY_PROGRAM} --version OUTPUT_VARIABLE CLANG_TIDY_VERSION_STRING)
    string(REGEX MATCH "LLVM version ([0-9A-Za-z]+)\\.([0-9A-Za-z\\.]+)" TIDY_VERSION "${CLANG_TIDY_VERSION_STRING}")
    set(TIDY_MAJOR_VERSION "${CMAKE_MATCH_1}")
    set(TIDY_VERSION "${CMAKE_MATCH_1}.${CMAKE_MATCH_2}")

    # We use NOLINTBEGIN and NOLINTEND to preserve some macros
    # This was only introduced in version 14
    if (TIDY_MAJOR_VERSION GREATER_EQUAL 14)
        # Add good checks which produce a minimal amount of false positives
        # One or two false positives can be dealt with using // NOLINT
        set(CMAKE_CXX_CLANG_TIDY ${CLANG_TIDY_PROGRAM} -checks=-*,cppcoreguidelines-macro-usage,hicpp-deprecated-headers,modernize-deprecated-headers,hicpp-use-override,hicpp-use-emplace,modernize-use-emplace,hicpp-use-auto,readability-container-size-empty,readability-implicit-bool-conversion,readability-redundant-smartptr-get,readability-qualified-auto,performance-unnecessary-value-param,modernize-make-unique,modernize-make-shared,misc-unused-using-decls,performance-move-const-arg,modernize-use-using,modernize-use-nullptr,modernize-deprecated-headers,modernize-loop-convert,misc-unused-using-decls,misc-static-assert,misc-redundant-expression,modernize-use-bool-literals,readability-delete-null-pointer,readability-redundant-member-init --warnings-as-errors=-*)
        message(STATUS "Enabled clang-tidy ${TIDY_VERSION}: ${CLANG_TIDY_PROGRAM}")
    else()
        message(WARNING "Found clang-tidy ${TIDY_VERSION}, but >=14 is required, thus disabled.")
    endif()
else(CLANG_TIDY_PROGRAM)
    message(WARNING "No clang-tidy found. Some checks are not enabled")
endif(CLANG_TIDY_PROGRAM)
