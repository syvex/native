//
// Copyright (c) 2013 Mike Naquin. All rights reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//

#include "benchmark.h"

#include <chrono>
#include <fstream>

benchmark_test::benchmark_test(const char* fixture, const char* name,
                               std::size_t trial_count)
    : fixture(fixture)
    , name(name)
    , timers(trial_count)
{
}

void benchmark_test::SetUp() {}

void benchmark_test::TearDown() {}

void benchmark_test::report(const boost::timer::cpu_times& fastestElapsed,
                            const boost::timer::nanosecond_type& total,
                            const std::string& name)
{
    auto fastest = fastestElapsed.wall;
    auto average = (total / timers.size());
    double seconds = total / 1e9;

    std::ofstream ostr("benchmarks.csv", std::ios::app);

    ostr << name << ',' << fastest << ',' << average << std::endl;

    std::cout << "Fastest: " << fastest << " ns" << std::endl;
    std::cout << "Average: " << average << " ns" << std::endl;
    std::cout << "Total:   " << seconds << " s" << std::endl;
}
