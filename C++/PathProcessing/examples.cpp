// Example: Using PathProcessing Library Standalone
// This demonstrates how to use the library independently of the MPCC controller

#include "path_processing.h"
#include <iostream>
#include <vector>

using namespace mpcc::path_processing;

void example_cubic_spline() {
    std::cout << "=== Cubic Spline Example ===" << std::endl;
    
    // Create sample data points
    Eigen::VectorXd x(6), y(6);
    x << 0.0, 1.0, 2.0, 3.0, 4.0, 5.0;
    y << 0.0, 2.0, 1.5, 3.0, 2.5, 4.0;
    
    // Create and fit spline
    CubicSpline spline;
    spline.genSpline(x, y, true);  // true = regularly spaced
    
    // Evaluate spline at various points
    std::cout << "Interpolated values:" << std::endl;
    for (double t = 0.0; t <= 5.0; t += 0.5) {
        double value = spline.getPoint(t);
        double derivative = spline.getDerivative(t);
        std::cout << "  t=" << t << ": value=" << value 
                  << ", derivative=" << derivative << std::endl;
    }
}

void example_arc_length_spline() {
    std::cout << "\n=== Arc Length Spline Example ===" << std::endl;
    
    // Create a circular-ish path
    int n = 20;
    Eigen::VectorXd X(n), Y(n);
    for (int i = 0; i < n; i++) {
        double theta = 2.0 * M_PI * i / n;
        X(i) = std::cos(theta);
        Y(i) = std::sin(theta);
    }
    
    // Create arc-length parametrized spline
    SplineParams params(1.0);  // max projection distance = 1.0
    ArcLengthSpline spline(params);
    spline.gen2DSpline(X, Y);
    
    std::cout << "Path length: " << spline.getLength() << std::endl;
    std::cout << "Expected (2*pi): " << 2.0 * M_PI << std::endl;
    
    // Sample points along the path
    std::cout << "\nSampled points:" << std::endl;
    for (double s = 0.0; s < spline.getLength(); s += spline.getLength() / 8.0) {
        Eigen::Vector2d pos = spline.getPosition(s);
        Eigen::Vector2d vel = spline.getDerivative(s);
        std::cout << "  s=" << s << ": pos=[" << pos(0) << ", " << pos(1) 
                  << "], vel=[" << vel(0) << ", " << vel(1) << "]" << std::endl;
    }
    
    // Project a point onto the spline
    SimpleState state;
    state.X = 1.2;
    state.Y = 0.3;
    state.s = 0.0;
    double s_proj = spline.projectOnSpline(state);
    Eigen::Vector2d closest = spline.getPosition(s_proj);
    
    std::cout << "\nProjection:" << std::endl;
    std::cout << "  Point: [" << state.X << ", " << state.Y << "]" << std::endl;
    std::cout << "  Projected s: " << s_proj << std::endl;
    std::cout << "  Closest point: [" << closest(0) << ", " << closest(1) << "]" << std::endl;
}

void example_normalization() {
    std::cout << "\n=== Normalization Example ===" << std::endl;
    
    // Create normalization with identity matrices
    Normalization norm;
    int nx = 10, nu = 3, ns = 3;
    norm.loadFromFile("../Params/normalization.json", nx, nu, ns);
    
    std::cout << "State transformation matrix (diagonal):" << std::endl;
    for (int i = 0; i < std::min(5, nx); i++) {
        std::cout << "  T_x(" << i << "," << i << ") = " << norm.T_x(i, i) << std::endl;
    }
    
    // Example: normalize a state vector
    Eigen::VectorXd state(nx);
    state << 1.0, 2.0, 0.5, 5.0, 0.2, 0.1, 10.0, 0.3, 0.2, 3.0;
    
    Eigen::VectorXd normalized = norm.T_x_inv * state;
    std::cout << "\nOriginal state: " << state.transpose() << std::endl;
    std::cout << "Normalized state: " << normalized.transpose() << std::endl;
}

int main() {
    std::cout << "PathProcessing Library - Usage Examples\n" << std::endl;
    std::cout << "========================================\n" << std::endl;
    
    try {
        example_cubic_spline();
        example_arc_length_spline();
        // example_normalization();  // Requires normalization.json file
        
        std::cout << "\n========================================" << std::endl;
        std::cout << "All examples completed successfully!" << std::endl;
        
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}
