[![Actions Status](https://github.com/filipdutescu/modern-cpp-template/workflows/MacOS/badge.svg)](https://github.com/filipdutescu/modern-cpp-template/actions)
[![Actions Status](https://github.com/filipdutescu/modern-cpp-template/workflows/Windows/badge.svg)](https://github.com/filipdutescu/modern-cpp-template/actions)
[![Actions Status](https://github.com/filipdutescu/modern-cpp-template/workflows/Ubuntu/badge.svg)](https://github.com/filipdutescu/modern-cpp-template/actions)
[![codecov](https://codecov.io/gh/filipdutescu/modern-cpp-template/branch/master/graph/badge.svg)](https://codecov.io/gh/filipdutescu/modern-cpp-template)
[![GitHub release (latest by date)](https://img.shields.io/github/v/release/filipdutescu/modern-cpp-template)](https://github.com/filipdutescu/modern-cpp-template/releases)

# Simulation for Shape-Changeble Computer

## Features

## Getting Started

These instructions will get you a copy of the project up and running on your local
machine for development and testing purposes.

### Prerequisites

This project is meant to be only a template, thus versions of the software used
can be change to better suit the needs of the developer(s). If you wish to use the
template *as-is*, meaning using the versions recommended here, then you will need:

* **CMake v3.15+** - found at [https://cmake.org/](https://cmake.org/)

* **C++ Compiler** - needs to support at least the **C++17** standard, i.e. *MSVC*,
*GCC*, *Clang*

> ***Note:*** *You also need to be able to provide ***CMake*** a supported
[generator](https://cmake.org/cmake/help/latest/manual/cmake-generators.7.html).*

### Installing

It is fairly easy to install the project, all you need to do is clone if from
[GitLab](git@geopelia.mtl.t.u-tokyo.ac.jp:naga/ShapeChangeable-Simulation.git)

If you wish to clone the repository, rather than generate from it, you simply need
to run:

```bash
git clone git@geopelia.mtl.t.u-tokyo.ac.jp:naga/ShapeChangeable-Simulation.git
```

After finishing getting a copy of the project, with any of the methods above, create
a new folder in the `include/` folder, with the name of your project.  Edit
`cmake/SourcesAndHeaders.cmake` to add your files.

You will also need to rename the `cmake/ProjectConfig.cmake.in` file to start with
the ***exact name of your project***. Such as `cmake/MyNewProjectConfig.cmake.in`.
You should also make the same changes in the GitHub workflows provided, notably
[`.github/workflows/ubuntu.yml`](.github/workflows/ubuntu.yml), in which you should
replace the CMake option `-DProject_ENABLE_CODE_COVERAGE=1` to
`-DMyNewProject_ENABLE_CODE_COVERAGE=1`.

## Building the project

```bash
mkdir build && cd build
sudo apt-get update
sudo apt-get install cmake libgtest-dev
pushd /usr/src/gtest
sudo cmake CMakeLists.txt
sudo make
sudo cp lib *.a /usr/lib/
popd
sudo cmake ..
```

```bash
python build.py -c ino/cordinator.ino -r ino/router.ino
```

running 
```bash
build/bin/Debug/ShapeChangeable-Simulation <simulation source file path>
```

## Contributing

Please read [CONTRIBUTING.md](CONTRIBUTING.md) for details on our how you can
become a contributor and the process for submitting pull requests to us.

## Versioning

This project makes use of [SemVer](http://semver.org/) for versioning. A list of
existing versions can be found in the
[project's releases](https://github.com/filipdutescu/modern-cpp-template/releases).

## Authors

## License
