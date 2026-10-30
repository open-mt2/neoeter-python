add_executable(test_scriptlib test_scriptlib.cpp)

target_link_libraries(test_scriptlib
    PRIVATE
        ScriptLib
)

add_test(NAME ScriptLib_SmokeTests COMMAND test_scriptlib)

# TA.1: shared test helpers and always-on asserts (tests/support/TestAssert.h)
foreach(_test_target test_scriptlib)
    target_include_directories(${_test_target} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
    target_compile_options(${_test_target} PRIVATE $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-UNDEBUG>)
endforeach()
