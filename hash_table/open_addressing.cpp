#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cstdlib>
#include <ctime>


const unsigned HASH_TBL_SIZE = 500;

enum CellStatus {
  FREE = 0,
  OCCUPIED = 1,
  DELETED = 2
};

using hash_func = size_t (*)(const std::string&, size_t);

class HashTable {
  std::vector<std::pair<std::string, CellStatus>> table;
  hash_func hasher;


public:
  HashTable(hash_func);
  bool insert(std::string elem);
  void print();
  void display_load();
  void display_runs();
  bool search(const std::string& elem);
  void remove(const std::string& elem);

};

HashTable::HashTable(hash_func hasher) {
  this->hasher = hasher;
  this->table.resize(HASH_TBL_SIZE);
}

bool HashTable::insert(std::string elem) {
  size_t hash_val = hasher(elem, HASH_TBL_SIZE);
  size_t trials = table.size();
  size_t cur_idx;

  while (trials) {
    cur_idx = hash_val % HASH_TBL_SIZE;
    if (table[cur_idx].second != OCCUPIED) {
      table[cur_idx].first = std::move(elem);
      table[cur_idx].second = OCCUPIED;
      return true;
    }

    trials--;
    hash_val++;
  }

  return false;
}

void HashTable::print() {
  for (auto& elem : this->table) {
    if (elem.second == OCCUPIED) {
      std::cout << elem.first << " ";
    }
  }
  std::cout << std::endl;
}

void HashTable::display_load() {
  for (auto& elem : this->table) {
    std::cout << (elem.second == OCCUPIED ? "*" : " ");
  }
  std::cout << "## END ##" << std::endl;
}

size_t simple_hash(const std::string& elem, size_t size) {
  size_t hash_val = 0;
  for (int i = 0; i < elem.size(); i++) {
    hash_val += (i+1)*elem[i];
  }

  return hash_val % HASH_TBL_SIZE;
}

bool HashTable::search(const std::string& elem) {
  size_t hash_val = hasher(elem, HASH_TBL_SIZE);
  size_t trials = table.size();
  size_t cur_idx;

  while(trials) {
    cur_idx = hash_val % HASH_TBL_SIZE;
    if (table[cur_idx].second == FREE) {
      return false;
    } else if (table[cur_idx].second == OCCUPIED && table[cur_idx].first == elem) {
      return true;
    }

    trials--;
    hash_val++;
  }

  return false;
}

void HashTable::remove(const std::string& elem) {
  size_t hash_val = hasher(elem, HASH_TBL_SIZE);
  size_t trials = table.size();
  size_t cur_idx;

  while(trials) {
    cur_idx = hash_val % HASH_TBL_SIZE;
    if (table[cur_idx].second == FREE) {
      return;
    } else if (table[cur_idx].second == OCCUPIED && table[cur_idx].first == elem) {
      table[cur_idx].second = DELETED;
    }

    trials--;
    hash_val++;
  }
}

void HashTable::display_runs() {
  bool is_full = true;
  for (int i = 0; i < table.size(); ) {
    if (table[i].second == FREE) {
      is_full = false;
      size_t trials = table.size();
      while (trials && i < table.size()) {
        if (table[i].second == FREE || table[i].second == DELETED) {
          i++;
        } else {
          break;
        }

        trials--;
      }

      if (trials && (i < table.size() || table[0].second == OCCUPIED)) {
        bool is_last = i >= table.size();

        int start = i % HASH_TBL_SIZE;
        trials = table.size();
        size_t run_size = 0;

        while (trials) {
          i = i % HASH_TBL_SIZE;
          if (table[i].second == FREE) {
            break;
          }

          i++;
          run_size++;
          trials--;
        }

        std::cout << "Run Start: " << start << ", Length: " << run_size << std::endl;

        if (is_last || start + run_size >= table.size()) {
          return;
        }

      } else {
        i++;
      }
      
    } else {
      i++;
    }
  }

  if (is_full) {
    std::cout << "Run Start: 0, Length: " << table.size() << std::endl;
  }

}


std::string generateRandomString(int maxLength = 5) {
  // CHAT-GPT Generated
  const std::string chars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
  int length = rand() % (maxLength + 1);
  std::string randomString;

  for (int i = 0; i < length; ++i) {
    randomString += chars[rand() % chars.size()];
  }

  return randomString;
}


int main() {
  HashTable htbl(&simple_hash);
  htbl.insert("hello");
  htbl.insert("bye");
  htbl.insert("world");

  std::cout << "Content: ";
  htbl.print();

  std::string str1 = "bye";
  std::cout << "DOES TABLE CONTAIN " << str1 << "? " << (htbl.search(str1) ? "YES!" : "NO!") << std::endl;

  std::string str2 = "table";
  std::cout << "DOES TABLE CONTAIN " << str2 << "? " << (htbl.search(str2) ? "YES!" : "NO!") << std::endl;

  htbl.remove("bye");
  std::cout << "After Removal: ";
  htbl.print();

  srand(static_cast<unsigned>(time(0)));
  for (int i = 0; i < 350; i++) {
    std::string randomStr = generateRandomString();
    htbl.insert(randomStr);
  }

  std::cout << "Displaying Load Below" << std::endl;
  htbl.display_load();
  htbl.display_runs();

  return 0;
}
