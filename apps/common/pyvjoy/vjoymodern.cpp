#include "vjoymodern.h"

#include <exception>
#include <Windows.h>

#include "vjoyinterface.h"

namespace vjoy_modern {
std::wstring GetvJoyProductString() {
  std::wstring product_string;
  PVOID result = vJoyNS::GetvJoyProductString();
  if (result) {
    auto product_str_ptr = reinterpret_cast<PWSTR>(result);
    product_string.assign(product_str_ptr);
    free(product_str_ptr);
    return product_string;
  }
  throw std::runtime_error("Could not retrieve vJoy product string");
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
}  // namespace vjoy_modern