# Codes and Datasets of $kPEX$ for Maximum  k-Plex Searching.

Quick start:
```shell
cd IterQC
make
./IterQC graph_path k
```


<hr>

## A. Input graph data format:

### Format : `*.bin`
binary graph:
- first $4$ Bytes: **sizeof(uint32_t)**, which should be $4$
- then $4$ Bytes: $n$
- then $4$ Bytes: $2\times m$
- then $4\times n$ Bytes: the degree $d_G(\cdot)$ of $n$ vertices
- then: $n$ parts ($2m\times 4$ Bytes in total), each part has $d_G(u)$ integers which are the neighbors of $u$ ***in ascending order***

We provide some examples of binary graph file  in [*data/bin/*](./data/bin/).

More details about reading graphs from files can be found in ***Graph::readFromFile*** in [**IterQC/Graph.h**](./IterQC/Graph.h).


### Transform other formats to `*.bin`
We provide [*trans.cpp*](./data/change_graph_format) to convert 4 kinds of formats to binary files.\
More details about it can be found in [**data/change_graph_format/readme.txt**](./data/change_graph_format/readme.txt)

<hr>

## B. Algorithm $IterQC$
The whole procedure for searching Maximum K-Plex is located at [*IterQC/*](./IterQC/). 

### 1. Compile
```shell
g++ -std=c++11 -O3 -w main.cpp -o IterQC -DNDEBUG -DNO_PROGRESS_BAR
```
or
```shell
make
```

Note that we add a macro definition in the compile command: 
- ***-DNO_PROGRESS_BAR*** will disable the progress bar; we recommend to add this definition when you use batch commands. 
- ***-DNDEBUG*** will disable  `assert`, which only works for debug.

### 2. Run
```shell
./IterQC graph_path gamma
```

### 3. An example
```shell
cd IterQC
make
./IterQC ../data/bin/brock200-2.bin 0.95
```

### 5. About major components in codes
- ***KPEX and Fake LB*** corresponds to (./IterQC/kplex.h);
- ***PreProccessing*** corresponds to (./IterQC/SuperUB.h)
