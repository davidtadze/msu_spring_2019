#include <iostream>

#include "external_sort.hpp"

int main() {
  uint64_t num_of_chunks =
      sort_chunks(std::string("/Users/daviddavitadze/Develop/tehnosphere/advanced-cpp/msu_spring_2019/06/in.txt"),
                  std::string("/Users/daviddavitadze/Develop/tehnosphere/advanced-cpp/msu_spring_2019/06/"));

  external_sort(std::string("/Users/daviddavitadze/Develop/tehnosphere/advanced-cpp/msu_spring_2019/06/"), num_of_chunks,
                std::string("/Users/daviddavitadze/Develop/tehnosphere/advanced-cpp/msu_spring_2019/06/out.txt"));

  return 0;
}