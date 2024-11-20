A://n rows
n m 
1 8 9 18 23 
...
n 34 44


B: //m rows
n m
1 8
1 9
1 18
...
n 44

C://m rows
p edge 453 2025
e 1 186
e 1 207
e 1 218
e 1 227
e 1 228
e 1 229
e 1 230
e 2 3
e 2 186

D://maybe you have multiple lines of '%..',then you may need to modify D2C.cpp by your self
%MatrixMarket matrix coordinate pattern symmetric 
%
6386 6386 217662 //n n m
195 1 //m rows
414 1
458 1
474 1
510 1
533 1



A->B: A2B.cpp
A->C: A2C.cpp
D->C: D2C.cpp
exmaple:  ./A2B file_path/graph new_floder (it will keep it original name)


C->bin:C2Bin.cpp
exmaple:   (The code is not written by me, so it is a little different.) ./C2Bin graph_path/graph new_floder/new_file_name