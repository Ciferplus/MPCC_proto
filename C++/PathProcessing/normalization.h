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

#ifndef PATH_PROCESSING_NORMALIZATION_H
#define PATH_PROCESSING_NORMALIZATION_H

#include "path_processing_config.h"
#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>

namespace mpcc {
namespace path_processing {

using json = nlohmann::json;

// Normalization matrices for state, input, and slack variables
// These are used to scale optimization variables for better numerical conditioning
class Normalization {
public:
    // Transformation matrices (diagonal scaling matrices)
    Eigen::MatrixXd T_x;       // State transformation
    Eigen::MatrixXd T_x_inv;   // Inverse state transformation
    
    Eigen::MatrixXd T_u;       // Input transformation
    Eigen::MatrixXd T_u_inv;   // Inverse input transformation
    
    Eigen::MatrixXd T_s;       // Slack transformation
    Eigen::MatrixXd T_s_inv;   // Inverse slack transformation

    // Constructors
    Normalization();
    Normalization(std::string file, int nx, int nu, int ns);

    // Load normalization parameters from JSON file
    void loadFromFile(std::string file, int nx, int nu, int ns);

private:
    void setIdentity(int nx, int nu, int ns);
};

}  // namespace path_processing
}  // namespace mpcc

#endif  // PATH_PROCESSING_NORMALIZATION_H
