# DSML

[Visual Studio Code]: https://code.visualstudio.com/
[CMake]: https://cmake.org
[cmocka]: https://cmocka.org

Sample Cross-Platform C/C++ project. The project implements communication layer between real time distributed systems.
The library code provide funtionality for bidirectinal message transfer, commands + data, data blocks, etc.
Additionally POSIX-compatible file access is implemented, providig means for distributed file read, write, etc.
The low layer communication is implemented with dedicated protocol, capable of running with exchange of small, arbitrary size data packets.

## Requirements

TODO Description

### Make

You can install in your system the tools ```g++```, ```make```, ...

## Compilation

Once [CMake] and the building tools are installed in your system, then you can go to ```build``` directory and from the command prompt, run the command ```cmake```, with the corresponding argument depending on your system.

The project is using [cmocka] as unit testing framework, therefore references to the library and include files must be provided.

### Unix/Linux

        build/ $> cmake -G "Unix Makefiles" ..
        build/ $> make

To clean the compiled objects:

        build/ $> make clean

### Windows

        C:\build> cmake -G "Visual Studio 11 2012 Win64" -DCMOCKA_HOME=<cmocka installation directory> ..
        C:\build> msbuild dynamics.sln

**Note:** In the example the solution has been generated for _Visual Studio 2012_ and platform _64_ bits. However you can choose the combination you're interested in.

To clean the compiled objects:

        C:\build> msbuild dynamics.sln /t:clean

## Testing

Along with the code, testing code is delivered and compiled when compiling the code.
To run the tests, there are two options:

1. using ```ctest``` command, it runs all tests at once. This command belongs to the same toolset as ```cmake```.

        # Linux
        build/ $> ctest

        REM Windows
        C:\build> ctest

1. Running the tests individually. After the compilation, the tests are kept in ```build\test\Debug``` (Windows) or ```build/test``` (Linux)

### CMocka configuration

TODO Description

### Code Coverage

TODO Description

        build/ $> lcov -c -d <parent directory with the *.gcda> -o <PROJ_ROOT>/coverage.info

        To create a html report of the coverage, run the command:

        build/ $> genhtml <PROJ_ROOT>/coverage.info -o <PROJ_ROOT>/reports/coverage
