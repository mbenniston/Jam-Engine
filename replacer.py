#!/bin/bash
import sys

def renameOcurrances(file, pattern, replaceStr):
    file = open(file, "r")
    lines = file.read()
    lines = lines.replace(pattern, replaceStr)
    file.close()
    return lines
    

if __name__ == '__main__':
     
    if len(sys.argv) > 3:
        output = renameOcurrances(sys.argv[1], sys.argv[2], sys.argv[3])

        if "-oo" in sys.argv:
            file = open(sys.argv[1], "w")
            file.write(output)
            file.close()
        elif "-o" in sys.argv and len(sys.argv) > 5:
            fileName = sys.argv[sys.argv.index("-o") + 1]
            file = open(fileName, "w")
            file.write(output)
            file.close()
        else:
            print(output)
    else:
        print("Please give a file name, pattern string and replacement string (-o to write the output to a file)")
