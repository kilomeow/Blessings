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

tempFile="configureTemp.x1zasd"
makefile=[]
structure=[]

currPath=os.getcwd()

def walk(dir):
    for name in os.listdir(dir):
        path = os.path.join(dir, name)
        if os.path.isfile(path):
            if name[-4:]!=".cpp":
                continue

            if path[len(currPath)+1:] in ignoreList:
                print("Ignoring "+path[len(currPath)+1:])
                continue

            print("Working with "+path[len(currPath)+1:])

            os.system("g++ -MM -MF "+tempFile+" -MT build/"+path[len(currPath)+1:-3]+"o "+path)

            f=open(tempFile, "r")
            lines=f.readlines();
            f.close()

            structure.append([path[len(currPath)+1:], "build/"+path[len(currPath)+1:-3]+"o",lines])
        else:
            if name==".git":
                continue
            walk(path)

walk(currPath)

for triple in structure:
    for string in triple[2]:
        makefile.append(string)

    secondStr="\tmkdir -p "+triple[1][:-len(triple[1].split("/")[-1])]+"\n"

    thirdStr=""
    if not gcc:
        thirdStr="\tclang --std=c++1z -c "+triple[0]+" -o "+triple[1]+"\n"
    else:
        thirdStr="\tg++ --std=c++1z -c "+triple[0]+" -o "+triple[1]+"\n"

    makefile.append(secondStr)
    makefile.append(thirdStr)

firstStr="all:"
for triple in structure:
    firstStr=firstStr+" "+triple[1]
firstStr=firstStr+"\n"

secondStr=""
if not gcc:
    secondStr="\tclang -lstdc++ --std=c++1z "
else:
    secondStr="\tg++ -lstdc++ --std=c++1z "

for triple in structure:
    secondStr=secondStr+triple[1]+" \\\n\t"
secondStr=secondStr+"-o work\n"

makefile=[firstStr]+[secondStr]+makefile

makefile=makefile+["clean:\n\trm -rf build\n\trm work\n"]

f=open("Makefile", "w")
for line in makefile:
    f.write(line)
f.close()

os.remove(tempFile)
