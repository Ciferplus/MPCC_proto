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

#include "normalization.h"

namespace mpcc {
namespace path_processing {

Normalization::Normalization()
{
    std::cout << "Default initialization of normalization" << std::endl;
}

void Normalization::setIdentity(int nx, int nu, int ns)
{
    T_x = Eigen::MatrixXd::Identity(nx, nx);
    T_x_inv = Eigen::MatrixXd::Identity(nx, nx);
    
    T_u = Eigen::MatrixXd::Identity(nu, nu);
    T_u_inv = Eigen::MatrixXd::Identity(nu, nu);
    
    T_s = Eigen::MatrixXd::Identity(ns, ns);
    T_s_inv = Eigen::MatrixXd::Identity(ns, ns);
}

Normalization::Normalization(std::string file, int nx, int nu, int ns)
{
    loadFromFile(file, nx, nu, ns);
}

void Normalization::loadFromFile(std::string file, int nx, int nu, int ns)
{
    // Initialize identity matrices
    setIdentity(nx, nu, ns);
    
    // Load normalization parameters from JSON file
    std::ifstream iNorm(file);
    json jsonNorm;
    iNorm >> jsonNorm;

    // Set state transformation matrix (diagonal)
    // The JSON file should contain scaling factors for each state variable
    if (jsonNorm.contains("X")) T_x(0, 0) = jsonNorm["X"];
    if (jsonNorm.contains("Y")) T_x(1, 1) = jsonNorm["Y"];
    if (jsonNorm.contains("phi")) T_x(2, 2) = jsonNorm["phi"];
    if (jsonNorm.contains("vx")) T_x(3, 3) = jsonNorm["vx"];
    if (jsonNorm.contains("vy")) T_x(4, 4) = jsonNorm["vy"];
    if (jsonNorm.contains("r")) T_x(5, 5) = jsonNorm["r"];
    if (jsonNorm.contains("s")) T_x(6, 6) = jsonNorm["s"];
    if (jsonNorm.contains("D")) T_x(7, 7) = jsonNorm["D"];
    if (jsonNorm.contains("delta")) T_x(8, 8) = jsonNorm["delta"];
    if (jsonNorm.contains("vs")) T_x(9, 9) = jsonNorm["vs"];

    // Compute inverse by inverting diagonal elements
    for(int i = 0; i < nx; i++)
    {
        T_x_inv(i, i) = 1.0/T_x(i, i);
    }

    // Set input transformation matrix (diagonal)
    if (jsonNorm.contains("dD")) T_u(0, 0) = jsonNorm["dD"];
    if (jsonNorm.contains("dDelta")) T_u(1, 1) = jsonNorm["dDelta"];
    if (jsonNorm.contains("dVs")) T_u(2, 2) = jsonNorm["dVs"];

    // Compute inverse by inverting diagonal elements
    for(int i = 0; i < nu; i++)
    {
        T_u_inv(i, i) = 1.0/T_u(i, i);
    }

    // Slack transformation is identity by default
    // Can be extended if needed
}

}  // namespace path_processing
}  // namespace mpcc
