find_package(Python COMPONENTS Interpreter REQUIRED)
find_package(Pytest REQUIRED)

set(TEST_NAME cgo_mmmd)
add_test(NAME ${TEST_NAME}
    COMMAND
<<<<<<< HEAD
    Pytest::Pytest
    ${CMAKE_CURRENT_SOURCE_DIR}/testsets/test_${TEST_NAME}.py
    --executable ${CMAKE_BINARY_DIR}/apps/pimd_qmcf
    --name ${TEST_NAME}
    WORKING_DIRECTORY
    ${CMAKE_CURRENT_SOURCE_DIR}
=======
    Pytest::Pytest ${CMAKE_CURRENT_SOURCE_DIR}/testsets/test_${TEST_NAME}.py --executable ${CMAKE_BINARY_DIR}/apps/pimd_qmcf --name ${TEST_NAME}
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
>>>>>>> ec0a8b94d80893214a767160da3ac1cf1f98a797
)
