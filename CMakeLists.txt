cmake_minimum_required(VERSION 3.20)
project(NeoeterPython VERSION 0.1.0 LANGUAGES C CXX)

# Python 2.7 host + bindings. See docs/architecture.md.
#
# This repository is a consumer of neoeter and a producer for client. When it is
# configured standalone it fetches neoeter; inside the devkit the targets
# already exist.

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(NEOETER_PYTHON_STANDALONE "Build Neoeter Python on its own" OFF)

if(NEOETER_PYTHON_STANDALONE)
    include(FetchContent)
    FetchContent_Declare(neoeter
        GIT_REPOSITORY https://github.com/open-mt2/neoeter.git
        GIT_TAG main)
    set(BUILD_TESTING_SAVED ${BUILD_TESTING})
    set(BUILD_TESTING OFF CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(neoeter)
    set(BUILD_TESTING ${BUILD_TESTING_SAVED} CACHE BOOL "" FORCE)
endif()

foreach(_package IN ITEMS ScriptLib EterPythonLib)
    if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/src/${_package}/CMakeLists.txt")
        # Keep the historic build/src/<Package> location: golden-check.sh and
        # the API snapshot tests resolve their binaries through it.
        add_subdirectory("src/${_package}" "${CMAKE_BINARY_DIR}/src/${_package}")
    else()
        message(STATUS "Neoeter Python: src/${_package} not imported yet")
    endif()
endforeach()

if(TARGET ScriptLib AND NOT TARGET NeoeterPython::Script)
    add_library(NeoeterPython_Script INTERFACE)
    target_link_libraries(NeoeterPython_Script INTERFACE ScriptLib)
    add_library(NeoeterPython::Script ALIAS NeoeterPython_Script)
endif()

if(TARGET EterPythonLib AND NOT TARGET NeoeterPython::Bindings)
    add_library(NeoeterPython_Bindings INTERFACE)
    target_link_libraries(NeoeterPython_Bindings INTERFACE EterPythonLib)
    add_library(NeoeterPython::Bindings ALIAS NeoeterPython_Bindings)
endif()
