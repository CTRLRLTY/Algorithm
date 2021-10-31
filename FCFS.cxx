#include <algorithm>
#include <iostream>
#include <vector>
#include "Process.cxx"

float get_average(const std::vector<float> &v) {
  float acc{0.0f};

  for (auto &&e : v)
    acc += e;

  return acc / v.size();
}

int main() {
  // Psuedo Processes
  std::vector<Process> processes{
      {2.0f, 0.0f}, {6.0f, 1.0f}, {4.0f, 2.0f}, {9.0f, 3.0f}, {12.0f, 6.0f}};

  std::vector<float> wait_times;

  // Sort the processes by arrival_time
  std::sort(processes.begin(), processes.end(), [&](Process a, Process b) {
    return a.get_arrival_time() < b.get_arrival_time();
  });

  float time_accumulator = 0;
  for (Process &p : processes) {
    // allocate start time offset
    p.start_time = time_accumulator;

    // Run process till finish
    while (p.get_execution_time() < p.get_burst_time()) {
      ++time_accumulator;
      p.execute();
    }

    wait_times.push_back(p.get_wait_time());
  }

  std::cout << get_average(wait_times);

  return 0;
}
