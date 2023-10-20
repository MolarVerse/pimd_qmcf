import pytest
import utils.read as read
import utils.filesystem as fs
import utils.execute as execute


class TestMethod:

    i = 1

    @pytest.fixture(scope="class", autouse=True)
    def setup(self, executable):
        self.i += 1
        yield
        print("teardown_class called")

    def test_test(self):
        print("hallo")
        assert read.func() == self.i
