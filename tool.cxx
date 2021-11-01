#include "Process.cxx"
#include <iostream>
#include <vector>

float get_average(const std::vector<float> &v) {
  float acc{0.0f};

  for (auto &&e : v)
    acc += e;

  return acc / v.size();
}

template<typename T>
void print_process_table(const T &v) {
  constexpr char hseperator[] = "  --  ";
  std::vector<float> wait_times;
  for (Process &p : v) {
    wait_times.push_back(p.get_wait_time());
    std::cout << p.get_name() << " --> " 
              << "burst_time: " << p.get_burst_time() << hseperator
              << "arrival_time: " << p.get_arrival_time() << hseperator
              << "completion_time: " << p.get_completion_time() << hseperator
              << "turnaround_time: " << p.get_turnaround_time() << hseperator
              << "wait_time: " << p.get_wait_time() << std::endl;
  }

  std::cout << "==================================\n";   
  std::cout << "average_waiting_time: " << get_average(wait_times) << std::endl; 
}
