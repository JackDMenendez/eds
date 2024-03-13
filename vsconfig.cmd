cmake.exe  -G "Ninja"  ^
    -DCMAKE_BUILD_TYPE:STRING="Debug" ^
    -DCMAKE_INSTALL_PREFIX:PATH="out\install\win\x64-Debug" ^
    -DCMAKE_CXX_COMPILER:FILEPATH="C:/Program Files/Microsoft Visual Studio/2022/Community/VC/Tools/MSVC/14.39.33519/bin/Hostx64/x64/cl.exe" ^ 
    -DCMAKE_MAKE_PROGRAM=ninja.exe ^
    -B out/build/x64-Debug ^
    -S "."
::cmake --no-warn-unused-cli -DCMAKE_EXPORT_COMPILE_COMMANDS:BOOL=TRUE -S. -B./out/build/win-X64-debug-VS2020 -G "Visual Studio 17 2022" -T host=x64 -A x64
::cmake.exe  -G "Ninja" -B./build/win-X64-debug-VC -DCMAKE_BUILD_TYPE:STRING="Debug" -DCMAKE_INSTALL_PREFIX:PATH="build\install\win-x64-Debug-VC" -DCMAKE_CXX_COMPILER:FILEPATH="C:/Program Files/Microsoft Visual Studio/2022/Community/VC/Tools/MSVC/14.39.33519/bin/Hostx64/x64/cl.exe"   -DCMAKE_MAKE_PROGRAM=ninja -S .
::cmake -G "Unix Makefiles" -S . -B build/win-X64-debug-unix
::cmake -G "NMake Makefiles" -S . -B build/win-X64-debug-nmake
::cmake -G "MinGWW Makefiles" -S . -B build/win-X64-debug-sys2-mingw
::cmake -G "MSYS Makefiles" -S . -B build/win-X64-debug-msys
::cmake --build ./build/win-X64-debug-sys2-mingw/
::cmake --build ./build/win-X64-debug-msys/
::cmake --build ./build/win-X64-unix/
::cmake --build ./build/win-X64-nmake/
::cmake --build ./out/build/win-X64-debug-VS2020/
::cmake --build ./build/win-X64-debug-VC/
