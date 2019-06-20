//
// Created by David Davitadze on 16/06/2019.
//

#ifndef INC_06_EXTERNAL_SORT_HPP
#define INC_06_EXTERNAL_SORT_HPP

#include <string>
#include <fstream>

void read_chunk(std::ifstream& in_file, size_t chunk_size, std::vector<uint64_t>& buffer);
uint64_t sort_chunks(const std::string& in_filename, const std::string& out_dir);

void external_sort(const std::string& in_dir, uint64_t num_of_chunks, const std::string& out_filename);

#endif //INC_06_EXTERNAL_SORT_HPP
