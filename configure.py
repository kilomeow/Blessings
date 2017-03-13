#!/usr/bin/python3

import sys
import os
import platform
import ast

def scan_args():
    args=sys.argv[1:];

    target_file=""
    compiler_type=""
    compiler_executable=""

    target_flie_given=False
    i=0
    while i<len(args):
        if args[i]=="--help":
            print("No help provided now. Sorry.")
        elif args[i]=="--compiler_type":
            if i==len(args)-1:
                print("Error: --compiler_type key given without arguments")

            compiler_type=args[i+1]
            i+=1
        elif args[i]=="--compiler_executable":
            if i==len(args)-1:
                print("Error: --compiler_executable key given without arguments")

            compiler_executable=args[i+1]
            i+=1
        else:
            target_file=args[i]
            target_flie_given=True

        i+=1

    if not target_flie_given:
        print("Error: no target file given")
        exit(1)

    return {"target_file" : target_file,\
        "compiler_type" : compiler_type,\
        "compiler_executable" : compiler_executable}

def add_dicts(dict1, dict2, f):
    keys1=dict1.keys()
    keys2=dict2.keys()

    intersection=[]
    keys1_new=[]
    keys2_new=[]
    for key in dict1:
        if key in dict2:
            intersection.append(key)
        else:
            keys1_new.append(key)
    for key in keys2:
        if not key in intersection:
            keys2_new.append(key)

    ret={}
    for key in keys1_new:
        ret[key]=dict1[key]
    for key in keys2_new:
        ret[key]=dict2[key]
    for key in intersection:
        ret[key]=f(dict1[key], dict2[key])

    return ret

def files_intersected(f1, f2):
    print(f1, f2)

    print("Filenames intersected")
    exit(1)

def walk(dir, sources_dir):
    sources={}
    headers={}

    for name in os.listdir(dir):
        path = os.path.join(dir, name)

        if os.path.isdir(path):
            if name[0]==".":
                continue

            temp=walk(path, sources_dir)

            sources=add_dicts(sources, temp["sources"],\
                lambda d1, d2: add_dicts(d1, d2, \
                lambda d1, d2: add_dicts(d1, d2, files_intersected)))
            headers=add_dicts(headers, temp["headers"],\
                lambda l1, l2: l1+l2)
        else:
            if name=="sources":
                f=open(path)
                sources_appendix=ast.literal_eval("".join(f.readlines()))
                f.close()

                sources_appendix_new={}
                for project in sources_appendix.keys():
                    sources_appendix_new[project]={}

                    for file in sources_appendix[project].keys():
                        sources_appendix_new[project][\
                            os.path.join(dir, file)[len(sources_dir)+1:]]=\
                            sources_appendix[project][file]

                sources_appendix=sources_appendix_new

                sources=add_dicts(sources, sources_appendix,\
                    lambda d1, d2: add_dicts(d1, d2, \
                    lambda d1, d2: add_dicts(d1, d2, files_intersected)))
            elif name=="headers":
                f=open(path)
                headers_appendix=ast.literal_eval("".join(f.readlines()))
                f.close()

                for project in headers_appendix.keys():
                    for i in range(0, len(headers_appendix[project])):
                        headers_appendix[project][i]=os.path.join(\
                            dir, headers_appendix[project][i])[len(sources_dir)+1:]

                headers=add_dicts(headers, headers_appendix,\
                    lambda l1, l2: l1+l2)

    return {"sources" : sources, "headers" : headers}

def main_linux(targets, files_given, compiler_type, compiler_executable):
    temp_file="temp.1224asda"

    makefile=[]

    for target in targets.keys():
        if targets[target]["target_type"]=="lib_static":
            if compiler_type=="":
                compiler_type="gcc"
                compiler_executable="gcc"

            if not compiler_type in targets[target]["compiler_flags"].keys():
                print("Warning: no compiler_flags specified for compiler type ", compiler_type,\
                    " in target ", target, ", but this compiler choosen")


            first_str=target+":"

            for source in files_given["sources"][targets[target]["sources_dict"]]:
                first_str=first_str+" \\\n build/"+target+"/"+source[:-4]+".o"

            second_str="\tar rsc lib"+targets[target]["output_name"]+".a ^$"

            makefile.append(first_str)
            makefile.append(second_str)

            for source in files_given["sources"][targets[target]["sources_dict"]]:
                source_target_name="build/"+target+"/"+source[:-4]+".o"

                os.system("gcc -MM -MF "+temp_file+" -MT "+\
                    source_target_name+" "+source)

                f=open(temp_file)
                lines=f.readlines()
                f.close()

                for line in lines:
                    makefile.append(line[:-1])

                compiler_flags=""
                if compiler_type in targets[target]["compiler_flags"].keys():
                    compiler_flags=targets[target]["compiler_flags"][compiler_type]

                if compiler_type in files_given["sources"]\
                    [targets[target]["sources_dict"]][source].keys():
                    compiler_flags=compiler_flags+" "+files_given["sources"]\
                        [targets[target]["sources_dict"]][source][compiler_type]

                if compiler_flags!="":
                    compiler_flags=" "+compiler_flags

                include_dirs_str=""
                for include_dir in targets[target]["include_dirs"]:
                    include_dirs_str=include_dirs_str+" -I"+include_dir

                line="\t"+compiler_executable+compiler_flags+include_dirs_str+" "+source+\
                    " -o "+source_target_name

                makefile.append(line)


    for line in makefile:
        print(line)



def main():
    args=scan_args()

    f=open(args["target_file"])
    targets=ast.literal_eval("".join(f.readlines()))
    f.close()

    curr_path=os.getcwd()
    files_given=walk(curr_path, curr_path)

    if platform.system()=="Linux":
        main_linux(targets, files_given, args["compiler_type"], args["compiler_executable"])
    else:
        print("Sorry, your operating system is unsupported now")
        exit(1)

if __name__=="__main__":
    main()
