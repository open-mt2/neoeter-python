add_executable(test_scriptlib test_scriptlib.cpp)

target_link_libraries(test_scriptlib
    PRIVATE
        ScriptLib
)

add_test(NAME ScriptLib_SmokeTests COMMAND test_scriptlib)
