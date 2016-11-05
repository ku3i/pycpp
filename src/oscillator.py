
from numpy import tanh

class SO2(object):
    def __init__(self, s, r, x = [0.0, 0.01]):
        self.w = [[float(s), float(r)], [-float(r), float(s)]]
        self.x = x
        self.y = [0.0, 0.0]

    def net_update(self):
        self.y[0] = tanh(self.w[0][0] * self.x[0] + self.w[0][1]*self.x[1])
        self.y[1] = tanh(self.w[1][0] * self.x[0] + self.w[1][1]*self.x[1])
        self.x = self.y
        return self.y
