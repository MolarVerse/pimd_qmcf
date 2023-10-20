import numpy as np


def read_energy_file(filename):
    """Reads the energy file and returns all the data in it.

    Args:
        filename (str): The name of the file to read.

    Returns:
        np.array: collection of all the data in the file.
    """
    with open(filename, "r") as f:
        data = np.array([line.split() for line in f.readlines()], dtype=float)

    return data


def func():
    return 1
