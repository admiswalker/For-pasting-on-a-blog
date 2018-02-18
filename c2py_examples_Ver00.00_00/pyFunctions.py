
#--------------------------------------------------------------------------------------------------------
#"""
import numpy as np
def plus_a_b(a, b): return a+b
def plus_vecA_vecB(vecA, vecB): return vecA+vecB
def selfMult(a, vecB, vecC):
    a[0]=a[0]*a[0]
    for i in range(len(vecB)): vecB[i]=vecB[i]*vecB[i]
    for i in range(len(vecC)): vecC[i]=vecC[i]*vecC[i]
def checkTypes(Numpy, builtIn, pNumpy, pBuiltIn):
    print(type(Numpy), Numpy)
    print(type(builtIn), builtIn)
    print(type(pNumpy), pNumpy)
    print(type(pBuiltIn), pBuiltIn)
def changeLen(pVec1, vec2):
    pVec1[0]=np.append(pVec1[0], 4) # numpy    # numpy is not able to add values without changing address of variables. so we need to treat as a pointer like objects (self inclusion list).
    vec2.append(4)                  # built-in
def multiRet(): return (9, 9, [1,2,3], [4,5,6])
    
#"""
#--------------------------------------------------------------------------------------------------------
"""
def emptyFunc(): return;
#"""
#--------------------------------------------------------------------------------------------------------
"""
import numpy as np
from PIL import Image

def imgPath2mat_rRGB(path):
    imgRaw = Image.open(path)
    imgRGB = imgRaw.split()
    imgR = imgRGB[0]
    imgG = imgRGB[1]
    imgB = imgRGB[2]
    return (imgR, imgG, imgB)
def mat_rRGB2img(path, imgR, imgG, imgB):
    imgCombined = np.dstack((np.dstack((imgR, imgG)), imgB))
    imgPIL      = Image.fromarray(imgCombined)
    imgPIL.save(path)
#"""
#--------------------------------------------------------------------------------------------------------
"""
import matplotlib as mpl        # "QXcbConnection: Could not connect to display" への対策
mpl.use('Agg')                  # "QXcbConnection: Could not connect to display" への対策
import matplotlib.pyplot as plt # "QXcbConnection: Could not connect to display" への対策
import matplotlib.ticker as tick
def vec2graph(writeName, vecX, vecY):
    plt.clf()
    fig = plt.figure(figsize=(8, 2.5)) # アスペクト比の設定
    ax1 = fig.add_subplot(111)
    ax1.plot(vecX, vecY, color='k', linewidth=0.5)

    title  = "Example of a \"vec2graph()\" python function called by \"sstd::c2py()\".   \n"
    title += "In this exmaple, a type of std::vector<double> in C++ is converted to\n"
    title += "a graph through the matplotlib in Python. Python function is called by  \n"
    title += "C++ only 2 lines enabled by \"sstd::c2py()\".                                           "
    ax1.set_title(title)
    ax1.set_xlabel("Time [sec]\nFig 1.  0.1 Hz sin wave sampled by 10 Hz.")
    #ax1.set_xlim(0, 60)
    ax1.xaxis.set_major_locator(tick.MultipleLocator(5))
    ax1.xaxis.set_minor_locator(tick.MultipleLocator(1))
    
    ax1.set_ylabel("Amplitude")
    ax1.set_ylim(-1.1, 1.1)
    ax1.yaxis.set_major_locator(tick.MultipleLocator(0.5))
    ax1.yaxis.set_minor_locator(tick.MultipleLocator(0.1))
    
    plt.savefig(writeName, bbox_inches="tight")
#"""
#--------------------------------------------------------------------------------------------------------


