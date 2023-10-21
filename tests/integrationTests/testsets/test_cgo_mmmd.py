import pytest
import utils.read as read
import os


@pytest.mark.usefixtures("execute_pimd_qmcf")
class TestCGOMMMD:

    def test_check_all_files(self):
        list_files = map(str, os.listdir())

        endings = [".en", ".xyz"]
        # endings = [".in"]

        for ending in endings:
            assert len(
                list(filter(lambda x: x.endswith(ending), list_files))) == 1

        assert list_files
