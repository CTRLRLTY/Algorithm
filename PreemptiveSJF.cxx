#include "Process.cxx"
#include "tool.cxx"
#include <iostream>
#include <memory_resource>
#include <queue>
#include <vector>

float Process::get_wait_time() const {
  return stop_time - execution_time - arrival_time;
}

int main() {
  // Psuedo Processes
  Process P1{12.0f, 0.0f};
  Process P2{4.0f, 3.0f};
  Process P3{9.0f, 5.0f};
  Process P4{2.0f, 7.0f};

  // Allocate a buffer on the stack
  char buffer[sizeof(Process) * 3 * 2];

  // assignable process alias
  using process_reference = std::reference_wrapper<Process>;

  // Assign pool
  std::pmr::monotonic_buffer_resource pool{std::data(buffer),
                                           std::size(buffer)};

  // Task queue
  std::pmr::deque<process_reference> processes{{P1, P2, P3, P4}, &pool};
  decltype(processes) task_queue;

  // Sort by arrival time
  std::sort(processes.begin(), processes.end(), [&](Process a, Process b) {
    return a.get_arrival_time() < b.get_arrival_time();
  });

  // Add the initial process with least arrival_time to task
  task_queue.push_back(processes.front());

  std::vector<float> wait_times;

  float time_accumulator{0.0f};

  // Naive execution loop
  while (1) {
    ++time_accumulator;

    // Consume the queue
    Process &active_process = task_queue.front();

    active_process.execute();

    // Remove from queue if the current process has finished
    if (active_process.get_execution_time() >=
        active_process.get_burst_time()) {
      active_process.stop_time = time_accumulator;
      task_queue.pop_front();
      wait_times.push_back(active_process.get_wait_time());
    }

    // Break from main loop once no more task is left
    if (task_queue.empty())
      break;

    // Poll process arrival
    auto result =
        std::find_if(processes.begin(), processes.end(), [&](Process p) {
          return p.get_arrival_time() == time_accumulator;
        });

    // Add process to task_queue if new process has arrived
    if (result != std::end(processes))
      task_queue.push_back(*result);

    // Sort the task_queue by least burst_time
    std::sort(task_queue.begin(), task_queue.end(), [&](Process a, Process b) {
      return a.get_burst_time() - a.get_execution_time() <
             b.get_burst_time() - b.get_execution_time();
    });
  }

  // Print average wait
  std::cout << get_average(wait_times) << std::endl;

  return 0;
}
