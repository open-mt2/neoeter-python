add_executable(test_eterpythonlib
    test_eterpythonlib.cpp
)

target_link_libraries(test_eterpythonlib
    PRIVATE
        EterPythonLib
        ScriptLib
        EterLib
        EterGrnLib
        EffectLib
        EterPack
        EterBase
        ${PYTHON_LIBRARIES}
        util
        dl
)

target_include_directories(test_eterpythonlib
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../include
        ${CMAKE_CURRENT_SOURCE_DIR}/../include/EterPythonLib
        ${CMAKE_CURRENT_SOURCE_DIR}/../include/python2.7
)

if(UNIX)
    target_compile_definitions(test_eterpythonlib PRIVATE __LINUX__ _GNU_SOURCE)
    target_compile_options(test_eterpythonlib PRIVATE -Wno-register)
    if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
        target_compile_options(test_eterpythonlib PRIVATE -Wno-macro-redefined)
    endif()
endif()

add_test(NAME EterPythonLib_SmokeTests COMMAND test_eterpythonlib)

# TA.1: shared test helpers and always-on asserts (tests/support/TestAssert.h)
foreach(_test_target test_eterpythonlib)
    target_include_directories(${_test_target} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
    target_compile_options(${_test_target} PRIVATE $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-UNDEBUG>)
endforeach()
