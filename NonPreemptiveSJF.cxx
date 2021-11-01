#include "Process.cxx"
#include "tool.cxx"
#include <iostream>
#include <memory_resource>
#include <queue>
#include <vector>

float Process::get_wait_time() const { return start_time - arrival_time; }

int main() {
  // Psuedo Processes
  Process P1{"A", 12.0f, 0.0f};
  Process P2{"B", 4.0f, 3.0f};
  Process P3{"C", 9.0f, 5.0f};
  Process P4{"D", 2.0f, 7.0f};

  // Allocate a buffer on the stack
  char buffer[sizeof(Process) * 3];

  // assignable process alias
  using process_reference = std::reference_wrapper<Process>;

  // Assign pool
  std::pmr::monotonic_buffer_resource pool{std::data(buffer),
                                           std::size(buffer)};

  // Task queue
  std::pmr::deque<process_reference> task_queue{{P1, P2, P3, P4}, &pool};
  std::pmr::vector<process_reference> processes{{P1, P2, P3, P4}, &pool};

  // Sort by arrival time
  std::sort(task_queue.begin(), task_queue.end(), [&](Process a, Process b) {
    return a.get_arrival_time() < b.get_arrival_time();
  });

  int time_accumulator = 0;
  while (1) {

    // Consume the queue
    Process &active_process = task_queue.front();
    task_queue.pop_front();

    active_process.start_time = time_accumulator;

    // Execute the active process till last instruction
    while (active_process.get_execution_time() <
           active_process.get_burst_time()) {
      ++time_accumulator;
      active_process.execute();
    }

    // Break from main loop once no more task is left
    if (task_queue.empty())
      break;

    // Sort queue by burst_time
    std::sort(task_queue.begin(), task_queue.end(), [&](Process a, Process b) {
      return a.get_burst_time() < b.get_burst_time();
    });
  }

  print_process_table(processes);
  return 0;
}
