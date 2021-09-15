import numpy as np

sv = [[0.39149519, 0.89635728],
      [0.97880407, 2.26144744],
      [2.61311169, 2.58774351],
      [1.6448857, 1.20768141],
      [3.58057881, 3.43199283],
      [4.02660689, 4.12098876],
      [5.67474149, 5.30948696]]
nv = [1, 3, 2, 1]
a = [[1.33143525,     -0.43355065, -0., -0.89788459,       -0.12048409, -0.,   -0.04220442],
     [0.12048409,     0., 1.21304109, 0.,                  -1.21304109, -0.,   -0.11917911],
     [0.04220442,     0., 0.11917911, 0.,                  0., 0.48417772,     -0.48417772]]
b = [2.32166302, 1.42426621, 1.25424389, 6.71682103, 2.79287738, 6.58414668]
cs = [0, 1, 2, 3]

X = [5, 6]  # The test sample

k = [np.dot(vi, X) for vi in sv]  # Vector inner product

print('k')
print(k)

start = [sum(nv[:i]) for i in range(len(nv))]  # nv=[1,3,2,1] start=[0,1,4,6]
end = [start[i] + nv[i] for i in range(len(nv))]  # end = [1,4,6,7]
'''
c = [sum(a[i][q] * k[q] for q in range(start[j], end[j])) +
     sum(a[j - 1][p] * k[p] for p in range(start[i], end[i]))
     for i in range(len(nv)) for j in range(i + 1, len(nv))]
print('c')
print(c)
'''

c = np.zeros(int(4*(4-1)/2))
ci = 0
for i in range(len(nv)):
    for j in range(i + 1, len(nv)):
        sum1 = 0
        sum2 = 0
        for q in range(start[j], end[j]):
            sum1 = sum1 + a[i][q] * k[q]
        for p in range(start[i], end[i]):
            sum2 = sum2 + a[j - 1][p] * k[p]
        print('i:' + str(i) + ';j:' + str(j))
        print(sum1 + sum2)
        c[ci] = sum1+sum2
        ci = ci+1


decision = [sum(x) for x in zip(c, b)]
print('decision')
print(decision)


votes = [(i if decision[p] > 0 else j) for p, (i, j) in enumerate((i, j)
                                                                  for i in range(4)
                                                                  for j in range(i + 1, 4))]

print('votes')
print(votes)

print(cs[max(set(votes), key=votes.count)])
