#include "vjoymodern.h"

#include <Windows.h>

#include <exception>
#include <tuple>

#include "vjoyinterface.h"

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
}

int VjoyDevice::GetOwnerPid() { return vJoyNS::GetOwnerPid(device_index_); }
}  // namespace vjoy_modern