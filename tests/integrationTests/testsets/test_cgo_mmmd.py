import pytest
import utils.read as read
import os
import numpy as np


@pytest.mark.usefixtures("execute_pimd_qmcf")
class TestCGOMMMD:

    def test_check_all_files(self):
        list_files = os.listdir()
        list_files = list(file for file in list_files if os.path.isfile(file))

        endings = [".en", ".xyz"]

        print(list_files)

        for ending in endings:
            assert len(
                list(filter(lambda x: x.endswith(ending), list_files))) == 1

        assert list_files

    def test_energy_file(self):
        ref_energy_file_data = read.energy_file("../output.en")
        energy_file_data = read.energy_file("output.en")
        np.testing.assert_allclose(
            ref_energy_file_data[:, :-1], energy_file_data[:, :-1])
