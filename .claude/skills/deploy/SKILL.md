# Deploy Skill

Build release binary and run the full test suite.

## Steps
1. Clean the build directory: `rm -rf build`
2. Configure with release flags: `cmake -B build -DCMAKE_BUILD_TYPE=Release`
3. Build: `cmake --build build`
4. Run full test suite: `cd build && ctest --output-on-failure`
5. Report results
