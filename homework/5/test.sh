g++ spt.cpp -o spt -std=c++11
./spt < input > output1
./clustering < input > output2
diff output1 output2