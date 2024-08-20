export PATH=/home/andtokm/DiskS/Utils/cmake/cmake-3.30/bin/:${PATH}
export GCC_13_PATH=/home/andtokm/DiskS/Utils/bin/gcc-14.2

export PATH=${GCC_13_PATH}/bin:${PATH}


cmake  -DCMAKE_C_COMPILER=/usr/bin/clang-17 -DCMAKE_CXX_COMPILER=/usr/bin/clang++-17 -DCMAKE_CXX_STANDARD=23 -B./build
cmake  -DCMAKE_C_COMPILER=/usr/bin/clang-19 -DCMAKE_CXX_COMPILER=/usr/bin/clang++-19 -DCMAKE_CXX_STANDARD=23 -B./build
cmake  -DCMAKE_C_COMPILER=gcc-14.2 -DCMAKE_CXX_COMPILER=g++-14.2 -DCMAKE_CXX_STANDARD=23 -B./build