
#include <iostream>
#include <string>
class Foo{
    public:
        int bar(std::string msg, double* arr, int i){
            std::cout << msg << ": " << i << std::endl;
            std::cout << "( ";            
            for (unsigned c = 0; c < i; ++c) {
                arr[c] = 2.0*arr[c];
                std::cout << arr[c] << " ";
            }
            std::cout << ")" << std::endl;
            return i*2;
        }
};

