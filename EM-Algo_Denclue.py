import numpy as np
from mpl_toolkits import mplot3d
import matplotlib.pyplot as plt
from sklearn.decomposition import PCA
from scipy.stats import multivariate_normal
clusters = 2
dim = 2
maxim = 100000
minesp = 0.001
denclueh=3
file1 = open("irisdataset.txt")
file1 = (file1.read()).split()
mydataset = []
for i in file1:
    temp = []
    temp = i.split(',')
    temp = temp[:-1]
    for j in range(len(temp)):
        temp[j] = float(temp[j])
    mydataset.append(temp)
pca = PCA(n_components=dim)
pca.fit(mydataset)
mydataset = pca.transform(mydataset)


def diff(mean, premean):
    sum = 0
    for i in range(len(mean)):
        for j in range(len(mean[i])):
            curr = mean[i][j]-premean[i][j]
            curr **= 2
            sum += curr
    return sum


premean = []
cov = []
mean = []
clusterprob = []
for i in range(clusters):
    currcov = []
    for j in range(dim):
        y = []
        for k in range(dim):
            y.append(0)
        y[j] = 1
        currcov.append(y)
    cov.append(currcov)
for i in range(clusters):
    mean.append(mydataset[i])
    clusterprob.append(1/clusters)
for i in range(clusters):
    ya = []
    for i in range(dim):
        ya.append(maxim)
    premean.append(ya)


s = 0
# m=[[-3.59,0.25],[-1.09,-0.46],[0.75,1.07]]
# mean=m.copy()
while(diff(mean, premean) > minesp):
#     print(diff(mean,premean))
    s += 1
    posteprob = []
#     Expection Step...................................
    for i in range(clusters):
        temp = []
        for j in mydataset:
            cc = multivariate_normal(mean=mean[i], cov=cov[i])
            cc = cc.pdf(j)
            cc *= clusterprob[i]
            upon = 0
            for k in range(clusters):
                ccc = multivariate_normal(mean=mean[k], cov=cov[k])
                ccc = ccc.pdf(j)
                ccc *= clusterprob[k]
                upon += ccc
            cc = cc/upon
            temp.append(cc)
        posteprob.append(temp)

#     Maximization step...................................
    premean = mean.copy()
    for i in range(clusters):
        sum = 0
        cc = []

#     ..........................................
        totalupon = 0
        for j in range(dim):
            cc.append(0)
        for j in range(len(mydataset)):
            curr = mydataset[j].copy()
            totalupon += posteprob[i][j]
            for k in range(len(curr)):
                curr[k] *= posteprob[i][j]
                cc[k] += curr[k]
        for k in range(dim):
            cc[k] = cc[k]/totalupon
        mean[i] = cc.copy()
#         ......................................
        covv = []
        for j in range(dim):
            temp = []
            for k in range(dim):
                temp.append(0)
            covv.append(temp)
        tempp = []
        for j in range(len(mydataset)):
            tempp = mydataset[j].copy()
            for k in range(len(tempp)):
                tempp[k] -= mean[i][k]
            for k in range(len(tempp)):
                for p in range(len(tempp)):
                    covv[k][p] += ((tempp[p]*tempp[k] *
                                    posteprob[i][j])/totalupon)
        cov[i] = covv.copy()
        clusterprob[i] = totalupon/len(mydataset)

print("Expectation Maximization final parameters:.....................................\n")
print("Total number of itearations to converge: ", end="")
print(s)
print("Final parameters for the each-", end="")
print(clusters, end=" ")
print("Clusters")
for i in range(clusters):
    print("*****************************")
    print("Cluster-", end="")
    print(i+1)
    print("Mean.......")
    print(mean[i])
    print("Covariance Matrics.........")
    for j in cov[i]:
        print(j)
    print("Probability......")
    print(clusterprob[i])

%matplotlib notebook
fig = plt.figure()
ax = fig.gca(projection='3d')


def computepdf(mean, cov, data):
    ccc = multivariate_normal(mean=mean, cov=cov)
    ccc = ccc.pdf(data)
    return ccc
def computeDenclueWeight(point1,point2):
    sum=0
    for i in range(dim):
        sum+=(point1[i]-point2[i])*(point1[i]*point2[i])
    sum*=-1
    sum=sum/(2*denclueh*denclueh)
    sum=2.71**sum
    cc=dim/2
    cc=6.28**cc
    sum=sum/cc
    return sum
    
def ComputeDenclue_pdf(mydataset, point):
    sum=0
    for i in mydataset:
        sum+= computeDenclueWeight(point,i)
    sum=sum/(len(mydataset))
    cc=denclueh**dim
    sum=sum/cc
    return sum
print("To see the EM-Algo analysis PDF Graph press-1")
print("To see the Denclue analysis PDF Graph press-2")
op=int(input())
if(op==1):
    for k in range(clusters):
        X = []
        Y = []
        Z = []
        for i in mydataset:
            X.append(i[0])
            Y.append(i[1])
            Z.append(computepdf(mean[k], cov[k], i))
        ax.plot_trisurf(X, Y, Z, linewidth=0.1, antialiased=True)
        plt.legend()
    for angle in range(0, 360):
        ax.view_init(15, angle)
        plt.draw()
        plt.pause(.0001)
    
# *************************************************************END-EM-Algorithm***************************
# >>>>>>>>>>Start/Denclue-Pdf-Estimation>>>>>>>>>>>>>>>>
else:
    X=[]
    Y=[]
    Z=[]
    for i in mydataset:
        X.append(i[0])
        Y.append(i[1])
        Z.append(ComputeDenclue_pdf(mydataset,i))
    ax.plot_trisurf(X, Y, Z, linewidth=0.1, antialiased=True)
    plt.show()
