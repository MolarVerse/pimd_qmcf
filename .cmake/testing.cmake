enable_testing()
option(INSTALL_GMOCK "install Googletest's GMock?" OFF)
option(INSTALL_GTEST "install Googletest's GTest?" OFF)
find_package(GTest CONFIG) # use googletest

if(NOT ${GTest_FOUND})
    message("GTest not found. Fetching...")
    include(FetchContent)
    FetchContent_Declare(
        gtest
        GIT_REPOSITORY "https://github.com/google/googletest"
        GIT_TAG main
    )

    # For Windows: Prevent overriding the parent project's compiler/linker settings
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(gtest)
else()
    MESSAGE(STATUS "aaa ${gtest_SOURCE_DIR}")
    include_directories(${GTEST_SOURCE_DIR}/include ${GMOCK_SOURCE_DIR}/include ${GTEST_SOURCE_DIR} ${GMOCK_SOURCE_DIR})
endif()

list(APPEND CMAKE_CTEST_ARGUMENTS "--output-on-failure")

if(NOT ${CMAKE_BUILD_TYPE} MATCHES "^[Rr]elease")
    include(gcovr)

    include(CodeCoverage)
    set(EXCLUDE_FOR_GCOVR
        "\.build"
        tests
        build/_deps # don't know why build
        apps
        external
        benchmarks
        tools
        src/setup/setup.cpp
        src/engine/*
        include/engine/*
    )

    setup_target_for_coverage_gcovr_html(
        NAME coverage
        EXECUTABLE ctest
        EXCLUDE ${EXCLUDE_FOR_GCOVR}
    )

    setup_target_for_coverage_gcovr_xml(
        NAME coverage_xml
        EXECUTABLE ctest
        EXCLUDE ${EXCLUDE_FOR_GCOVR}
    )

    setup_target_for_coverage_lcov(
        NAME coverage_lcov EXECUTABLE ctest LCOV_ARGS " --no-external " EXCLUDE tests* _deps* apps* external* apps* benchmarks* build* .build*)
endif()

# add_subdirectory(tests)