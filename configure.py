#!/usr/bin/python3

import sys
import os

gcc=False
ignoreList=[]

args=sys.argv[1:]
for arg in args:
    if arg=="--gcc":
        gcc=True
    elif arg[:9]=="--ignore=":
        ignoreList.append(arg[9:])
    else:
        print("Bad argument ", arg)
        exit(1)

makefile=""
structure=[]

currPath=os.getcwd()

def walk(dir):
    for name in os.listdir(dir):
        path = os.path.join(dir, name)
        if os.path.isfile(path):
            if name[-4:]!=".cpp":
                continue

            if path[len(currPath)+1:] in ignoreList:
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

    if pair[0][len(currPath)+1:-len(pair[0].split("/")[-1])]!="":
        secondStr="\tmkdir -p "+"build/"+pair[0][len(currPath)+1:-len(pair[0].split("/")[-1])]

    thirdStr=""
    if not gcc:
        thirdStr="\tclang --std=c++1z -c "+(pair[0])[len(currPath)+1:]+" -o "+"build"\
            +(pair[0][:-3]+"o")[len(currPath):]
    else:
        thirdStr="\tg++ --std=c++1z -c "+(pair[0])[len(currPath)+1:]+" -o "+"build"\
            +(pair[0][:-3]+"o")[len(currPath):]

    if secondStr:
        makefile=makefile+firstStr+"\n"+secondStr+"\n"+thirdStr+"\n\n"
    else:
        makefile=makefile+firstStr+"\n"+thirdStr+"\n\n"

firstStr="all:"
for pair in structure:
    firstStr=firstStr+" build"+(pair[0][:-3]+"o")[len(currPath):]

secondStr=""
if not gcc:
    secondStr="\tclang -lstdc++ --std=c++1z"
else:
    secondStr="\tg++ -lstdc++ --std=c++1z"
for pair in structure:
    secondStr=secondStr+" build"+(pair[0][:-3]+"o")[len(currPath):]
secondStr=secondStr+" -o work\n"

makefile=makefile+"clean:\n\trm -rf build\n"

makefile=firstStr+"\n"+secondStr+"\n"+makefile

f=open("Makefile", "w")
f.write(makefile)
f.close()
