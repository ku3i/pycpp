#!/usr/bin/python


# g++ -c -fPIC hellow.cpp -o hellow.o
# g++ -shared -Wl,-soname,libhellow.so -o libhellow.so  hellow.o



from ctypes import cdll
from ctypes import c_int, c_double, c_char_p

#TODO check and compile lib before loading

lib = cdll.LoadLibrary('./libhellow.so')

class Foo(object):
    def __init__(self):
        self.obj = lib.Foo_new()

    def bar(self, msg, mylist):
        arr = (c_double * len(mylist))(*mylist)
        ret = lib.Foo_bar(self.obj, c_char_p(msg), arr, c_int(len(arr)))
        print("Answer: {}".format(ret))
        return list(arr)


li = [0.0,1.1,2.2,3.3,4.4,5.5,6.6,7.7,8.8,9.9]
print(li)

print("_____")
f = Foo()
lo = f.bar("hello my name is", li)

print(lo)


