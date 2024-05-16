#if defined(EDSMSVSBUILD)
#include "pch.h"
#else
#include "gtest/gtest.h"
#endif
#include "custom_gtest.hpp"
#include "private/eds_hash.hpp"
#include <memory>
class HashFT : public ::testing::Test {
   public:
     class TestSource {
          void (TestSource::*_method_ptr)();

        public:
          virtual void test_method() {}
          TestSource() : _method_ptr(&TestSource::test_method) {}
          size_t hash() const noexcept {
               return EDS hash2upper(reinterpret_cast<size_t>(this)) |
                      EDS hash2lower(reinterpret_cast<size_t>(&_method_ptr));
          }
     };

   protected:
     struct Sorter {
          bool operator()(const std::unique_ptr<TestSource> &obj1,
                          const std::unique_ptr<TestSource> &obj2) const {
               if (obj1->hash() == obj2->hash()) {
                    ++count_of_duplicates;
               }
               return obj1->hash() < obj2->hash();
          }

          mutable int count_of_duplicates = 0;
     };
     int found_duplicates = 0;
     std::vector<std::unique_ptr<TestSource>> _hashed_list;
     bool run_test() {
          for (int i = 0; i < 10000; i++) {
               _hashed_list.push_back(std::make_unique<TestSource>());
          }
          Sorter sorter;
          std::sort(_hashed_list.begin(), _hashed_list.end(), sorter);
          found_duplicates = sorter.count_of_duplicates;
          _hashed_list.clear();
          return found_duplicates;
     }
};

EDS_GTESTF(HashUGTest, HashFT, LookForDuplicates) {
     run_test();
     constexpr int expected_duplicates = 0;
     EDS_PROBE(EXPECT_EQ(expected_duplicates, found_duplicates)
               << "expect: " << expected_duplicates
               << " duplicates, found: " << found_duplicates << " duplicates.");
}
