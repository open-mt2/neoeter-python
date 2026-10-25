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
    target_compile_options(test_eterpythonlib PRIVATE -Wno-register -Wno-macro-redefined)
endif()

add_test(NAME EterPythonLib_SmokeTests COMMAND test_eterpythonlib)
