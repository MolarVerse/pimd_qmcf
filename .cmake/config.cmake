# **********
# BUILD TYPE
# **********
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "RelWithDebug" CACHE STRING "Build type" FORCE)
endif()

set(CMAKE_BUILD_TYPES "Debug" "RelWithDebug" "Release")
set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS ${CMAKE_BUILD_TYPES})

# *****************
# shared vs. static
# *****************
option(BUILD_SHARED_LIBS "Build using shared libraries" ON)

# **************
# INSTALL PREFIX
# **************
if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR}/install)
endif()

# **************
# BUILD WITH MPI
# **************
option(BUILD_WITH_MPI "Build with MPI" OFF)

# ***********
# BUILD TOOLS
# ***********
option(BUILD_TOOLS "Build tools" OFF)

# ***************
# BUILD WITH IWYU
# ***************
option(BUILD_WITH_IWYU "Build with include-what-you-use" OFF)

# ***************
# BUILD WITH DOCS
# ***************
option(BUILD_WITH_DOCS "Build documentation" ON)

# ***********************
# BUILD WITH BENCHMARKING
# ***********************
option(BUILD_WITH_BENCHMARKING "Build benchmarking" OFF)

# ***************
# Testing options
# ***************
option(BUILD_WITH_TESTS "Build tests" ON)
option(BUILD_WITH_INTEGRATION_TESTS "Build integration tests" OFF)