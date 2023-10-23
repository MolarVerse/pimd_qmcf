import numpy as np


def energy_file(filename):
    """Reads the energy file and returns all the data in it.

    Args:
        filename (str): The name of the file to read.

    Returns:
        np.array: collection of all the data in the file.
    """
    data = np.loadtxt(filename, dtype=float)

    return data
