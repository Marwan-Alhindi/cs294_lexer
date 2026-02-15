# Deploy Skill

Build the shared library and run all tests (C++ and Python).

## Steps
1. Clean: `rm -rf build`
2. Configure: `cmake -B build -DCMAKE_BUILD_TYPE=Release`
3. Build: `cmake --build build`
4. Run C++ tests: `cd build && ctest --output-on-failure`
5. Run Python tests: `pytest tests/ -v`
6. Report results
