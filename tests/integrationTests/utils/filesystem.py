import os


def create_temp_dir():
    """Create a temporary directory and return its path."""
    os.mkdir("temp")
    os.chdir("temp")


def delete_temp_dir():
    """Delete the temporary directory."""
    os.chdir("..")
    os.rmdir("temp")
