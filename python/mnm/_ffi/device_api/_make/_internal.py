from mnm._lib import _APIS

# pylint: disable=invalid-name
# Defined in ./src/device_api/cpu/cpu.cc
cpu = _APIS.get("mnm.device_api._make.cpu", None)
# Defined in ./src/device_api/cuda/cuda.cc
cuda = _APIS.get("mnm.device_api._make.cuda", None)