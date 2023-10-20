import pytest
import utils.read as read


class TestMethod:

    i = 1

    @classmethod
    def setup_class(cls):
        cls.i += 1

    def test_test(self, executable):
        assert read.func() == self.i

    @classmethod
    def teardown_class(cls):
        cls.i -= 1
