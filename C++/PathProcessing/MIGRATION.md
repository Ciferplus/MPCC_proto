# PathProcessing Library - Migration Notes

## Changes from Original MPCC Code

This library extracts and refactors path processing code from the main MPCC repository to create a standalone, reusable library.

### Key Differences

#### 1. Namespace
- **Original**: `namespace mpcc`
- **New**: `namespace mpcc::path_processing`

This allows the library to be used alongside the original MPCC code without conflicts.

#### 2. State Structure
- **Original**: Uses full `State` struct from `types.h` with 10 members
- **New**: Uses minimal `SimpleState` with only X, Y, s needed for spline operations

```cpp
// Old
State x;
x.X = 1.0;
x.Y = 2.0;
x.s = 0.0;

// New
SimpleState state;
state.X = 1.0;
state.Y = 2.0;
state.s = 0.0;
```

#### 3. Parameters
- **Original**: `ArcLengthSpline` depends on full `Param` class
- **New**: Uses lightweight `SplineParams` with only required parameters

```cpp
// Old
Param param(path.param_path);
ArcLengthSpline spline(path);

// New
SplineParams params(1.0);  // max_dist_proj
ArcLengthSpline spline(params);
```

#### 4. Method Names
- **Original**: `porjectOnSpline` (typo in original)
- **New**: `projectOnSpline` (fixed typo), `getPosition` (was `getPostion`)

#### 5. Normalization
- **Original**: `NormalizationParam` class in `Params/params.h`
- **New**: `Normalization` class with more flexible interface

```cpp
// Old
NormalizationParam norm(path.normalization_path);

// New
Normalization norm;
norm.loadFromFile("normalization.json", nx, nu, ns);
```

#### 6. Configuration
- **Original**: Depends on `config.h` with MPC-specific defines
- **New**: Minimal `path_processing_config.h` with only required constants

### Removed Dependencies

The library no longer depends on:
- Full `types.h` with State/Input/PathToJson structures
- `Params/params.h` with Param/CostParam/BoundsParam
- MPC-specific configuration (NX, NU, NPC, NS macros)
- Cost, Model, Constraints modules

### Preserved Functionality

All core algorithms remain unchanged:
- Cubic spline interpolation algorithm
- Arc-length spline fitting with iterative refinement
- Outlier removal
- Newton-method projection
- Track data loading
- Normalization matrix operations

### Integration with Original MPCC Code

The original MPCC code can be updated to use this library with adapter wrappers:

```cpp
// Adapter example
namespace mpcc {
    
State adaptState(const path_processing::SimpleState& simple) {
    State full;
    full.X = simple.X;
    full.Y = simple.Y;
    full.s = simple.s;
    // ... set other fields as needed
    return full;
}

path_processing::SimpleState adaptState(const State& full) {
    path_processing::SimpleState simple;
    simple.X = full.X;
    simple.Y = full.Y;
    simple.s = full.s;
    return simple;
}

}
```

### Benefits

1. **Reusability**: Can be used in other projects without MPCC
2. **Minimal dependencies**: Only Eigen and nlohmann/json
3. **Clear API**: Simpler interfaces for common operations
4. **Maintainability**: Easier to test and modify independently
5. **Flexibility**: Can be built as a standalone library

### Future Enhancements

Potential improvements that could be made:
- Template-based spline for different numeric types
- Python bindings for easier scripting
- Additional spline types (B-spline, Bezier)
- Thread-safe caching for performance
- More robust error handling
