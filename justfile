dev:
    cmake -S . -B build -G Ninja -DCMAKE_BUILD_TYPE=Debug
    cmake --build build
    ./build/bin/wisp_dev

release:
    cmake -S . -B build -G Ninja -DCMAKE_BUILD_TYPE=Release
    cmake --build build
