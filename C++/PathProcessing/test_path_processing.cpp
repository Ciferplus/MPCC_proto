// Simple test to verify PathProcessing library compiles correctly

#include "path_processing.h"
#include <iostream>

using namespace mpcc::path_processing;

int main() {
    std::cout << "PathProcessing Library Test" << std::endl;
    
    // Test 1: Create a simple cubic spline
    std::cout << "\n1. Testing CubicSpline..." << std::endl;
    Eigen::VectorXd x(5), y(5);
    x << 0.0, 1.0, 2.0, 3.0, 4.0;
    y << 0.0, 1.0, 0.5, 1.5, 1.0;
    
    CubicSpline spline;
    spline.genSpline(x, y, true);
    double val = spline.getPoint(2.5);
    std::cout << "   Spline value at 2.5: " << val << std::endl;
    
    // Test 2: Create an arc length spline
    std::cout << "\n2. Testing ArcLengthSpline..." << std::endl;
    SplineParams params(1.0);
    ArcLengthSpline arc_spline(params);
    
    Eigen::VectorXd X(5), Y(5);
    X << 0.0, 1.0, 2.0, 2.5, 3.0;
    Y << 0.0, 0.5, 1.0, 1.5, 2.0;
    
    arc_spline.gen2DSpline(X, Y);
    double length = arc_spline.getLength();
    std::cout << "   Arc length: " << length << std::endl;
    
    Eigen::Vector2d pos = arc_spline.getPosition(length / 2.0);
    std::cout << "   Position at mid-point: [" << pos(0) << ", " << pos(1) << "]" << std::endl;
    
    // Test 3: Test projection
    std::cout << "\n3. Testing projection..." << std::endl;
    SimpleState state;
    state.X = 1.5;
    state.Y = 0.8;
    state.s = 0.0;
    double s_proj = arc_spline.projectOnSpline(state);
    std::cout << "   Projected s: " << s_proj << std::endl;
    
    std::cout << "\nAll tests completed successfully!" << std::endl;
    
    return 0;
}
