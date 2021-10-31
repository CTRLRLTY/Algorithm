#include "Process.cxx"
#include "tool.cxx"
#include <functional>
#include <iostream>
#include <queue>

float Process::get_wait_time() const { return stop_time - execution_time; }

int main() {
  const float time_slice{2.0f};

  Process P1{4.0f};
  Process P2{3.0f};
  Process P3{5.0f};

  std::vector<std::reference_wrapper<Process>> processes{P1, P2, P3};
  std::queue<std::reference_wrapper<Process>> task_queue;

  std::vector<float> wait_times;
  wait_times.reserve(3);

  for (auto &&p : processes)
    task_queue.push(p);

  int time_accumulator = 0;

  while (1) {
    Process &active_process = task_queue.front();
    task_queue.pop();

    for (int i = 0; i < time_slice; ++i) {
      ++time_accumulator;

      active_process.execute();

      if (active_process.get_execution_time() ==
          active_process.get_burst_time())
        break;
    }

    if (active_process.get_execution_time() < active_process.get_burst_time())
      task_queue.push(active_process);
    else {
      active_process.stop_time = time_accumulator;
      wait_times.push_back(active_process.get_wait_time());
    }

    if (task_queue.empty())
      break;
  }

  std::cout << get_average(wait_times) << std::endl;

  return 0;
}
