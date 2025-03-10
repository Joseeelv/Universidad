# Python Program to Get File Creation and Modification Date
import time
import pathlib
import os

file = pathlib.Path('./data_file.txt')
print("Last modification time: %s" % time.ctime(os.path.getmtime(file)))
print("Last metadata change time or path creation time: %s" % time.ctime(os.path.getctime(file)))