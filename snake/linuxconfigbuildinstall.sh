mkdir build
cd build
cmake .. -DINCLUDEDLLS=false
make
cmake --install .
$SHELL
