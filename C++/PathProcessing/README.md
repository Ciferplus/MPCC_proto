# PathProcessing Library / 路径处理库

[English](#english) | [中文](#chinese)

---

<a name="english"></a>
## English

A standalone C++ library for path processing operations including spline interpolation, path parameterization, and normalization.

### Components

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

### License

Apache License 2.0 - See individual files for full license text.

---

<a name="chinese"></a>
## 中文

一个独立的C++库，用于路径处理操作，包括样条插值、路径参数化和标准化。

### 组件

#### 1. 三次样条 (`cubic_spline.h/cpp`)
- 自然三次样条插值
- 支持规则和不规则间隔的数据点
- 计算一阶和二阶导数
- 周期性样条包装

#### 2. 弧长样条 (`arc_length_spline.h/cpp`)
- 弧长参数化的2D样条生成
- 迭代细化以获得精确的弧长表示
- 异常值移除以实现稳健拟合
- 使用牛顿法将点投影到样条上

#### 3. 轨迹 (`track.h/cpp`)
- 从JSON文件加载轨迹数据
- 存储中心线、内边界和外边界
- 使用Eigen::VectorXd表示以实现高效计算

#### 4. 标准化 (`normalization.h/cpp`)
- 用于优化中数值调节的变量缩放
- 状态、输入和松弛变量的对角变换矩阵
- 基于JSON的配置

### 依赖项

- **Eigen3**: 线性代数库
- **nlohmann/json**: JSON解析（仅用于Track和Normalization）

### 使用示例

```cpp
#include "PathProcessing/arc_length_spline.h"
#include "PathProcessing/track.h"

using namespace mpcc::path_processing;

// 从文件加载轨迹
Track track("path/to/track.json");
TrackPos track_data = track.getTrack();

// 创建弧长样条
SplineParams params(1.0);  // max_dist_proj = 1.0
ArcLengthSpline spline(params);
spline.gen2DSpline(track_data.X, track_data.Y);

// 查询样条
Eigen::Vector2d pos = spline.getPosition(5.0);
Eigen::Vector2d vel = spline.getDerivative(5.0);
double length = spline.getLength();

// 将点投影到样条上
SimpleState state;
state.X = 1.0;
state.Y = 2.0;
state.s = 0.0;
double s_projected = spline.projectOnSpline(state);
```

### 主要特性

- **自包含**: 对外部代码的依赖最少
- **命名空间隔离**: 所有代码都在 `mpcc::path_processing` 命名空间中
- **清晰的API**: 常见操作的简单接口
- **无MPC依赖**: 可以独立于主MPCC控制器使用

### 集成方法

要在您的项目中使用此库：

1. 将 `PathProcessing` 目录包含在您的包含路径中
2. 链接编译的 `.cpp` 文件或创建静态/共享库
3. 只包含您需要的头文件

### 文件清单

```
PathProcessing/
├── path_processing.h          # 主头文件
├── path_processing_config.h   # 配置和类型定义
├── cubic_spline.h/cpp          # 三次样条实现
├── arc_length_spline.h/cpp     # 弧长样条实现
├── track.h/cpp                 # 轨迹数据管理
├── normalization.h/cpp         # 变量标准化
├── CMakeLists.txt              # 构建配置
├── examples.cpp                # 使用示例
├── test_path_processing.cpp    # 测试程序
└── README.md                   # 本文档
```

### 许可证

Apache License 2.0 - 完整许可文本请参见各个文件。
