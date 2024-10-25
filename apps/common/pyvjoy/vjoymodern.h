// Wraps VJoyInterface with a modern C++ object-oriented interface.

#pragma once

#include <exception>
#include <format>
#include <string>

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
int GetNumberExistingVJD();

struct VjoyDeviceInfo {
  int num_buttons;
  int num_axes;
  int num_pov_hats;
};

// All the functions in this class will throw runtime error if they can't
// communicate with the driver.
class VjoyDevice {
 public:
  // Initialize with the given device number (1-indexed).
  // Throws InvalidArgumentError if specified device does not exist.
  explicit VjoyDevice(int device_number);

  void SetBtn(int index);

 private:
  const int device_index_;
};
}  // namespace vjoy_modern