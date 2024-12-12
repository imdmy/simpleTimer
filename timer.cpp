/*
name: timer.cpp
author: mingo
date: 2024/12/12
description: a simple timer program but use some modern C++ features, awesome!
*/
#include <chrono>
#include <format>
#include <iostream>
#include <thread>

static long long unsuck_start_time =
    std::chrono::high_resolution_clock::now().time_since_epoch().count();

inline double now() {
  auto now = std::chrono::high_resolution_clock::now();
  long long nanosSinceStart =
      now.time_since_epoch().count() - unsuck_start_time;

  double secondsSinceStart = double(nanosSinceStart) / 1'000'000'000.0;

  return secondsSinceStart;
}

template <typename... Args>
inline void printfmt(std::string_view fmt, const Args &...args) {
#ifdef __cpp_lib_format
  struct thousandsSeparator : std::numpunct<char> {
    char_type do_thousands_sep() const override { return '\''; }
    string_type do_grouping() const override { return "\3"; }
  };
  auto thousands = std::make_unique<thousandsSeparator>();
  auto locale = std::locale(std::cout.getloc(), thousands.release());

  std::cout << std::vformat(locale, fmt, std::make_format_args(args...));
#else
  std::cout << fmt::vformat(fmt, fmt::make_format_args(args...));
#endif
}

double t_start = 0.0; // time when the started , initialized to 0.0

int main() {
  t_start = now();
  printfmt("start at {:.3f} \n", t_start);
  std::this_thread::sleep_for(std::chrono::milliseconds(1000));
  printfmt("end at {:.3f} \n", now());
}