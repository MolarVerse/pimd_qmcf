import subprocess


def execute(executable, inFile):
    process = subprocess.run([executable, inFile])
