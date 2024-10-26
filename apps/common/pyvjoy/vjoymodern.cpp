#include "vjoymodern.h"

#include <Windows.h>

#include <exception>
#include <format>
#include <tuple>

#include "public.h"
#include "vjoyinterface.h"

namespace {
static constexpr int kMaxAxisUsages = 17;
static constexpr std::array<UINT, kMaxAxisUsages> kAxisUsages = {
    HID_USAGE_X,      HID_USAGE_Y,           HID_USAGE_Z,
    HID_USAGE_RX,     HID_USAGE_RY,          HID_USAGE_RZ,
    HID_USAGE_SL0,    HID_USAGE_SL1,         HID_USAGE_WHL,
    HID_USAGE_POV,    HID_USAGE_ACCELERATOR, HID_USAGE_BRAKE,
    HID_USAGE_CLUTCH, HID_USAGE_STEERING,    HID_USAGE_AILERON,
    HID_USAGE_RUDDER, HID_USAGE_THROTTLE};
}  // anonymous namespace.

namespace vjoy_modern {
std::wstring GetvJoyProductString() {
  PVOID result = vJoyNS::GetvJoyProductString();
  if (result) {
    auto product_str_ptr = reinterpret_cast<PWSTR>(result);
    std::wstring product_string(product_str_ptr);
    free(product_str_ptr);
    return product_string;
  }
  throw std::runtime_error("Could not retrieve vJoy product string");
}

std::wstring GetvJoyManufacturerString() {
  PVOID result = vJoyNS::GetvJoyManufacturerString();
  if (result) {
    auto mfg_str_ptr = reinterpret_cast<PWSTR>(result);
    std::wstring mfg_str(mfg_str_ptr);
    free(mfg_str_ptr);
    return mfg_str;
  }
  throw std::runtime_error("Could not retrieve vJoy manufacturer string");
}

std::wstring GetvJoySerialNumberString() {
  PVOID result = vJoyNS::GetvJoySerialNumberString();
  if (result) {
    auto serial_str_ptr = reinterpret_cast<PWSTR>(result);
    std::wstring serial_str(serial_str_ptr);
    free(serial_str_ptr);
    return serial_str;
  }
  throw std::runtime_error("Could not retrieve vJoy serial number string");
}

std::tuple<WORD, WORD> DriverMatch() {
  WORD dll_version;
  WORD driver_version;
  if (vJoyNS::DriverMatch(&dll_version, &driver_version)) {
    return std::tuple<WORD, WORD>(dll_version, driver_version);
  }
  throw std::runtime_error("DLL/Library and driver versions do not match");
}

bool vJoyFfbCap() {
  BOOL ffb_enabled;
  if (vJoyNS::vJoyFfbCap(&ffb_enabled)) {
    return static_cast<bool>(ffb_enabled);
  }
  throw std::runtime_error("Could not query driver for FFB enabled state.");
}

int GetvJoyMaxDevices() {
  int max_devices;
  if (vJoyNS::GetvJoyMaxDevices(&max_devices)) {
    return max_devices;
  }
  throw std::runtime_error(
      "Could not query driver for maximum number of vJoy devices.");
}

int GetNumberExistingVJD() {
  int num_vjds = 0;
  if (vJoyNS::GetNumberExistingVJD(&num_vjds)) {
    return num_vjds;
  }
  throw std::runtime_error("Could not retrieve number of active vJoy devices.");
}

VjoyDevice::VjoyDevice(int device_number) : device_index_(device_number) {
  if (!vJoyNS::isVJDExists(device_number)) {
    throw InvalidArgumentError<int>("vJoy device does not exist",
                                    device_number);
  }
  // Buttons.
  device_info_.num_buttons_ = vJoyNS::GetVJDButtonNumber(device_index_);
  if (device_info_.num_buttons_ < 0) {
    throw std::runtime_error(
        "Could not query number of buttons for vJoy device");
  }
  // The following logic should be correct for mixed type hats, although the
  // vJoy configuration tool only allows for all hats to be of the same type.
  // Discrete hats.
  device_info_.num_pov_hats_ = vJoyNS::GetVJDDiscPovNumber(device_index_);
  if (device_info_.num_pov_hats_ < 0) {
    throw std::runtime_error(
        "Could not query number of discrete POV hats for vJoy device");
  }
  for (int i = 0; i < device_info_.num_pov_hats_; ++i) {
    device_info_.hat_is_continuous_[i] = false;
  }
  // Continuous hats.
  auto num_continous_pov_hats = vJoyNS::GetVJDContPovNumber(device_index_);
  if (num_continous_pov_hats < 0) {
    throw std::runtime_error(
        "Could not query number of continuous POV hats for vJoy device");
  }
  for (int i = 0; i < num_continous_pov_hats; ++i) {
    device_info_.hat_is_continuous_[device_info_.num_pov_hats_ + i] = true;
  }
  device_info_.num_pov_hats_ += num_continous_pov_hats;
  // Axes.
  device_info_.num_axes_ = 0;
  for (auto usage : kAxisUsages) {
    if (vJoyNS::GetVJDAxisExist(device_index_, usage)) {
      LONG axis_min;
      if (!vJoyNS::GetVJDAxisMin(
              device_index_, usage,
              &axis_min)) {
        // Axes not enabled still show up as present, but don't return ranges.
        break;
      }
      LONG axis_max;
      if (!vJoyNS::GetVJDAxisMax(
              device_index_, usage,
              &axis_max)) {
        // Not expected - should have encountered break in the previous if block.
        break;
      }
      auto axis_i = device_info_.num_axes_;
      device_info_.axis_usage_by_position_[axis_i] = usage;
      device_info_.axis_min_by_position_[axis_i] = axis_min;
      device_info_.axis_max_by_position_[axis_i] = axis_max;
      device_info_.num_axes_ += 1;
      if (device_info_.num_axes_ == VjoyDeviceInfo::kMaxAxes) {
        // Axes not enabled still show up as present, stop if at max.
        break;
      }
    }
  }
}

VjoyDeviceInfo VjoyDevice::device_info() const { return device_info_; }

int VjoyDevice::GetOwnerPid() const {
  return vJoyNS::GetOwnerPid(device_index_);
}
}  // namespace vjoy_modern