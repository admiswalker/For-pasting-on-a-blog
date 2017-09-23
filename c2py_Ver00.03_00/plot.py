# Python 2.7

import sys
import matplotlib as mpl           # "QXcbConnection: Could not connect to display" への対策
mpl.use('Agg')                     # "QXcbConnection: Could not connect to display" への対策
import matplotlib.pyplot as plt    # "QXcbConnection: Could not connect to display" への対策
import matplotlib.ticker as tick

from c2py import*


def plot_ax(ax, X_interval, vec):
    # X軸の値域を指定
    ax.set_xlim(0, len(vec)-1)

    # Y軸の値域を指定
    y_max = -10
    y_min =  10
    while y_max < max(vec): y_max += 1 # y 軸の最大値・最小値を 1 の倍数値とする
    while y_min > min(vec): y_min -= 1 # y 軸の最大値・最小値を 1 の倍数値とする
    ax.set_ylim(y_min, y_max)

    # 主目盛の数値を指定
    X_tick_discription = [('%d' % (5*(i-1))) for i in range(int((len(vec)*X_interval)/5)+2)] # 5 sec interval (なんかmatplot バグってるきがして，-5 から始めないとばぐる)
    ax.set_xticklabels(X_tick_discription) # , rotation=0

    # 主目盛の設定 (major ticks)
    ax.tick_params(pad=5, which='minor', direction='in', bottom='on', top='on', left='on', right='on', length=2) # 軸の余白 # which: major tick と minor tick に対して変更を適用 # tick を内側方向に # tick を bottom, top, left, right に付加 # tick width # tick length
    ax.xaxis.set_major_locator(tick.MultipleLocator(5/X_interval)) # 5 sec interval

    # 補助目盛の設定 (minor ticks)
    ax.tick_params(pad=5, which='major', direction='in', bottom='on', top='on', left='on', right='on', length=5) # 軸の余白 # which: major tick と minor tick に対して変更を適用 # tick を内側方向に # tick を bottom, top, left, right に付加 # tick width # tick length
    ax.xaxis.set_minor_locator(tick.MultipleLocator(1/X_interval)) # 1 sec interval
    ax.yaxis.set_minor_locator(tick.MultipleLocator(0.1))

    # vec をプロット
    ax.plot(vec, linewidth=0.5) # , color='k', marker='.', marker='o', linestyle='dashed',
    
def vec2graph_1(WriteName, X_interval, vec1):
    plt.clf()#メモリのクリア

    # Figure インスタンスを生成
    fig = plt.figure(figsize=(8, 1*2.5)) # 3*5, 1*5 # アスペクト比の設定

    # Axes インスタンスを生成
    ax1 = fig.add_subplot(111)
    plot_ax(ax1, X_interval, vec1)

    # グラフタイトル、X軸 Y軸のキャプション
    ax1.set_title("Title")
    ax1.set_ylabel("sin amplitude\n(0.3 Hz)")
    ax1.set_xlabel("time [sec]\nFig 1. Up side graph is a 0.3 Hz sin wave which was sampled by 10 Hz.")

    # グラフの保存
    plt.savefig(WriteName, bbox_inches="tight") # , dpi=100
    
def vec2graph_2(WriteName, X_interval, vec1, vec2):
    plt.clf()#メモリのクリア

    # Figure インスタンスを生成
    fig = plt.figure(figsize=(8, 2*2.5)) # 3*5, 1*5 # アスペクト比の設定

    # Axes インスタンスを生成
    ax1 = fig.add_subplot(211)
    ax2 = fig.add_subplot(212)
    plot_ax(ax1, X_interval, vec1)
    plot_ax(ax2, X_interval, vec2)

    # グラフタイトル、X軸 Y軸のキャプション
    ax1.set_title("Title")
    ax1.set_ylabel("sin amplitude\n(0.3 Hz)")
    ax2.set_ylabel("cos amplitude\n(0.3 Hz)")
    ax2.set_xlabel("time [sec]\nFig 1. Up side graph is a 0.3 Hz sin wave which was sampled by 10 Hz, \nand down side graph is a 0.3 Hz cos wave which was sampled by 10 Hz.")

    # グラフの保存
    plt.savefig(WriteName, bbox_inches="tight") # , dpi=100
    
def vec2graph_3(WriteName, X_interval, vec1, vec2, vec3):
    plt.clf()#メモリのクリア

    # Figure インスタンスを生成
    fig = plt.figure(figsize=(8, 3*2.5)) # 3*5, 1*5 # アスペクト比の設定

    # Axes インスタンスを生成
    ax1 = fig.add_subplot(311)
    ax2 = fig.add_subplot(312)
    ax3 = fig.add_subplot(313)
    plot_ax(ax1, X_interval, vec1)
    plot_ax(ax2, X_interval, vec2)
    plot_ax(ax3, X_interval, vec3)

    # グラフタイトル、X軸 Y軸のキャプション
    ax1.set_title("Title")
    ax1.set_ylabel("sin amplitude\n(0.3 Hz)")
    ax2.set_ylabel("cos amplitude\n(0.3 Hz)")
    ax3.set_ylabel("2*sin amplitude\n(0.3 Hz)")
    ax3.set_xlabel("time [sec]\nFig 1. Up side graph is a 0.3 Hz sin wave which was sampled by 10 Hz, \nmiddle side graph is a 0.3 Hz cos wave which was sampled by 10 Hz, \nand down side graph is a 0.3 Hz 2*sin wave which was sampled by 10 Hz.")

    # グラフの保存
    plt.savefig(WriteName, bbox_inches="tight") # , dpi=100
    
def main():
    args = sys.argv
    if len(args)<=1: return

    i = [1] # 参照渡しにする
    writeName = c2py_str   (args, i)
    interval  = c2py_double(args, i)

    vec1 = c2py_vecDouble(args, i)
    if len(args) == i[0]:
        vec2graph_1(writeName, interval, vec1)
        return

    vec2 = c2py_vecDouble(args, i)
    if len(args) == i[0]:
        vec2graph_2(writeName, interval, vec1, vec2)
        return

    vec3 = c2py_vecDouble(args, i)
    if len(args) == i[0]:
        vec2graph_3(writeName, interval, vec1, vec2, vec3)
        return


main()


# How to test
#
# 引数の与え方
# [$ python -u ./plot.py writeName interval len1 vec1 len2 vec2 ... lenN vecN]
#                0       1         2        3    4    5    6    ... 2*N  2*N+1
