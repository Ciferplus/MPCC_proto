# PathProcessing Library

A standalone C++ library for path processing operations including spline interpolation, path parameterization, and normalization.

## Components

### 1. Cubic Spline (`cubic_spline.h/cpp`)
- Natural cubic spline interpolation
- Supports both regular and irregular spaced data points
- First and second derivative computation
- Periodic spline wrapping

### 2. Arc Length Spline (`arc_length_spline.h/cpp`)
- Arc-length parametrized 2D spline generation
- Iterative refinement for accurate arc-length representation
- Outlier removal for robust fitting
- Point projection onto spline using Newton's method

### 3. Track (`track.h/cpp`)
- Track data loading from JSON files
- Stores center line, inner boundary, and outer boundary
- Eigen::VectorXd representation for efficient computation

### 4. Normalization (`normalization.h/cpp`)
- Variable scaling for numerical conditioning in optimization
- Diagonal transformation matrices for states, inputs, and slack variables
- JSON-based configuration

## Dependencies

- **Eigen3**: Linear algebra library
- **nlohmann/json**: JSON parsing (only for Track and Normalization)

## Usage Example

```cpp
#include "PathProcessing/arc_length_spline.h"
#include "PathProcessing/track.h"

using namespace mpcc::path_processing;

// Load track from file
Track track("path/to/track.json");
TrackPos track_data = track.getTrack();

// Create arc-length spline
SplineParams params(1.0);  // max_dist_proj = 1.0
ArcLengthSpline spline(params);
spline.gen2DSpline(track_data.X, track_data.Y);

// Query spline
Eigen::Vector2d pos = spline.getPosition(5.0);
Eigen::Vector2d vel = spline.getDerivative(5.0);
double length = spline.getLength();

// Project point onto spline
SimpleState state;
state.X = 1.0;
state.Y = 2.0;
state.s = 0.0;
double s_projected = spline.projectOnSpline(state);
```

## Key Features

- **Self-contained**: Minimal dependencies on external code
- **Namespace isolation**: All code in `mpcc::path_processing` namespace
- **Clean API**: Simple interfaces for common operations
- **No MPC dependencies**: Can be used independently of the main MPCC controller

## Integration

To use this library in your project:

1. Include the `PathProcessing` directory in your include path
2. Link the compiled `.cpp` files or create a static/shared library
3. Include only the headers you need

## License

Apache License 2.0 - See individual files for full license text.
