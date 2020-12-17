import sys
import time


def printProgressBar(iteration, total, prefix='', suffix='', decimals=1, length=100, fill='█', printEnd="\r"):
    percent = ("{0:." + str(decimals) + "f}").format(100 * (iteration / float(total)))
    filledLength = int(length * iteration // total)
    bar = fill * filledLength + '-' * (length - filledLength)
    # print('\r%s |%s| %s%% %s' % (prefix, bar, percent, suffix), end=printEnd)
    sys.stdout.write('\r %s |%s| %s%% %s [%s-%s]' % (prefix, bar, percent, suffix, iteration, total))
    # Print New Line on Complete
    if iteration == total:
        print()
    sys.stdout.flush()


def progress(iteration, total):
    percent = ("{0:." + str(1) + "f}").format(100 * (iteration / float(total)))
    sys.stdout.write("\r [ %s" % percent + "% ] ")
    sys.stdout.flush()


if __name__ == '__main__':
    t = 20000
    for i in range(t + 1):
        time.sleep(0.00001)
        printProgressBar(i, t)
    pass
