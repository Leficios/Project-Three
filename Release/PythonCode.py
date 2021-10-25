import re
import string
import collections


def AddingItems():
    # Opens the file 
    with open('CS210_Project_Three_Input_File.txt') as fp:
        counts = collections.Counter(line.strip() for line in fp)
    # For evey item display amount how many sold
    for key in counts:
        print('%s %d' % (key, counts[key]))

def ItemCounter(v):
    # Alwyas capatalize first letter
    v = v.capitalize()
    # User count function int the file
    with open('CS210_Project_Three_Input_File.txt') as fp:
        data = fp.read()
        occurences = data.count(v)
        return occurences

def ItemStore():
    # Open both the read and the write files
    with open('frequency.dat', "w") as wp:    
        # Store in the dictionary 
        with open('CS210_Project_Three_Input_File.txt') as fp:
            counts = collections.Counter(line.strip() for line in fp)
        # Write to the outpute
        for key in counts:
            wp.write('%s %d\n' % (key, counts[key]))
    # Tell user when its properly closed
    if wp.closed:
        print('Success')