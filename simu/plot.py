import numpy as np
import matplotlib.pyplot as plt
from matplotlib import rc

def plot(x, y1, y2):
    cnt = x
    x = [i for i in range(0, cnt)]

    rc('mathtext', default='regular')

    fig = plt.figure()
    ax = fig.add_subplot(111)

    lns1 = ax.plot(x, y1, '-', label = 'Actual Usage')


    ax2 = ax.twinx()
    lns2 = ax2.plot(x, y2, '-r', label = 'Current Balance')

    # added these three lines
    lns = lns1+lns2
    labs = [l.get_label() for l in lns]
    ax.legend(lns, labs, loc=0)

    ax.grid()
    ax.set_xlabel("Time")
    ax.set_ylabel(r"Actual Usage")
    ax2.set_ylabel(r"Current Balance")

    ax2.set_ylim(0, (y1[cnt - 1] + 100) / 100)
    ax.set_ylim(0, y1[cnt - 1] + 100)

    plt.show()

def readIn():
    cnt = 0
    y1, y2 = [0], [0]
    while(True):
        in_str = input().split();

        if(in_str[0] == "-1"):
            break
        elif(in_str[0] != "[INFO]"):
            continue
            
        # balance, actual usage, util rate
        tmp1, tmp2 = map(float, in_str[1:-1])

        y1.append(tmp1)
        y2.append(tmp2)

        cnt += 1

    return (cnt + 1, y1, y2)

def main():
    x, y1, y2 = readIn()
    
    plot(x, y1, y2)

if __name__ == '__main__':
    main()