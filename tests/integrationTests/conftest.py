import pytest


def pytest_addoption(parser):
    parser.addoption("--executable", action="store", default="default")


@pytest.fixture(scope="session")
def executable(pytestconfig):
    executable = pytestconfig.getoption("executable")

    if executable == "default":
        Exception("Please specify a executable for the executable.")

    return executable
