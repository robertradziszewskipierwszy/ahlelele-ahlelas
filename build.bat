@echo off
echo Building Ahlelele Ahlelas Compiler...

if not exist build mkdir build
cd build

cmake ..
cmake --build . --config Release

echo.
echo Build complete! Executable: build\Release\ahlelele.exe
echo.
echo Try it out:
echo   .\build\Release\ahlelele.exe --in examples\hello_world.ahl --out hello.ahlx
echo   .\build\Release\ahlelele.exe --exec hello.ahlx

