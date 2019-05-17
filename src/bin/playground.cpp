#include <iostream>

#include <random>

#include "types.hpp"
#include "tpch/tpch_table_generator.hpp"
#include "operators/get_table.hpp"
#include "operators/aggregate_hashsort.hpp"
#include "operators/aggregate_hash.hpp"
#include "operators/aggregate_sort.hpp"
#include "operators/table_wrapper.hpp"
#include "operators/print.hpp"
#include "storage/table.hpp"
#include "table_generator.hpp"
#include "utils/timer.hpp"

using namespace opossum;  // NOLINT

std::shared_ptr<ValueSegment<int32_t>> make_segment(size_t row_count, int32_t min, int32_t max) {
  std::uniform_int_distribution<int32_t> dist{min, max};
  std::random_device rd;
  std::mt19937 gen(rd());

  std::vector<int32_t> values(row_count);

  for (auto i = size_t{0}; i < row_count; ++i) {
    values[i] = dist(gen);
  }

  return std::make_shared<ValueSegment<int32_t>>(std::move(values));
}

int main() {
  TableColumnDefinitions table_column_definitions;
  table_column_definitions.emplace_back("a", DataType::Int);
  table_column_definitions.emplace_back("b", DataType::Int);
  table_column_definitions.emplace_back("c", DataType::Int);

  const auto row_count = size_t{200'000};

  Segments segments;
  segments.emplace_back(make_segment(row_count, 0, 100));
  segments.emplace_back(make_segment(row_count, 0, 100));
  segments.emplace_back(make_segment(row_count, 0, 100));
  segments.emplace_back(make_segment(row_count, 0, 100));
  segments.emplace_back(make_segment(row_count, 0, 100));
  segments.emplace_back(make_segment(row_count, 0, 100));

  const auto table = std::make_shared<Table>(table_column_definitions, TableType::Data);
  table->append_chunk(segments);

  //Print::print(table);

//  Print::print(table);

  const auto table_op = std::make_shared<TableWrapper>(table);
  table_op->execute();

  auto aggregates = std::vector<AggregateColumnDefinition>{};
 // aggregates.emplace_back(ColumnID{2}, AggregateFunction::Sum);

  auto group_by_column_ids = std::vector<ColumnID>{};
  group_by_column_ids.emplace_back(ColumnID{0});
  group_by_column_ids.emplace_back(ColumnID{1});

  Timer t1;
  const auto aggregate_op2 = std::make_shared<AggregateHash>(table_op, aggregates, group_by_column_ids);
  aggregate_op2->execute();
  std::cout << "Hash: " << t1.lap_formatted() << std::endl;
  const auto aggregate_op = std::make_shared<AggregateHashSort>(table_op, aggregates, group_by_column_ids);
  aggregate_op->execute();
  std::cout << "HashSort: " << t1.lap_formatted() << std::endl;
  const auto aggregate_op3 = std::make_shared<AggregateSort>(table_op, aggregates, group_by_column_ids);
  aggregate_op3->execute();
  std::cout << "Sort: " << t1.lap_formatted() << std::endl;

  std::cout << "HashSort: " << aggregate_op->get_output()->row_count() << std::endl;
  std::cout << "Hash: " << aggregate_op2->get_output()->row_count() << std::endl;
  std::cout << "Sort: " << aggregate_op3->get_output()->row_count() << std::endl;

//  Print::print(aggregate_op->get_output());
//  Print::print(aggregate_op2->get_output());


  return 0;
}
