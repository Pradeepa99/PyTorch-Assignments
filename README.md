# PyTorch-Assignments

## Setup Instructions
#### 1. Extract the folder linspace-app and fmod-app from the repository
Let us assume our directory is in the following structure
 ```
 linspace-app/
   CMakeLists.txt
   linspace-app.cpp
 ```
#### 2. To build the Cmake
``` 
mkdir build
cd build
```
```
cmake -DCMAKE_PREFIX_PATH= /absolute/path/to/libtorch ..
/absolute/path/to - This is the path where libtorch is present(For example, /home/user/Downloads/libtorch-cxx11-abi-shared-with-deps-1.8.1+cpu/libtorch)
```


```
cmake --build . --config Release
```
#### 3.Type the following command
```
./filename.app (e.g: ./linspace-app or ./fmod-app)

```
