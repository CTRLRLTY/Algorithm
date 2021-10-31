#include <vector>

float get_average(const std::vector<float> &v) {
  float acc{0.0f};

  for (auto &&e : v)
    acc += e;

  return acc / v.size();
}
