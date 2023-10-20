find_package(Python COMPONENTS Interpreter REQUIRED)
find_package(Pytest REQUIRED)

add_test(NAME PythonTest
    COMMAND Pytest::Pytest --executable ${CMAKE_BINARY_DIR}/apps/pimd_qmcf ${CMAKE_CURRENT_SOURCE_DIR}/testsets/test.py
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)