#pragma once

#include <vector>

#include "all_type_variant.hpp"

namespace opossum {

// Hard-coded to test server
struct CalibrationConstantHardwareFeatures {
  size_t l1_size_kb = 32;
  size_t l1_block_size_kb = 0;
  size_t l2_size_kb = 256;
  size_t l2_block_size_kb = 0;
  size_t l3_size_kb = 38400;
  size_t l3_block_size_kb = 0;

  size_t memory_size_kb = 2113645780;
  size_t memory_access_bandwidth = 0;
  size_t memory_access_latency = 0;
  size_t num_cpu_cores = 60;
  size_t cpu_clock_speed_mhz = 3100;
  size_t num_numa_nodes = 4;

  size_t cpu_architecture = 0;  // Should be ENUM

  static const std::vector<std::string> columns;
};

inline const std::vector<std::string> CalibrationConstantHardwareFeatures::columns(
    {"l1_size_kb", "l1_block_size_kb", "l2_size_kb", "l2_block_size_kb", "l3_size_kb", "l3_block_size_kb",
     "memory_size_kb", "memory_access_bandwidth", "memory_access_latency", "num_cpu_cores", "cpu_clock_speed_mhz",
     "num_numa_nodes", "cpu_architecture"});

inline std::vector<AllTypeVariant> serialize(const CalibrationConstantHardwareFeatures& features) {
  return {static_cast<int32_t>(features.l1_size_kb),
          static_cast<int32_t>(features.l1_block_size_kb),
          static_cast<int32_t>(features.l2_size_kb),
          static_cast<int32_t>(features.l2_block_size_kb),
          static_cast<int32_t>(features.l3_size_kb),
          static_cast<int32_t>(features.l3_block_size_kb),
          static_cast<int32_t>(features.memory_size_kb),
          static_cast<int32_t>(features.memory_access_bandwidth),
          static_cast<int32_t>(features.memory_access_latency),
          static_cast<int32_t>(features.num_cpu_cores),
          static_cast<int32_t>(features.cpu_clock_speed_mhz),
          static_cast<int32_t>(features.num_numa_nodes),
          static_cast<int32_t>(features.cpu_architecture)};
}

}  // namespace opossum
