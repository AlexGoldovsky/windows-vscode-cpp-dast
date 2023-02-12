# Awesome!
From now on, I merely need to write code since the environment is ready!

I have a setup here to work with cpp which includes:
- Tests
- Debugging
- Memory leak detection


## Tests
#### *Setup tests*
gtest setup script
```Powershell
git clone https://github.com/google/googletest.git
cd .\googletest # root repo not the sub directory!
mkdir build
cd build
. "C:\Program Files\CMake\bin\cmake.exe" .. -G "MinGW Makefiles"
cp lib/* C:\msys64\mingw64\lib
cp -Recurse ..\googletest\include\* C:\msys64\mingw64\include
cp -Recurse ..\googlemock\include\* C:\msys64\mingw64\include
```

what it does:
1. clone *[gtest](https://github.com/google/googletest)*
2. build using cmake 
3. copy relevant lib(.a archive files) and include(.h header files) files to mingw64 directories

#### *Write tests*
- see *[test example](Tests/Array/test_sort.cpp)*
- see *[documentation](https://google.github.io/googletest/)*

#### *Run tests*
1. configure test directives [makefile](.\Makefile)
2. run `make tests` or `make test_{name}`
3. execute `.\test_{name}.exe`

## Debugging
1. configure a proper task in [tasks.json](.vscode\tasks.json) file.
Specifically note the `"type": "cppbuild"` parameter
2. add launch configuration in [launch.json](.\vscode\launch.json) file.
note the `"request": "launch"`, `"preLaunchTask": "test"`, `"cwd": "${workspaceFolder}"` parameters
3. now you should be able to start the debugging by pressing `f5`, but might need to add a debug configuration


## Memory leaks detection
#### *Prepare for running leak test*
1. using [drmemory](https://drmemory.org/)
2. to get line numbers for the leaks found we need to compile with  `-gdwarf-2` flag
3. to surpress annoying false positives or whatever it is add to relevant [supresssions](.\drmemory_supresssions.txt)

#### *Run leak test*
use the command `drmemory.exe -suppress .\drmemory_supresssions.txt -- .\test_sort.exe`

# Notes
- in order to use g++ I had to install `msys64\mingw64`, don't remember how exactly
- had to install *`cmake`* as well (for gtest)
- somehow installed *`make`*
- **!important** add everything relevant to the path
- *`Task Runner`* for vscode is nice to run task defined in [tasks.json](.\vscode\tasks.json) file