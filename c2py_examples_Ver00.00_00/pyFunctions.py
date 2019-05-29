
#--------------------------------------------------------------------------------------------------------

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

#--------------------------------------------------------------------------------------------------------

def emptyFunc(): return;

#--------------------------------------------------------------------------------------------------------

import matplotlib as mpl        # "QXcbConnection: Could not connect to display" への対策
mpl.use('Agg')                  # "QXcbConnection: Could not connect to display" への対策
import matplotlib.pyplot as plt # "QXcbConnection: Could not connect to display" への対策
import matplotlib.ticker as tick
def vec2graph(writeName, vecX, vecY):
    plt.clf()
    fig = plt.figure(figsize=(9, 3)) # アスペクト比の設定
    ax1 = fig.add_subplot(111)
    ax1.plot(vecX, vecY, color='k', linewidth=0.5)
    
    title  = "An example of Plotting a figure of sin wave data generated on C++,\n"
    title += "using matplotlib which is a famous graph plotting library of python. \n"
    title += "\"sstd::c2py()\" convertes a type of std::vector<double> on C++ to  \n"
    title += "numpy array type on Python, and calling a Python function from      \n"
    title += "only 2 lines of C++ code.                                                                    "
    ax1.set_title(title)
    
    ax1.grid(which='minor', linewidth=0.5, linestyle=':',  color='gainsboro')
    ax1.grid(which='major', linewidth=0.5, linestyle='-',  color='silver'    )
    
    ax1.tick_params(pad=5, which='major', direction='in', bottom=True, top=True, left=True, right=True, length=4) # 軸の余白 # which: major tick と minor tick に対して変更を適用 # tick を内側方向に # tick を bottom, top, left, right に付加 # tick width # tick length
    ax1.tick_params(pad=5, which='minor', direction='in', bottom=True, top=True, left=True, right=True, length=2) # 軸の余白 # which: major tick と minor tick に対して変更を適用 # tick を内側方向に # tick を bottom, top, left, right に付加 # tick width # tick length
    
    ax1.set_xlabel("Time [sec]\nFig 1.  0.1 Hz sin wave sampled by 10 Hz, 0-60 sec.")
    ax1.set_xlim(0-1, 60+1)
    ax1.xaxis.set_major_locator(tick.MultipleLocator(5))
    ax1.xaxis.set_minor_locator(tick.MultipleLocator(1))
    
    ax1.set_ylabel("Amplitude")
    ax1.set_ylim(-1.1, 1.1)
    ax1.yaxis.set_major_locator(tick.MultipleLocator(0.5))
    ax1.yaxis.set_minor_locator(tick.MultipleLocator(0.1))
    
    plt.savefig(writeName, bbox_inches="tight") # , dpi=100

#--------------------------------------------------------------------------------------------------------

def vvec2graph(writeName, vLabel, vvecX, vvecY):
    plt.clf()
    fig = plt.figure(figsize=(9, 3)) # アスペクト比の設定
    ax1 = fig.add_subplot(111)
    #cmap = plt.get_cmap("tab10")
    vColor=['black', 'blue', 'red']
    vLineStyle = ['solid', 'solid', 'solid'] # solid, dashed, dashdot, dotted
    for i in range(len(vvecX)):
        ax1.plot(vvecX[i], vvecY[i], linewidth=0.5, color=vColor[i], linestyle=vLineStyle[i], label=vLabel[i])
        #ax1.plot(vvecX[i], vvecY[i], linewidth=0.5, color=cmap(i), linestyle=vLineStyle[i], label=vLabel[i])
    ax1.legend(loc='upper right')
    
    ax1.grid(which='minor', linewidth=0.5, linestyle=':',  color='gainsboro')
    ax1.grid(which='major', linewidth=0.5, linestyle='-',  color='silver'    )
    
    ax1.tick_params(pad=5, which='major', direction='in', bottom=True, top=True, left=True, right=True, length=4) # 軸の余白 # which: major tick と minor tick に対して変更を適用 # tick を内側方向に # tick を bottom, top, left, right に付加 # tick width # tick length
    ax1.tick_params(pad=5, which='minor', direction='in', bottom=True, top=True, left=True, right=True, length=2) # 軸の余白 # which: major tick と minor tick に対して変更を適用 # tick を内側方向に # tick を bottom, top, left, right に付加 # tick width # tick length
    
    ax1.set_xlabel("Time [sec]\nFig 2.  0.1 Hz sin, cos and -cos wave sampled by 10 Hz, 0-60 sec.")
    ax1.set_xlim(0-1, 60+1)
    ax1.xaxis.set_major_locator(tick.MultipleLocator(5))
    ax1.xaxis.set_minor_locator(tick.MultipleLocator(1))
    
    ax1.set_ylabel("Amplitude")
    ax1.set_ylim(-1.1, 1.1)
    ax1.yaxis.set_major_locator(tick.MultipleLocator(0.5))
    ax1.yaxis.set_minor_locator(tick.MultipleLocator(0.1))
    
    plt.legend(loc='best')
    plt.savefig(writeName, bbox_inches="tight") # , dpi=100

#--------------------------------------------------------------------------------------------------------

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

#--------------------------------------------------------------------------------------------------------


