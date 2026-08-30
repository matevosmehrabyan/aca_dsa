#include <iostream>
#include <vector>
#include <unordered_map>


int main() {
  std::vector<std::vector<int>> matrix {
  {1, 1, 1, 1},
  {1, 1, 1, 1},
  {1, 0, 1, 1},
  {1, 1, 1, 1}
  };

  std::vector<std::vector<int>> result;
  for (int i = 0; i < matrix.size(); i++) {
    result.push_back(std::vector<int>(matrix.size()));
  }

  result[result.size() - 1][result.size() - 1] = matrix[matrix.size() -1][matrix.size() - 1] ? 1 : 0;
  for (int i = matrix.size() - 2; i >= 0; i--) {
    if (!matrix[matrix.size() - 1][i]) {
      break;
    }
    result[matrix.size() - 1][i] = 1;
  }

  for (int i = matrix.size() - 2; i >= 0; i--) {
    if (!matrix[i][matrix.size() - 1]) {
      break;
    }
    result[i][matrix.size() - 1] = 1;
  }

  for (int i = matrix.size() - 2; i >= 0; i--) {
    for (int j = matrix.size() - 2; j >= 0; j--) {
      
      if (matrix[i][j] == 0) {
        continue;
      }

      result[i][j] = result[i + 1][j] + result[i][j + 1];
    }
  }


  for (int i = 0; i < result.size(); i++) {
    for (int j = 0; j < result.size(); j++) {
      std::cout << result[i][j] << " ";
    }
    std::cout << std::endl;
  }



  return 0;
}