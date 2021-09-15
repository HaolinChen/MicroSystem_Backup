import numpy as np
import matplotlib.pyplot as plt
from sklearn import svm
from sklearn.datasets import make_blobs

n_samples = [10, 10, 10, 10]
centers = [[0.0, 0.0], [2.0, 2.0], [4.0, 4.0], [6.0, 6.0]]
cluster_std = [0.4, 0.4, 0.4, 0.4]

# x: dataset[sample_num][feature_num(default:2)]
# y: label of each sample
x, y = make_blobs(n_samples=n_samples, centers=centers, cluster_std=cluster_std, random_state=0, shuffle=False)

clf = svm.SVC(kernel='linear', C=10, gamma=0.5, decision_function_shape='ovo')  # Initialization
clf.fit(x, y)  # Training

xx = np.linspace(-1, 7, 400)  # Generate x coordinate, 400 samples
yy = np.linspace(-1, 7, 400)  # Generate y coordinate, 400 samples
XX, YY = np.meshgrid(xx, yy)  # Generate grid point coordinate matrix
XY = np.vstack([XX.ravel(), YY.ravel()]).T  # 400(x)*400(y) samples (Transposed). Now it's 160000*2
Z = clf.predict(XY).reshape(XX.shape)  # Converse the matrix from 160000*1 to 400*400
plt.pcolormesh(XX, YY, Z, cmap=plt.cm.rainbow)
# Find the color in rainbow according to the value of Z to color the coordinates
plt.scatter(x[:, 0], x[:, 1], c=y, cmap=plt.cm.rainbow, edgecolors='k')
plt.scatter(clf.support_vectors_[:, 0], clf.support_vectors_[:, 1], s=100, facecolors='none', edgecolors='k')
# Size = 100

print('clf.support_vectors_')
print(clf.support_vectors_)

print('clf.n_support_')
print(clf.n_support_)

print('clf.support_')
print(clf.support_)

print('clf.dual_coef_')
print(clf.dual_coef_)

print('clf.coef_')
print(clf.coef_)

print('clf.intercept_')
print(clf.intercept_)

print(clf.decision_function([[1, 1]]))
print(clf.predict([[1, 1]]))

plt.show()
