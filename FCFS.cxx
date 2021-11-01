#include "Process.cxx"
#include "tool.cxx"
#include <functional>
#include <algorithm>
#include <iostream>
#include <vector>

float Process::get_wait_time() const { return start_time - arrival_time; }

int main() {
  // Psuedo Processes
  Process P1{"A", 12.0f, 0.0f}; Process P2{"B", 4.0f, 3.0f};
  Process P3{"C", 9.0f, 5.0f};
  Process P4{"D", 2.0f, 7.0f};

  std::vector<std::reference_wrapper<Process>> processes{P1, P2, P3, P4};

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

  }
  
  print_process_table(processes);
  return 0;
}
