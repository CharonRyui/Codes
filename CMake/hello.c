#include "hello.h"

static void inline hello();

static void hellon(int n){
    for(int i=0;i<n;i++){
        hello();
    }
}

static void inline hello(){
    printf("hello,world\n");
}