import csv
PATH = "/mnt/remote/face/training-data/s"

for x in range(42):
    filename = ''
    fullname = ''

    filename = PATH + "{0}/".format(x)
    for y in range(1,11):
        fullname = filename + "{0}".format(y) + ".pgm;" + "{0}".format(x)
        print(fullname)