mkdir build
cd build
cmake .. -DINCLUDEDLLS=true -G "MinGW Makefiles"
make
cmake --install .
