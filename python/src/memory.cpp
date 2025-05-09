// Copyright © 2025 Apple Inc.

#include "mlx/memory.h"
#include <nanobind/nanobind.h>

namespace mx = mlx::core;
namespace nb = nanobind;
using namespace nb::literals;

void init_memory(nb::module_& m) {
  m.def(
      "get_active_memory",
      &mx::get_active_memory,
      R"pbdoc(
      Get the actively used memory in bytes.

      Note, this will not always match memory use reported by the system because
      it does not include cached memory buffers.
      )pbdoc");
  m.def(
      "get_peak_memory",
      &mx::get_peak_memory,
      R"pbdoc(
      Get the peak amount of used memory in bytes.

      The maximum memory used recorded from the beginning of the program
      execution or since the last call to :func:`reset_peak_memory`.
      )pbdoc");
  m.def(
      "reset_peak_memory",
      &mx::reset_peak_memory,
      R"pbdoc(
      Reset the peak memory to zero.
      )pbdoc");
  m.def(
      "get_cache_memory",
      &mx::get_cache_memory,
      R"pbdoc(
      Get the cache size in bytes.

      The cache includes memory not currently used that has not been returned
      to the system allocator.
      )pbdoc");
  m.def(
      "set_memory_limit",
      &mx::set_memory_limit,
      "limit"_a,
      R"pbdoc(
      Set the memory limit.

      The memory limit is a guideline for the maximum amount of memory to use
      during graph evaluation. If the memory limit is exceeded and there is no
      more RAM (including swap when available) allocations will result in an
      exception.

      When metal is available the memory limit defaults to 1.5 times the
      maximum recommended working set size reported by the device.

      Args:
        limit (int): Memory limit in bytes.

      Returns:
        int: The previous memory limit in bytes.
      )pbdoc");
  m.def(
      "set_cache_limit",
      &mx::set_cache_limit,
      "limit"_a,
      R"pbdoc(
      Set the free cache limit.

      If using more than the given limit, free memory will be reclaimed
      from the cache on the next allocation. To disable the cache, set
      the limit to ``0``.

      The cache limit defaults to the memory limit. See
      :func:`set_memory_limit` for more details.

      Args:
        limit (int): The cache limit in bytes.

      Returns:
        int: The previous cache limit in bytes.
      )pbdoc");
  m.def(
      "set_wired_limit",
      &mx::set_wired_limit,
      "limit"_a,
      R"pbdoc(
      Set the wired size limit.

      .. note::
         * This function is only useful on macOS 15.0 or higher.
         * The wired limit should remain strictly less than the total
           memory size.

      The wired limit is the total size in bytes of memory that will be kept
      resident. The default value is ``0``.

      Setting a wired limit larger than system wired limit is an error. You can
      increase the system wired limit with:

      .. code-block::

        sudo sysctl iogpu.wired_limit_mb=<size_in_megabytes>

      Use :func:`device_info` to query the system wired limit
      (``"max_recommended_working_set_size"``) and the total memory size
      (``"memory_size"``).

      Args:
        limit (int): The wired limit in bytes.

      Returns:
        int: The previous wired limit in bytes.
      )pbdoc");
  m.def(
      "clear_cache",
      &mx::clear_cache,
      R"pbdoc(
      Clear the memory cache.

      After calling this, :func:`get_cache_memory` should return ``0``.
      )pbdoc");
}
