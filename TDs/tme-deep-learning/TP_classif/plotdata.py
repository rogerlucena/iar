import numpy as np
import matplotlib.pyplot as plt
import torch
import torch.nn as nn
import torch.nn.functional as F


def plotdata(data, indexes, model=None, original=True):
    l = []
    l_original = []
    for elt in indexes:
        t, _ = data.test[elt]
        l.append(t)
        tbis, _ = data.test_original[elt]
        l_original.append(tbis)
    cte = 30.0/9.0
    k = len(l)
    n = int(np.sqrt(cte * k))
    m = int(k/(n * 1.0))
    if (n*m<k):
        m = m+1
    width=20
    mult = 2
    if model is None:
        mult = 1
    f, ax = plt.subplots(mult*m,n,squeeze=False, figsize=(width,int(width*m/(n*2.0))))
    for i in range(m):
        if model is not None:
            for j in range(n):
                if(j+n*i < k):
                    ax[mult*i+1,j].tick_params(axis=u'both', which=u'both',length=0)
                    ax[mult*i+1,j].set_ylim([-0.5,10.5])
                    ax[mult*i+1,j].set_xlim([-1.5,12.5])
                    ax[mult*i+1,j].set_xticks([])
                    ax[mult*i+1,j].set_xticks(np.arange(0.5,9.5,1), minor=True)
                    ax[mult*i+1,j].set_yticks([])
                    ax[mult*i+1,j].grid(False)
                    ax[mult*i+1,j].set_aspect('equal')
                    L = F.softmax(model(l[j+n*i]), dim=1).cpu().data.numpy().flatten()
                    C = [(0.9, 0.1, 0.0, 1.0), (0.0, 0.1, 0.9, 1.0)]
                    ax[mult*i+1,j].barh([1,5], [z * 10.0 for z in reversed(L)], color=C)
                    for idx in range(len(L)):
                        if L[idx]>0.02:
                            ax[mult*i+1,j].text(10.0*L[idx]+0.15,(len(L)-1-idx+0.1)*4.0,idx)
                else:
                    ax[mult*i+1,j].axis('off')
        # ------------------
        for j in range(n):
            if(j+n*i < k):
                ax[mult*i+0,j].tick_params(axis=u'both', which=u'both',length=0)
                ax[mult*i+0,j].set_xticks([])
                ax[mult*i+0,j].set_yticks([])
                ax[mult*i+0,j].grid(False)
                ax[mult*i+0,j].set_xticklabels([])
                ax[mult*i+0,j].set_yticklabels([])
                img = None
                if original:
                    img = l_original[j + n * i]
                else:
                    img = l[j + n * i]
                if img.shape[0] == 3:
                    N = img[:, :, :]
                    ax[mult * i + 0, j].imshow(N.permute(1, 2, 0), )
                else:
                    N = img[0, :, :]
                    ax[mult*i+0,j].matshow(N, cmap='Greys', )
            else:
                ax[mult*i+0,j].axis('off')
    plt.show()
