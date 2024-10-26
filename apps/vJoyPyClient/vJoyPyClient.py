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
  print('vJoy device 1 num buttons:', vjoy_1.device_info.num_buttons)
  print('vJoy device 1 num axes:', vjoy_1.device_info.num_axes)
  print('Axes usage by position:', vjoy_1.device_info.axis_usage_by_position)
  print('Axes min values:', vjoy_1.device_info.axis_min_by_position)
  print('Axes max values:', vjoy_1.device_info.axis_max_by_position)
  print('vJoy device 1 num POV hats:', vjoy_1.device_info.num_pov_hats)
  print('POV continuous hats:', vjoy_1.device_info.hat_is_continuous)


if __name__ == '__main__':
    RunDemo()
