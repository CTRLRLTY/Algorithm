#include "Process.cxx"
#include "tool.cxx"
#include <functional>
#include <iostream>
#include <queue>

float Process::get_wait_time() const {
  return stop_time - execution_time - arrival_time;
}

int main() {
  // Quantum time
  const float time_slice{4.0f};

  Process P1{"A", 12.0f, 0.0f};
  Process P2{"B", 4.0f, 3.0f};
  Process P3{"C", 9.0f, 5.0f};
  Process P4{"D", 2.0f, 7.0f};

  // Convert reference to assignable
  std::vector<std::reference_wrapper<Process>> processes{P1, P2, P3, P4};
  std::queue<std::reference_wrapper<Process>> task_queue;

  std::sort(processes.begin(), processes.end(), [&](Process a, Process b) {
    return a.get_arrival_time() < b.get_arrival_time();
  });

  task_queue.push(processes.front());

  int time_accumulator = 0;

  // Main loop
  while (1) {
    // Consume queue
    Process &active_process = task_queue.front();
    task_queue.pop();

    // Execute the process till time_slice is up
    for (int i = 0; i < time_slice; ++i) {
      ++time_accumulator;

      active_process.execute();

      // Poll process arrival
      auto result =
          std::find_if(processes.begin(), processes.end(), [&](Process p) {
            return p.get_arrival_time() == time_accumulator;
          });

      if (result != std::end(processes)) 
        task_queue.push(*result);

      // break out if process execution is finished
      if (active_process.get_execution_time() ==
          active_process.get_burst_time())
        break;
    }

    // Stop scheduling the process if they have completed their execution
    if (active_process.get_execution_time() < active_process.get_burst_time())
      task_queue.push(active_process);
    else 
      // Record it's timer offset
      active_process.stop_time = time_accumulator;

    // Main breakout condition
    //  exit the main loop if there's no more task
    if (task_queue.empty())
      break;
  }

  print_process_table(processes);
  return 0;
}
