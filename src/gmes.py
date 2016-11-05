# g++ -c -fPIC hellow.cpp -o hellow.o
# g++ -shared -Wl,-soname,libhellow.so -o libhellow.so  hellow.o

from ctypes import cdll
from ctypes import c_int, c_uint, c_double, c_char_p

lib = cdll.LoadLibrary('./bin/libgmesmodule.so')

class GMES(object):
    def __init__(self, num_experts, local_rate, global_rate, num_samples):
        self.obj = lib.gmes_new(c_uint(num_experts), c_double(local_rate), c_double(global_rate), c_uint(num_samples))

    def __del__(self):
         lib.gmes_del(self.obj)

    def execute_cycle(self, data):
        carray = (c_double * len(data))(*data)
        lib.gmes_execute_cycle(self.obj, carray, c_uint(len(carray)))
