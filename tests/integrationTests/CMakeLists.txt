find_package(Python COMPONENTS Interpreter REQUIRED)
find_package(Pytest REQUIRED)

add_test(NAME PythonTest
    COMMAND Pytest::Pytest ${CMAKE_CURRENT_SOURCE_DIR}/testsets/test.py --executable ${CMAKE_BINARY_DIR}/apps/pimd_qmcf
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)