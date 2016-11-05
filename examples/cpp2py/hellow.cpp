
#include "./foo.hpp"

extern "C" {
    Foo* Foo_new(){ return new Foo(); }
    int Foo_bar(Foo* foo, char* msg, double *arr, int i){ return foo->bar(msg, arr, i); }
}


