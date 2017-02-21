#!/usr/bin/python3

import sys
import os



makefile=""
structure=[]

currPath=os.getcwd()

def walk(dir):
    for name in os.listdir(dir):
        path = os.path.join(dir, name)
        if os.path.isfile(path):
            if name[-4:]!=".cpp":
                continue

            f=open(path, "r")
            contents=f.readlines()

            filesToInclude=[]

            for string in contents:
                if string[:8]!="#include":
                    continue

                fileToInclude=string.split()[1]
                if fileToInclude[0]=="<":
                    continue

                filesToInclude.append(os.path.join(dir, fileToInclude[1:-1]))

            structure.append([os.path.join(dir, name), filesToInclude])

            f.close()
        else:
            if name==".git":
                continue
            walk(path)

walk(currPath)

for pair in structure:
    firstStr="build"+(pair[0][:-3]+"o")[len(currPath):]+" :"

    for header in pair[1]:
        firstStr=firstStr+" "+header[len(currPath)+1:]

    secondStr="\tclang --std=c++1z -c "+(pair[0])[len(currPath)+1:]+" -o "+"build"\
        +(pair[0][:-3]+"o")[len(currPath):]

    makefile=makefile+firstStr+"\n"+secondStr+"\n\n"

firstStr="all:"
for pair in structure:
    firstStr=firstStr+" build"+(pair[0][:-3]+"o")[len(currPath):]

secondStr="\tclang --std=c++1z"
for pair in structure:
    secondStr=secondStr+" build"+(pair[0][:-3]+"o")[len(currPath):]
secondStr=secondStr+" -o work"

makefile=makefile+firstStr+"\n"+secondStr

f=open("Makefile", "w")
f.write(makefile)
f.close()
