cmake_minimum_required(VERSION 3.16)
project(ScriptLib LANGUAGES C CXX)

if(CMAKE_SOURCE_DIR STREQUAL PROJECT_SOURCE_DIR)
    set(SCRIPTLIB_STANDALONE ON)
    set(CMAKE_CXX_STANDARD 17)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)
    set(CMAKE_CXX_EXTENSIONS OFF)
    option(BUILD_TESTING "Build ScriptLib tests" ON)
else()
    set(SCRIPTLIB_STANDALONE OFF)
endif()

if(SCRIPTLIB_STANDALONE)
    include(FetchContent)

    foreach(dep EterBase:pkg_eterbase EterLocale:pkg_eterlocale EterPack:pkg_eterpack EterImageLib:pkg_eterimagelib SphereLib:pkg_spherelib CWebBrowser:pkg_cwebbrowser EterLib:pkg_eterlib MilesLib:pkg_mileslib EterGrnLib:pkg_etergrnlib EffectLib:pkg_effectlib)
        string(REPLACE ":" ";" dep_list ${dep})
        list(GET dep_list 0 dep_name)
        list(GET dep_list 1 dep_repo)
        if(NOT TARGET ${dep_name})
            if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/../${dep_name}/CMakeLists.txt")
                set(BUILD_TESTING_SAVED ${BUILD_TESTING})
                set(BUILD_TESTING OFF CACHE BOOL "" FORCE)
                add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/../${dep_name}" "${CMAKE_BINARY_DIR}/deps/${dep_name}")
                set(BUILD_TESTING ${BUILD_TESTING_SAVED} CACHE BOOL "" FORCE)
            else()
                FetchContent_Declare(
                    ${dep_name}
                    GIT_REPOSITORY https://github.com/open-mt2/${dep_repo}.git
                    GIT_TAG main
                )
                set(BUILD_TESTING_SAVED ${BUILD_TESTING})
                set(BUILD_TESTING OFF CACHE BOOL "" FORCE)
                FetchContent_MakeAvailable(${dep_name})
                set(BUILD_TESTING ${BUILD_TESTING_SAVED} CACHE BOOL "" FORCE)
            endif()
        endif()
    endforeach()
endif()

# Locate Python 2.7
find_package(PythonLibs 2.7 QUIET)

if(NOT PYTHON_LIBRARIES)
    find_library(PYTHON_LIBRARIES NAMES python2.7 python27 libpython2.7 libpython27
        HINTS
            ${CMAKE_CURRENT_SOURCE_DIR}/../../extern/lib
            ${CMAKE_CURRENT_SOURCE_DIR}/../extern/lib
            ${CMAKE_CURRENT_SOURCE_DIR}/extern/lib
            ${CMAKE_SOURCE_DIR}/extern/lib
            /usr/lib
            /usr/lib/x86_64-linux-gnu
            /usr/local/lib
    )
endif()

if(NOT PYTHON_INCLUDE_DIRS)
    find_path(PYTHON_INCLUDE_DIRS NAMES python2.7/Python.h Python.h
        HINTS
            ${CMAKE_CURRENT_SOURCE_DIR}/include/python2.7
            ${CMAKE_CURRENT_SOURCE_DIR}/include
            ${CMAKE_CURRENT_SOURCE_DIR}/../../extern/include/python2.7
            ${CMAKE_CURRENT_SOURCE_DIR}/../../extern/include
            ${CMAKE_SOURCE_DIR}/extern/include/python2.7
            ${CMAKE_SOURCE_DIR}/extern/include
            /usr/include/python2.7
            /usr/include
    )
endif()

file(GLOB_RECURSE SCRIPTLIB_SOURCES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)

add_library(ScriptLib STATIC ${SCRIPTLIB_SOURCES})
add_library(OpenMT2::ScriptLib ALIAS ScriptLib)

target_include_directories(ScriptLib
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/ScriptLib>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/python2.7>
        $<INSTALL_INTERFACE:include>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        ${PYTHON_INCLUDE_DIRS}
)

target_link_libraries(ScriptLib
    PUBLIC
        EterBase
        EterPack
        EterLib
        EterGrnLib
        EffectLib
        ${PYTHON_LIBRARIES}
        util
        dl
)

if(UNIX)
    target_compile_definitions(ScriptLib PUBLIC __LINUX__ _GNU_SOURCE)
    target_compile_options(ScriptLib PUBLIC -Wno-register)
    if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
        target_compile_options(ScriptLib PUBLIC -Wno-macro-redefined)
    endif()
endif()

if((SCRIPTLIB_STANDALONE AND BUILD_TESTING) OR (NOT SCRIPTLIB_STANDALONE AND BUILD_TESTS))
    enable_testing()
    add_subdirectory(tests)
endif()
