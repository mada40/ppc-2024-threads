// Copyright 2024 Makhinya Danil
#include <gtest/gtest.h>

#include <functional>
#include <vector>

#include "omp/makhinya_d_hoare_sort_batcher_merge/include/hoare_sort_omp.hpp"

class MakhinyaDTestSort : public ::testing::Test {
 public:
  HoareSortOMP testTaskSequential;
  const uint32_t COUNT = 128;

  MakhinyaDTestSort() : testTaskSequential{HoareSortOMP(std::make_shared<ppc::core::TaskData>())} {}

  void set_data(HoareSortOMP::vec_t* in_vec, HoareSortOMP::compare_t* in_comp = nullptr) {
    std::shared_ptr<ppc::core::TaskData> taskDataSeq = std::make_shared<ppc::core::TaskData>();

    taskDataSeq->inputs.emplace_back(reinterpret_cast<uint8_t*>(in_vec));
    taskDataSeq->inputs_count.emplace_back(1);

    if (in_comp != nullptr) {
      taskDataSeq->inputs.emplace_back(reinterpret_cast<uint8_t*>(in_comp));
      taskDataSeq->inputs_count.emplace_back(1);
    }

    taskDataSeq->outputs.emplace_back(nullptr);
    taskDataSeq->outputs_count.emplace_back(0);

    testTaskSequential.set_data(taskDataSeq);
  }

  bool run_test() {
    if (!testTaskSequential.validation()) {
      return false;
    }

    testTaskSequential.pre_processing();
    testTaskSequential.run();
    testTaskSequential.post_processing();
    bool isSorted = testTaskSequential.check_order();
    return isSorted;
  }
};

TEST_F(MakhinyaDTestSort, Reverse_Vec) {
  HoareSortOMP::vec_t in_vec(COUNT);

  srand(time(nullptr));
  for (uint32_t i = 0; i < COUNT; ++i) {
    in_vec[i] = static_cast<HoareSortOMP::sortable_type>(COUNT - i);
  }

  set_data(&in_vec);
  EXPECT_TRUE(run_test());
}

TEST_F(MakhinyaDTestSort, Sorted_Vec) {
  HoareSortOMP::vec_t in_vec(COUNT);

  srand(time(nullptr));
  for (uint32_t i = 0; i < COUNT; ++i) {
    in_vec[i] = static_cast<HoareSortOMP::sortable_type>(i);
  }

  set_data(&in_vec);
  EXPECT_TRUE(run_test());
}

TEST_F(MakhinyaDTestSort, EQ_Vec) {
  HoareSortOMP::vec_t in_vec(COUNT);

  srand(time(nullptr));
  for (uint32_t i = 0; i < COUNT; ++i) {
    in_vec[i] = static_cast<HoareSortOMP::sortable_type>(COUNT);
  }

  set_data(&in_vec);
  EXPECT_TRUE(run_test());
}

TEST_F(MakhinyaDTestSort, Random_Vec) {
  HoareSortOMP::vec_t in_vec(COUNT);

  srand(time(nullptr));
  for (HoareSortOMP::sortable_type& x : in_vec) {
    x = static_cast<HoareSortOMP::sortable_type>(rand());
  }

  set_data(&in_vec);
  EXPECT_TRUE(run_test());
}

TEST_F(MakhinyaDTestSort, Random_Vec_With_Comp) {
  HoareSortOMP::vec_t in_vec(COUNT);

  HoareSortOMP::compare_t in_comp = [](const HoareSortOMP::sortable_type& a,
                                       const HoareSortOMP::sortable_type& b) -> bool {
    if ((a & 1) != (b & 1)) return (a & 1) < (b & 1);
    return a > b;
  };

  srand(time(nullptr));
  for (HoareSortOMP::sortable_type& x : in_vec) {
    x = static_cast<HoareSortOMP::sortable_type>(rand());
  }

  set_data(&in_vec, &in_comp);
  EXPECT_TRUE(run_test());
}
