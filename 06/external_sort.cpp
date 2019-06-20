//
// Created by David Davitadze on 20/06/2019.
//

// файл сортируется следующим способом:
// 1) зачитываем файл чанками размером с ram
//    и сортируем, сохраняем в промежуточные файлы
// 2) разделяем каждый промежуточный файл на n кусков,
//    зачитываем память каждый первый кусок + выделяем свободное место
//    для выходного массива; делаем merge sort, как только какой то кусочек заканчивается,
//    читаем следующий, как только кусочек для выходного массива заканчивается,
//    выгружаем в выходной файл

#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <sys/stat.h>
#include <memory>
#include <future>

const uint64_t RAM_SIZE  = 1000 * sizeof(uint64_t);
const uint64_t NB_THREADS = 2;

void parallel_sort(std::vector<uint64_t>* data, size_t left, size_t right) {
  int min_len = std::max(256, int((right - left)/NB_THREADS));

  if(right - left < min_len) {
    std::sort(data->begin() + left, data->begin() + right);
  } else if (left < right) {
    size_t mid = (left + right)/2;

    auto future = std::async(parallel_sort, data, left, mid);
    parallel_sort(data, mid + 1,  right);

    future.wait();

    std::inplace_merge(data->begin() + left, data->begin() + mid, data->begin() + right);
  }
}

void read_chunk(std::ifstream& in_file, size_t chunk_size, std::vector<uint64_t>& buffer) {
  uint64_t buffer_value;

  for (size_t i = 0; i < chunk_size; ++i) {
    if (in_file >> buffer_value) {
      buffer[i] = buffer_value;
    }
    else if (in_file.peek() == EOF) {
      buffer[i] = std::numeric_limits<uint64_t>::max();
    }
    else {
      throw std::runtime_error("couldn't read input");
    }
  }
}

uint64_t sort_chunks(const std::string& in_filename, const std::string& out_dir) {
  std::ifstream in_file(in_filename, std::ifstream::binary);
  if (not in_file) {
    throw std::runtime_error("couldn't open file");
  }

  const uint64_t chunk_size = RAM_SIZE / sizeof(uint64_t);
  std::vector<uint64_t> buffer(chunk_size);

  uint64_t counter = 0;
  while (in_file.peek() != EOF) {
    read_chunk(in_file, chunk_size, buffer);

    //std::sort(buffer.begin(), buffer.end());
    parallel_sort(&buffer, 0, buffer.size() - 1);

    std::ofstream out_file(out_dir + std::string("out") + std::to_string(counter) + std::string(".txt"));
    for (const auto &element : buffer) out_file << element << "\n";

    ++counter;
  }

  return counter;
}

void external_sort(const std::string& in_dir, uint64_t num_of_chunks, const std::string& out_filename) {
  // open all temporary files
  std::vector<std::unique_ptr<std::ifstream>> in_files(num_of_chunks);
  for (size_t i = 0; i < num_of_chunks; ++i) {
    in_files[i] = std::make_unique<std::ifstream>(in_dir
                                                      + std::string("out")
                                                      + std::to_string(i)
                                                      + std::string(".txt"));
    if (not in_files[i]) {
      throw std::runtime_error("couldn't open file");
    }
  }

  // load first chunks from all temporary files
  const uint64_t chunk_size = RAM_SIZE / sizeof(uint64_t) / (num_of_chunks + 1);
  std::vector<std::vector<uint64_t>> in_buffers(num_of_chunks);
  for (size_t i = 0; i < num_of_chunks; ++i) {
    in_buffers[i] = std::vector<uint64_t>(chunk_size);

    read_chunk(*in_files[i], chunk_size, in_buffers[i]);
  }

  std::ofstream out_file(out_filename);
  if (not out_file) {
    throw std::runtime_error("couldn't open file");
  }

  std::vector<uint64_t> out_buffer(chunk_size);
  std::vector<size_t> indexes(num_of_chunks + 1, 0);

  // perform k way merge sort
  for (size_t i = 0; i < num_of_chunks * RAM_SIZE / sizeof(uint64_t); ++i) {
    size_t least_index = 0;
    for (size_t j = 1; j < num_of_chunks; ++j) {
      if (in_buffers[j][indexes[j]] < in_buffers[least_index][indexes[least_index]]) {
        least_index = j;
      }
    }

    out_buffer[indexes[num_of_chunks]] = in_buffers[least_index][indexes[least_index]];
    ++indexes[num_of_chunks];
    ++indexes[least_index];

    if(indexes[num_of_chunks] == chunk_size) {
      for (const auto &element : out_buffer) out_file << element << "\n";
      indexes[num_of_chunks] = 0;
    }
    if(indexes[least_index] == chunk_size) {
      read_chunk(*in_files[least_index], chunk_size, in_buffers[least_index]);
      indexes[least_index] = 0;
    }
  }

  if(indexes[num_of_chunks] != 0) {
    size_t counter = 0;
    for (const auto &element : out_buffer) {
      if(counter < indexes[num_of_chunks]) out_file << element << "\n";
      ++counter;
    }
  }
}