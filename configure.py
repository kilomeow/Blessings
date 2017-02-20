import os

makefile=""
cppFiles=[]

currPath=os.getcwd()

def walk(dir):
    for name in os.listdir(dir):
        path = os.path.join(dir, name)
        if os.path.isfile(path):
            if name[-4:]!=".cpp":
                continue

            cppFiles.append(os.path.join(dir, name))

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

            print(filesToInclude)

            f.close()
        else:
            if name==".git":
                continue
            walk(path)

walk(currPath)
