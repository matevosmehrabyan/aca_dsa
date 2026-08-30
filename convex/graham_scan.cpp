#include <iostream>
#include <vector>
#include <random>
#include <stack>
#include <algorithm>

std::pair<int, int> mid;
std::pair<int, int> rmost;


std::pair<int, int> get_mid(const std::vector<std::pair<int, int>>& points) {
  std::pair<int, int> mid(0,0);
  for (auto& point : points) {
    mid.first += point.first;
    mid.second += point.second;
  }

  mid.first /= points.size();
  mid.second /= points.size();

  return mid;
}

std::pair<int, int> get_rmost(const std::vector<std::pair<int, int>>& points) {
  std::vector<std::pair<int, int>> tmp;
  int max =points[0].first;
  for (auto& point : points) {
    if (point.first > max) {
      tmp.clear();
      tmp.push_back(point);
    } else if (point.first == max) {
      tmp.push_back(point);
    }
  }

  max = tmp[0].second;
  std::vector<std::pair<int, int>> tmp2;
  for (auto& point : tmp) {
    if (point.first > max) {
      tmp2.clear();
      tmp2.push_back(point);
    } else if (point.first == max) {
      tmp2.push_back(point);
    }
  }

  return tmp2[0];
}

bool is_right_turn(std::pair<int, int>& p1, std::pair<int, int>& p2, std::pair<int, int>& p3) {
  return (p2.first - p1.first)*(p3.second - p1.second)
         - (p2.second - p1.second)*(p3.first - p1.first) <= 0;
}

void graham_scan(std::vector<std::pair<int, int>>& points) {
  std::stack<std::pair<int, int>> ch;
  
}


int main() {
  std::vector<std::pair<int, int>> points;
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dis(0, 20);
  for (int i = 0; i < 20; i++) {
    points.push_back({dis(gen), dis(gen)});
  }

  std::sort(points.begin(), points.end(), [](const std::pair<int, int>& a, const std::pair<int, int>& b) {
        return static_cast<double>(a.first - rmost.first) / a.second - rmost.second
               < static_cast<double>(b.first - rmost.first) / b.second - rmost.second;
    });

  for (int i = 0; i < 20; i++) {
    std::cout << "(" << points[i].first << "," << points[i].second << ") ";
  }

  graham_scan(points);

  return 0;
}