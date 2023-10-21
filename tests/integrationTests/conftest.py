import pytest
import os
import subprocess
import shutil


def pytest_addoption(parser):
    parser.addoption("--executable", action="store", default="default")

    parser.addoption("--input", action="store", default="run-01.in")

    parser.addoption("--name", action="store", default="default")


@pytest.fixture(scope="session")
def executable(pytestconfig):
    executable = pytestconfig.getoption("executable")

    if executable == "default":
        raise Exception("Please specify an executable for the executable.")

    return executable


@pytest.fixture(scope="session")
def test_dir(pytestconfig):
    executable = pytestconfig.getoption("name")

    if executable == "default":
        raise Exception("Please specify an name for the test directory.")

    return executable


@pytest.fixture(scope="class")
def input_file(pytestconfig):
    input_file = pytestconfig.getoption("input")

    return input_file


@pytest.fixture(scope="class")
def execute_pimd_qmcf(executable, input_file):

    dir = "temp"

    os.chdir("referenceData/cgo_mmmd")
    if (os.path.exists(dir) and os.path.isdir(dir)):
        shutil.rmtree(dir)
    os.mkdir(dir)

    shutil.copy(input_file, dir)
    # os.chdir(dir)

    # subprocess([executable, input_file])

    yield

    # os.chdir("..")
    shutil.rmtree(dir)
