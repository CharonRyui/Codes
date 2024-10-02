#include <iostream>
#include <mpi.h>
#include <cstddef>

struct MyStruct {
    int a;
    double b;
    int arr[3];
    char c;
    float d;
};

int main(int argc, char **argv) {
    MPI_Init(&argc, &argv);

    MPI_Datatype CustomType;
    MPI_Aint displacement[5] = {offsetof(MyStruct, a), offsetof(MyStruct, b), offsetof(MyStruct, arr), offsetof(MyStruct, c), offsetof(MyStruct, d)};
    int block_length[5] = {1, 1, 3, 1, 1};
    MPI_Datatype types[5] = {MPI_INT, MPI_DOUBLE, MPI_INT, MPI_CHAR, MPI_FLOAT};
    MPI_Type_create_struct(5, block_length, displacement, types, &CustomType);
    MPI_Type_commit(&CustomType);

    int rank;
    int size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MyStruct myStruct1{rank, rank * 3.14, {rank + 3, rank + 2, rank + 1}, rank + 65, rank * 1.41};
    MyStruct myStruct2{rank, rank * 3.14, {rank + 3, rank + 2, rank + 1}, rank + 65, rank * 1.41};
    MyStruct myList[2] = {myStruct1, myStruct2};

    MyStruct result[100];
    MPI_Gather(myList, 2, CustomType, result, 2, CustomType, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        for (int i = 0; i < size * 2; i++) {
            std::cout << result[i].a << " " << result[i].b << " " << result[i].arr[1] << " " << result[i].c << std::endl;
        }
    }

    MPI_Finalize();
    return 0;
}