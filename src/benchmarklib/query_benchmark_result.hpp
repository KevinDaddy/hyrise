#pragma once

#include "sql/sql_pipeline.hpp"
#include <atomic>

#include "benchmark_config.hpp"

namespace opossum {

struct QueryBenchmarkResult : public Noncopyable {
  QueryBenchmarkResult();

  QueryBenchmarkResult(QueryBenchmarkResult&& other) noexcept;

  QueryBenchmarkResult& operator=(QueryBenchmarkResult&&) = default;

  std::atomic<size_t> num_iterations = 0;
  Duration duration = Duration{};
  tbb::concurrent_vector<std::shared_ptr<SQLPipelineMetrics>> metrics;

  std::optional<bool> verification_passed;
};

}  // namespace opossum
