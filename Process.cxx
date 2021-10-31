#ifndef PROCESS_CXX
#define PROCESS_CXX

// Process structure
class Process {
  float burst_time;
  float arrival_time;

  float execution_time{0.0f};

public:
  float start_time{0.0f};
  float stop_time{0.0f};

  Process(float p_burst_time, float p_arrival_time = 0.0f)
      : burst_time{p_burst_time}, arrival_time{p_arrival_time} {}

  float get_burst_time() const { return burst_time; }

  float get_arrival_time() const { return arrival_time; }

  float get_execution_time() const { return execution_time; }

  float get_completion_time() const {
    return execution_time + arrival_time + get_wait_time();
  }

  float get_turnaround_time() const {
    return get_completion_time() - arrival_time;
  }

  float get_wait_time() const;

  void execute() { ++execution_time; }
};

#endif // PROCESS_CXX
