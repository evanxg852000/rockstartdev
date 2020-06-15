## CHIP-8 SFML (with conan)

# Add bincrafter repository
```bash
conan remote add bincrafters https://api.bintray.com/conan/bincrafters/public-conan
```

# How to build
```bash
mkdir build && cd build
conan install ..  -s build_type=Release --build
cmake .. -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release
cmake --build .
./bin/app
```
