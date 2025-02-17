mkdir build
cd build
cmake .. -DINCLUDEDLLS=true
make
cmake --install .
$SHELL
