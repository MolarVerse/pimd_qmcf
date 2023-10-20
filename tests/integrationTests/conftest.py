import pytest
import os
import subprocess


def pytest_addoption(parser):
    parser.addoption("--executable", action="store", default="default")

    parser.addoption("--input", action="store", default="run-01.in")


@pytest.fixture(scope="session")
def executable(pytestconfig):
    executable = pytestconfig.getoption("executable")

    if executable == "default":
        raise Exception("Please specify an executable for the executable.")

    return executable


@pytest.fixture(scope="class")
def input_file(pytestconfig):
    input_file = pytestconfig.getoption("input")

    return input_file


@pytest.fixture(scope="class")
def execute_pimd_qmcf(executable, input_file):
    os.mkdir("temp")
    os.chdir("temp")

    # subprocess([executable, input_file])

    yield

    os.chdir("..")
    os.rmdir("temp")
