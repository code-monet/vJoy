"""Example script for the Python vJoy API.

Ensure that the pyvjoy.pyc file is available in your Python path. The easiest
way to do this may be to copy that file to the same directory as your script.
(The pyvjoy.pyc file in this example directory was manually built and copied).
"""

import pyvjoy


def RunDemo():
  print(pyvjoy.GetvJoyVersion())
  print(pyvjoy.GetvJoyProductString())


if __name__ == '__main__':
    RunDemo()