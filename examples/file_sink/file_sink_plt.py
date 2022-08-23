#!/usr/bin/env python
import matplotlib.pyplot as plt
import numpy as np

vals = np.fromfile('testfile',dtype=np.complex64)

plt.plot(np.real(vals))
plt.plot(np.imag(vals))
plt.show()



