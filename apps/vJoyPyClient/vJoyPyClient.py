"""Example script for the Python vJoy API.

Ensure that the pyvjoy.pyc file is available in your Python path. The easiest
way to do this may be to copy that file to the same directory as your script.
(The pyvjoy.pyc file in this example directory was manually built and copied).
"""

import pyvjoy


def PrintFnNameAndResult(fn, *args, **kwargs):
  print(fn.__name__, fn(*args, **kwargs))


def RunDemo():
  PrintFnNameAndResult(pyvjoy.GetvJoyVersion)
  PrintFnNameAndResult(pyvjoy.GetvJoyProductString)
  PrintFnNameAndResult(pyvjoy.GetvJoyManufacturerString)
  PrintFnNameAndResult(pyvjoy.GetvJoySerialNumberString)
  try:
    PrintFnNameAndResult(pyvjoy.DriverMatch)
  except RuntimeError as e:
    print(e)
  PrintFnNameAndResult(pyvjoy.vJoyFfbCap)
  PrintFnNameAndResult(pyvjoy.GetvJoyMaxDevices)
  PrintFnNameAndResult(pyvjoy.GetNumberExistingVJD)
  PrintFnNameAndResult(pyvjoy.ResetAll)

  vjoy_1 = pyvjoy.VjoyDevice(1)
  PrintFnNameAndResult(vjoy_1.GetOwnerPid)


if __name__ == '__main__':
    RunDemo()
