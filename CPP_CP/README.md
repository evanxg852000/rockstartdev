g++ build:
```bash
cd project/
RUN g++ main.cpp -std=c++17 -o ./build/app
```

gcc build:
```bash
cd project/
RUN g++ main.cpp -std=c++17 -o ./build/app
```


CMake build:
```bash
 cd project/
 mkdir build && cd build/
 cmake ..
 make
```

Book:
http://www.fredosaurus.com/notes-cpp/index.html
