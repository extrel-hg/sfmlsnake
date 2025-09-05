cd build
cmake .. -DINCLUDEDLLS=true -G "MinGW Makefiles"
make
cmake --install .
cd finishedsnake
.\sfmlsnake.exe
