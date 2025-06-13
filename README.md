# N-Dimensional Ray Tracer (C++ Version)

This project is a C++ implementation of an N-dimensional ray tracer.

## Prerequisites

- C++17 compatible compiler (e.g., g++, clang++)
- CMake (version 3.10 or later)
- Eigen library (version 3.3 or later)

### Installation of Prerequisites

#### macOS (using Homebrew)
```bash
brew install cmake eigen
pip3 install matplotlib
```

#### Debian/Ubuntu (using apt)
```bash
sudo apt-get update
sudo apt-get install cmake libeigen3-dev python3-matplotlib
```

## Building the Project

1.  **Create a build directory:**
    ```bash
    mkdir build
    cd build
    ```

2.  **Run CMake to configure the project:**
    ```bash
    cmake ..
    ```

3.  **Compile the project:**
    ```bash
    make
    ```

## Running the Executable

After a successful build, you can run the test suite:
```bash
./nd_ray_tracer