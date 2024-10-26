"""Example script for the Python vJoy API.

Ensure that the pyvjoy.pyc file is available in your Python path. The easiest
way to do this may be to copy that file to the same directory as your script.
(The pyvjoy.pyc file in this example directory was manually built and copied).
"""
import datetime
import time

import pyvjoy

SLEEP_BETWEEN_INPUTS = datetime.timedelta(milliseconds=100).total_seconds()


def SleepBetweenInputs(sleep_s=SLEEP_BETWEEN_INPUTS):
  time.sleep(sleep_s)
  

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
  PrintFnNameAndResult(vjoy_1.GetVJDStatus)

  # Acquire device and change some controls.
  # You can monitor these using JoyMonitor.exe.
  vjoy_1.AcquireVJD()
  try:
    for btn_i in range(1, vjoy_1.device_info.num_buttons + 1):
      vjoy_1.SetBtn(True, btn_i)
      SleepBetweenInputs()
    vjoy_1.ResetButtons()
    for pov_position in [-1, 0, 5_000, 10_000, 20_000, 30_000, 35_999]:
      for pov_i in range(1, vjoy_1.device_info.num_pov_hats + 1):
        vjoy_1.SetPov(pov_position, pov_i)
        SleepBetweenInputs()
    vjoy_1.ResetPovs()
    for axis_value in [-1, -0.5, 0, 0.5, 1]:
      for axis_i in range(1, vjoy_1.device_info.num_axes + 1):
        vjoy_1.SetAxisByNumber(axis_value, axis_i)
        SleepBetweenInputs()
    for axis_i in range(1, vjoy_1.device_info.num_axes + 1):
      # Note that there isn't a standard "rest" state for axes,
      # it depends on the device.
      vjoy_1.SetAxisByNumber(0, axis_i)
    vjoy_1.ResetVJD()
  finally:
    vjoy_1.RelinquishVJD()
  PrintFnNameAndResult(pyvjoy.ResetAll)


if __name__ == '__main__':
    RunDemo()
