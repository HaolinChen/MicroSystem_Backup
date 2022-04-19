import numpy as np

np.set_printoptions(threshold=1e6)
test=np.load('./demo_16q.npy',allow_pickle=True)
with open("./demo_16q.txt", "w") as f:
    print(test, file=f)

