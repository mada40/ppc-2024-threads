// Copyright 2023 Nesterov Alexander
#include <gtest/gtest.h>

#include <numeric>
#include <random>
#include <vector>

#include "stl/kashin_s_dijkstra_algorithm/include/Dijkstra.hpp"

#ifdef __APPLE__
const std::vector<int> TEST_CHECKS = {522, 1074, 3507, 6345};
#else
const std::vector<int> TEST_CHECKS = {299, 987, 3831, 6411};
#endif

TEST(KashinDijkstraStlTest, TestGraph10) {
  const int vertexCount = 10;
  const int edgeWeight = 100;
  const int start = 0;
  const int seed = 42;
  // создаем повторяющийся рандом
  std::mt19937 rng(seed);
  std::uniform_int_distribution<int> dist(1, edgeWeight);
  std::uniform_int_distribution<int> isEdge(0, 2);

  // Create data
  std::vector<int> in;
  in.reserve(vertexCount * vertexCount);
  std::vector<int> out(vertexCount);
  for (int i = 0; i < vertexCount * vertexCount; i++) {
    int weight = isEdge(rng) == 0 ? -1 : dist(rng);
    in.push_back(weight);
  }

  // Create TaskData
  std::shared_ptr<ppc::core::TaskData> taskDataStl = std::make_shared<ppc::core::TaskData>();
  taskDataStl->inputs.emplace_back(reinterpret_cast<uint8_t *>(in.data()));
  taskDataStl->inputs_count.emplace_back(in.size());
  taskDataStl->inputs_count.emplace_back(start);
  taskDataStl->outputs.emplace_back(reinterpret_cast<uint8_t *>(out.data()));
  taskDataStl->outputs_count.emplace_back(out.size());

  // Create Task
  KashinDijkstraStl::Dijkstra dijkstra(taskDataStl);
  ASSERT_EQ(dijkstra.validation(), true);
  dijkstra.pre_processing();
  dijkstra.run();
  dijkstra.post_processing();
  ASSERT_EQ(TEST_CHECKS[0], std::accumulate(out.begin(), out.end(), 0));
}

TEST(KashinDijkstraStlTest, CheckingIncorrectInputData) {
  const int vertexCount = 10;
  const int edgeWeight = 10000;
  const int start = -1;
  const int seed = 42;
  // создаем повторяющийся рандом
  std::mt19937 rng(seed);
  std::uniform_int_distribution<int> dist(1, edgeWeight);
  std::uniform_int_distribution<int> isEdge(0, 2);

  // Create data
  std::vector<int> in;
  in.reserve(vertexCount * vertexCount);
  std::vector<int> out(vertexCount);
  for (int i = 0; i < vertexCount * vertexCount; i++) {
    int weight = isEdge(rng) == 0 ? -1 : dist(rng);
    in.push_back(weight);
  }

  // Create TaskData
  std::shared_ptr<ppc::core::TaskData> taskDataStl = std::make_shared<ppc::core::TaskData>();
  taskDataStl->inputs.emplace_back(reinterpret_cast<uint8_t *>(in.data()));
  taskDataStl->inputs_count.emplace_back(in.size());
  taskDataStl->inputs_count.emplace_back(start);
  taskDataStl->outputs.emplace_back(reinterpret_cast<uint8_t *>(out.data()));
  taskDataStl->outputs_count.emplace_back(out.size());

  // Create Task
  KashinDijkstraStl::Dijkstra dijkstra(taskDataStl);
  ASSERT_EQ(dijkstra.validation(), false);
}

