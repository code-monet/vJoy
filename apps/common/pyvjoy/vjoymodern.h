// Wraps VJoyInterface with a modern C++ object-oriented interface.

#pragma once

#include <array>
#include <exception>
#include <format>
#include <string>
#include <tuple>
#include <Windows.h>

namespace vjoy_modern {

template <typename T>
class InvalidArgumentError : public std::invalid_argument {
 public:
  InvalidArgumentError(const char* error_msg, const T& argument)
      : std::invalid_argument(error_msg), argument_(argument) {}
  const char* what() {
    return std::format("{}: {}", std::string(std::runtime_error::what()),
                       argument_);
  }

 private:
  T argument_;
};

// All the following functions will throw runtime error if they can't
// communicate with the driver or get an invalid response.
std::wstring GetvJoyProductString();
std::wstring GetvJoyManufacturerString();
std::wstring GetvJoySerialNumberString();
// Returns a tuple of the DLL version and driver version if matching.
// Raises runtime error if the driver doesn't match the library.
std::tuple<WORD, WORD> DriverMatch();
bool vJoyFfbCap();
int GetvJoyMaxDevices();
int GetNumberExistingVJD();

struct VjoyDeviceInfo {
  int num_buttons_;
  int num_axes_;
  int num_pov_hats_;
  static constexpr int kMaxHats = 4;  // DirectInput limit.
  std::array<bool, kMaxHats> hat_is_continuous_;
  static constexpr int kMaxAxes = 8;  // DirectInput limit.
  std::array<UINT, kMaxAxes> axis_usage_by_position_;
  std::array<LONG, kMaxAxes> axis_min_by_position_;
  std::array<LONG, kMaxAxes> axis_max_by_position_;
};

// All the functions in this class will throw runtime error if they can't
// communicate with the driver.
class VjoyDevice {
 public:
  // Initialize with the given device number (1-indexed).
  // Throws InvalidArgumentError if specified device does not exist.
  explicit VjoyDevice(int device_number);
  // Returns a copy - suitable for Python binding.
  VjoyDeviceInfo device_info() const;

  // Negative values indicate no owner or an error condition.
  // See GetOwnerPid in vJoyInterface.cpp for details.
  int GetOwnerPid() const;

 private:
  const int device_index_;
  VjoyDeviceInfo device_info_;
};
}  // namespace vjoy_modern