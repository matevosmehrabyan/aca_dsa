#include <iostream>
#include <vector>
#include <algorithm>
#include <forward_list>


const unsigned HASH_TBL_SIZE = 20;

using hash_func = size_t (*)(const std::string&, size_t);

class HashTable {
  std::vector<std::forward_list<std::string>> table;
  hash_func hasher;


public:
  HashTable(hash_func);
  void insert(std::string elem);
  void print();
  bool search(const std::string& elem);
  void remove(const std::string& elem);

};

HashTable::HashTable(hash_func hasher) {
  this->hasher = hasher;
  this->table.resize(HASH_TBL_SIZE);
}

void HashTable::insert(std::string elem) {
  size_t hash_val = hasher(elem, HASH_TBL_SIZE);
  if (std::find(table[hash_val].begin(), table[hash_val].end(), elem) == table[hash_val].end()) {
    table[hash_val].push_front(elem);
  }
}

void HashTable::print() {
  for (auto& list : this->table) {
    for (const auto& elem : list) {
      std::cout << elem << " ";
    }
  }
  std::cout << std::endl;
}

size_t simple_hash(const std::string& elem, size_t size) {
  size_t hash_val = 0;
  for (int i = 0; i < elem.size(); i++) {
    hash_val += (i+1)*elem[i];
  }

  return hash_val % 20;
}

bool HashTable::search(const std::string& elem) {
  size_t hash_val = hasher(elem, HASH_TBL_SIZE);
  return std::find(table[hash_val].begin(), table[hash_val].end(), elem) != table[hash_val].end();
}

void HashTable::remove(const std::string& elem) {
  size_t hash_val = hasher(elem, HASH_TBL_SIZE);
  table[hash_val].remove(elem);
}


int main() {
  HashTable htbl(&simple_hash);
  htbl.insert("hello");
  htbl.insert("hello");
  htbl.insert("world");
  htbl.print();

  std::cout << "has word hello: " << htbl.search("hello") << std::endl;
  std::cout << "has word bye: " << htbl.search("bye") << std::endl;

  htbl.remove("hello");
  std::cout << "has word hello: " << htbl.search("hello") << std::endl;



  return 0;
}
