// Copyright 2019 Alexander Liniger

// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at

//     http://www.apache.org/licenses/LICENSE-2.0

// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////

#ifndef PATH_PROCESSING_CONFIG_H
#define PATH_PROCESSING_CONFIG_H

#include <math.h>
#include <iostream>
#include <fstream>
#include <string>
#include <Eigen/Dense>

namespace mpcc {
namespace path_processing {

// Number of points for spline resampling
static constexpr int N_SPLINE = 5000;

// Simple position state for path projection
struct SimpleState {
    double X;    // X position
    double Y;    // Y position
    double s;    // arc length parameter
};

// Spline parameters needed for arc length spline
struct SplineParams {
    double max_dist_proj;  // Maximum distance for projection
    
    SplineParams() : max_dist_proj(1.0) {}
    SplineParams(double max_dist) : max_dist_proj(max_dist) {}
};

}  // namespace path_processing
}  // namespace mpcc

#endif  // PATH_PROCESSING_CONFIG_H
