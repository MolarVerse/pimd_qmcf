import pytest
import utils.read as read


@pytest.mark.usefixtures("execute_pimd_qmcf")
class TestMethod:

    i = 1

    def test_test(self):
        assert read.func() == self.i + 1

    def test_test2(self):
        assert read.func() == self.i + 2
