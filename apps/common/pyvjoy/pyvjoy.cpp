#include <pybind11/pybind11.h>

#include <Windows.h>

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
  pyvjoy_m.def("GetNumberExistingVJD", &vjoy_modern::GetNumberExistingVJD,
               "Returns the number of active vJoy devices.");

  // A single vJoy device.
  py::class_<vjoy_modern::VjoyDevice>(pyvjoy_m, "VjoyDevice").def(py::init());
}
}  // namespace pyvjoy