TEST(KashinDijkstraStlTest, TestGraph100) {
  const int vertexCount = 100;
  const int edgeWeight = 100;
  const int start = 0;
  const int seed = 42;
  // создаем повторяющийся рандом
  std::mt19937 rng(seed);
  std::uniform_int_distribution<int> dist(1, edgeWeight);
  std::uniform_int_distribution<int> isEdge(0, 2);

  // Create data
  std::vector<int> in;
  in.reserve(vertexCount * vertexCount);
  std::vector<int> out(vertexCount);
  for (int i = 0; i < vertexCount * vertexCount; i++) {
    int weight = isEdge(rng) == 0 ? -1 : dist(rng);
    in.push_back(weight);
  }

  // Create TaskData
  std::shared_ptr<ppc::core::TaskData> taskDataStl = std::make_shared<ppc::core::TaskData>();
  taskDataStl->inputs.emplace_back(reinterpret_cast<uint8_t *>(in.data()));
  taskDataStl->inputs_count.emplace_back(in.size());
  taskDataStl->inputs_count.emplace_back(start);
  taskDataStl->outputs.emplace_back(reinterpret_cast<uint8_t *>(out.data()));
  taskDataStl->outputs_count.emplace_back(out.size());

  // Create Task
  KashinDijkstraStl::Dijkstra dijkstra(taskDataStl);
  ASSERT_EQ(dijkstra.validation(), true);
  dijkstra.pre_processing();
  dijkstra.run();
  dijkstra.post_processing();
  ASSERT_EQ(TEST_CHECKS[1], std::accumulate(out.begin(), out.end(), 0));
}

TEST(KashinDijkstraStlTest, TestGraph1000) {
  const int vertexCount = 1000;
  const int edgeWeight = 100;
  const int start = 0;
  const int seed = 42;
  // создаем повторяющийся рандом
  std::mt19937 rng(seed);
  std::uniform_int_distribution<int> dist(1, edgeWeight);
  std::uniform_int_distribution<int> isEdge(0, 2);

  // Create data
  std::vector<int> in;
  in.reserve(vertexCount * vertexCount);
  std::vector<int> out(vertexCount);
  for (int i = 0; i < vertexCount * vertexCount; i++) {
    int weight = isEdge(rng) == 0 ? -1 : dist(rng);
    in.push_back(weight);
  }

  // Create TaskData
  std::shared_ptr<ppc::core::TaskData> taskDataStl = std::make_shared<ppc::core::TaskData>();
  taskDataStl->inputs.emplace_back(reinterpret_cast<uint8_t *>(in.data()));
  taskDataStl->inputs_count.emplace_back(in.size());
  taskDataStl->inputs_count.emplace_back(start);
  taskDataStl->outputs.emplace_back(reinterpret_cast<uint8_t *>(out.data()));
  taskDataStl->outputs_count.emplace_back(out.size());

  // Create Task
  KashinDijkstraStl::Dijkstra dijkstra(taskDataStl);
  ASSERT_EQ(dijkstra.validation(), true);
  dijkstra.pre_processing();
  dijkstra.run();
  dijkstra.post_processing();
  ASSERT_EQ(TEST_CHECKS[2], std::accumulate(out.begin(), out.end(), 0));
}

TEST(KashinDijkstraStlTest, TestGraph10000) {
  const int vertexCount = 2000;
  const int edgeWeight = 100;
  const int start = 0;
  const int seed = 42;
  // создаем повторяющийся рандом
  std::mt19937 rng(seed);
  std::uniform_int_distribution<int> dist(1, edgeWeight);
  std::uniform_int_distribution<int> isEdge(0, 2);

  // Create data
  std::vector<int> in;
  in.reserve(vertexCount * vertexCount);
  std::vector<int> out(vertexCount);
  for (int i = 0; i < vertexCount * vertexCount; i++) {
    int weight = isEdge(rng) == 0 ? -1 : dist(rng);
    in.push_back(weight);
  }

  // Create TaskData
  std::shared_ptr<ppc::core::TaskData> taskDataStl = std::make_shared<ppc::core::TaskData>();
  taskDataStl->inputs.emplace_back(reinterpret_cast<uint8_t *>(in.data()));
  taskDataStl->inputs_count.emplace_back(in.size());
  taskDataStl->inputs_count.emplace_back(start);
  taskDataStl->outputs.emplace_back(reinterpret_cast<uint8_t *>(out.data()));
  taskDataStl->outputs_count.emplace_back(out.size());

  // Create Task
  KashinDijkstraStl::Dijkstra dijkstra(taskDataStl);
  ASSERT_EQ(dijkstra.validation(), true);
  dijkstra.pre_processing();
  dijkstra.run();
  dijkstra.post_processing();
  ASSERT_EQ(TEST_CHECKS[3], std::accumulate(out.begin(), out.end(), 0));
}
