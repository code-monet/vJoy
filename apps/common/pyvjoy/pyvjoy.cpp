#include <Windows.h>
#include <pybind11/pybind11.h>

#include "vjoyinterface.h"
#include "vjoymodern.h"

#pragma comment(lib, "vJoyInterfaceStat.lib")

namespace py = pybind11;

namespace pyvjoy {
PYBIND11_MODULE(pyvjoy, pyvjoy_m) {
  pyvjoy_m.doc() = "Python client library for VJoy";

  // Generic driver functions.
  pyvjoy_m.def("GetvJoyVersion", &vJoyNS::GetvJoyVersion,
               "Returns the version of the installed vJoy driver.");
  pyvjoy_m.def("vJoyEnabled", &vJoyNS::vJoyEnabled,
               "Returns True if vJoy is enabled.");
  pyvjoy_m.def("GetvJoyProductString", &vjoy_modern::GetvJoyProductString,
               "Returns the vJoy product string.");
  pyvjoy_m.def("GetvJoyManufacturerString",
               &vjoy_modern::GetvJoyManufacturerString,
               "Returns the vJoy manufacturer string.");
  pyvjoy_m.def("GetvJoySerialNumberString",
               &vjoy_modern::GetvJoySerialNumberString,
               "Returns the vJoy serial number string.");
  pyvjoy_m.def("DriverMatch", &vjoy_modern::DriverMatch,
               "Returns the vJoy library and driver versions if they match.");
  pyvjoy_m.def(
      "vJoyFfbCap", &vjoy_modern::vJoyFfbCap,
      "Returns true if force feedback is enabled (for all vJoy devices).");
  pyvjoy_m.def("GetvJoyMaxDevices", &vjoy_modern::GetvJoyMaxDevices,
               "Returns the maximum number of vJoy devices.");
  pyvjoy_m.def("GetNumberExistingVJD", &vjoy_modern::GetNumberExistingVJD,
               "Returns the number of active vJoy devices.");
  pyvjoy_m.def("ResetAll", &vJoyNS::ResetAll,
               "Resets all controls to predefined values in all vJoy devices.");

  // A single vJoy device.
  py::class_<vjoy_modern::VjoyDevice>(pyvjoy_m, "VjoyDevice")
      .def(py::init<int>())
      .def("GetOwnerPid", &vjoy_modern::VjoyDevice::GetOwnerPid);
}
}  // namespace pyvjoy