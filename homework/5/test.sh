g++ spt.cpp -o spt -std=c++11
g++ mst.cpp -o mst -std=c++11

time ./mst < input > output1
time ./spt < input > output2