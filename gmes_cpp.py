#!/usr/bin/python

from src.oscillator import SO2
from src.gmes import GMES

import collections

gmes = GMES(50, 0.1, 0.01, 1)
osci = SO2(1.1, 0.4)
data = collections.deque(maxlen=10)

for i in range(1000):
    y = osci.net_update()
    gmes.execute_cycle(y)
    data.append(y[0])

print("____\nDONE.")
