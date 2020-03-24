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
    archiver_type=""
    archiver_executable=""
    prefix="/usr"

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
        elif args[i]=="--archiver_type":
            if i==len(args)-1:
                print("Error: --archiver_type key given without arguments")

            archiver_type=args[i+1]
            i+=1
        elif args[i]=="--archiver_executable":
            if i==len(args)-1:
                print("Error: --archiver_executable key given without arguments")

            archiver_executable=args[i+1]
            i+=1
        elif args[i]=="--prefix":
            if i==len(args)-1:
                print("Error: --prefix key given without arguments")

            prefix=args[i+1]
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
        "compiler_executable" : compiler_executable,\
        "archiver_type" : archiver_type,\
        "archiver_executable" : archiver_executable,\
        "prefix" : prefix}

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

    print("Filenames intersected while adding dictionaries")
    exit(1)

def walk(dir, sources_dir): #walk and scan sources/headers files
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

def linux_compile_objects(target_name, target, files_given, compiler_type,\
    compiler_executable, temp_file, add_flags=""):

    makefile=[]

    for source in files_given["sources"][target["sources_dict"]]:
        print("Processing source file "+source)

        source_target_name="build/"+target_name+"/"+source[:-4]+".o"

        resCode=os.system(compiler_executable+" -std=c++14 -MM -MF "+temp_file+" -MT "+\
            source_target_name+" "+source)
        if resCode!=0:
            print("Error: header scan finished unsuccesfull. Stopping configure")
            exit(1)

        f=open(temp_file)
        lines=f.readlines()
        f.close()

        for line in lines:
            makefile.append(line[:-1]) #Without \n

        dir="build/"+target_name+"/"+"/".join(source.split("/")[:-1])
        makefile.append("\tmkdir -p "+dir)

        compiler_flags=""
        if compiler_type in target["compiler_flags"].keys():
            if target["compiler_flags"][compiler_type]!="":
                compiler_flags=" "+target["compiler_flags"][compiler_type]

        if compiler_type in files_given["sources"]\
            [target["sources_dict"]][source].keys():
            compiler_flags=compiler_flags+" "+files_given["sources"]\
                [targets["sources_dict"]][source][compiler_type]

        if add_flags!="":
            compiler_flags=compiler_flags+" "+add_flags

        include_dirs_str=""
        for include_dir in target["include_dirs"]:
            include_dirs_str=include_dirs_str+" -I"+include_dir

        preprocessor_directives_str=""
        for directive in target["preprocessor_directives"]:
            preprocessor_directives_str=" -D"+directive

        line="\t"+compiler_executable+compiler_flags+preprocessor_directives_str\
            +include_dirs_str+" "+source+" -c -o "+source_target_name

        makefile.append(line)

    return makefile

def linux_static_lib(target_name, target, files_given, compiler_type, compiler_executable,\
    archiver_type, archiver_executable, temp_file):

    if not compiler_type in target["compiler_flags"].keys():
        print("Warning: no compiler_flags specified for compiler type ", compiler_type,\
            " in target ", target_name, ", but this compiler choosen")

    makefile=["", "#Target "+target_name]

    first_str=target_name+":"

    for source in files_given["sources"][target["sources_dict"]]:
        first_str=first_str+" \\\n build/"+target_name+"/"+source[:-4]+".o"

    second_str="\t"+archiver_executable+" rcs lib"+target["output_name"]+".a $^"

    makefile.append(first_str)
    makefile.append(second_str)

    makefile=makefile+linux_compile_objects(target_name,\
        target, files_given, compiler_type, compiler_executable, temp_file)

    return makefile


def linux_shared_lib(target_name, target, files_given, compiler_type, compiler_executable,\
    temp_file):

    if not compiler_type in target["compiler_flags"].keys():
        print("Warning: no compiler_flags specified for compiler type", compiler_type,\
            "in target", target_name, ", but this compiler choosen")

    makefile=["", "#Target "+target_name]

    first_str=target_name+":"

    for source in files_given["sources"][target["sources_dict"]]:
        first_str=first_str+" \\\n build/"+target_name+"/"+source[:-4]+".o"

    compiler_flags=""
    if compiler_type in target["compiler_flags"].keys():
        compiler_flags=" "+target["compiler_flags"][compiler_type]

    second_str="\t"+compiler_executable+compiler_flags+\
        " -shared -o lib"+target["output_name"]+".so $^"

    makefile.append(first_str)
    makefile.append(second_str)

    makefile=makefile+linux_compile_objects(target_name,\
        target, files_given, compiler_type, compiler_executable, temp_file, "-fpic")

    return makefile

def linux_executable(target_name, targets, files_given, compiler_type, compiler_executable,\
    temp_file):

    target=targets[target_name]

    if not compiler_type in target["compiler_flags"].keys():
        print("Warning: no compiler_flags specified for compiler type ", compiler_type,\
            " in target ", target_name, ", but this compiler choosen")

    makefile=["", "#Target "+target_name]

    first_str=target_name+":"

    object_files_str=""
    for source in files_given["sources"][target["sources_dict"]]:
        first_str=first_str+" \\\n build/"+target_name+"/"+source[:-4]+".o"
        object_files_str=object_files_str+" "+"build/"+target_name+"/"+source[:-4]+".o"
    for needed_target in target["link_with_target"]:
        first_str=first_str+" \\\n "+needed_target

    link_targets_str=""
    for needed_target in target["link_with_target"]:
        if targets[needed_target]["target_type"]=="static_lib":
            link_targets_str=link_targets_str+" -l:lib"+targets[needed_target]["output_name"]+".a"
        elif targets[needed_target]["target_type"]=="shared_lib":
            link_targets_str=link_targets_str+" -l:lib"+targets[needed_target]["output_name"]+".so"
        else:
            print("Error: couldn't link", target_name, "with", needed_target)
            exit(1)

    compiler_flags_str=""
    if compiler_type in target["compiler_flags"].keys():
        compiler_flags_str=" "+target["compiler_flags"][compiler_type]

    include_dirs_str=""
    for include_dir in target["include_dirs"]:
        include_dirs_str=include_dirs_str+" -I"+include_dir

    lib_dirs_str=""
    for lib_dir in target["lib_dirs"]:
        lib_dirs_str=lib_dirs_str+" -L"+lib_dir
    if link_targets_str!="":
        lib_dirs_str=lib_dirs_str+" -L$(PWD)"

    link_with_str=""
    for lib in target["link_with"]:
        link_with_str=" -l"+lib

    preprocessor_directives_str=""
    for directive in target["preprocessor_directives"]:
        preprocessor_directives_str=" -D"+directive

    second_str="\t"+compiler_executable+compiler_flags_str+\
        " -o "+target["output_name"]+object_files_str+lib_dirs_str+include_dirs_str+\
        link_with_str+link_targets_str

    makefile.append(first_str)
    makefile.append(second_str)

    makefile=makefile+linux_compile_objects(target_name,\
        target, files_given, compiler_type, compiler_executable, temp_file)

    return makefile

def linux_install(target_name, targets, files_given, prefix):
    target=targets[target_name]

    makefile=["", "#Target "+target_name]

    first_str=target_name+":"
    makefile.append(first_str)

    for needed_target in target["targets_to_install"]:
        if targets[needed_target]["headers_dict"]!=None:
            makefile.append("\t#Headers of "+needed_target)

            for header in files_given["headers"][targets[needed_target]["headers_dict"]]:
                dest_path=os.path.join(prefix, target["includes_path"],\
                    "/".join(header.split("/")[:-1]))
                makefile.append("\tmkdir -p "+dest_path)
                makefile.append("\tcp "+header+" "+dest_path)

            makefile.append("")

    for needed_target in target["targets_to_install"]:
        if targets[needed_target]["target_type"]!="static_lib":
            makefile.append("\t#Static lib "+needed_target)

            dest_path=os.path.join(prefix, target["static_libs_path"])
            makefile.append("\tmkdir -p "+dest_path)
            makefile.append("\t-cp lib"+targets[needed_target]["output_name"]+".a "+\
                dest_path)

            makefile.append("")
        elif targets[needed_target]["target_type"]!="shared_lib":
            makefile.append("\t#Shared lib "+needed_target)

            dest_path=os.path.join(prefix, target["shared_libs_path"])
            makefile.append("\tmkdir -p "+dest_path)
            makefile.append("\t-cp lib"+targets[needed_target]["output_name"]+".so "+\
                dest_path)

            makefile.append("")
        elif targets[needed_target]["target_type"]!="executable":
            makefile.append("\t#Executable "+needed_target)

            dest_path=os.path.join(prefix, target["executable_path"])
            makefile.append("\tmkdir -p "+dest_path)
            makefile.append("\tcp "+targets[needed_target]["output_name"]+" "+\
                dest_path)
            makefile.append("\tchmod +x "+dest_path+targets[needed_target]["output_name"])

            makefile.append("")

    return makefile

def linux_uninstall(target_name, targets, files_given, prefix):
    target=targets[target_name]

    makefile=["", "#Target "+target_name]

    first_str=target_name+":"
    makefile.append(first_str)

    makefile.append("\t#Removing headers")
    for headers_path in target["headers_pathes"]:
        makefile.append("\trm -rf "+os.path.join(prefix, headers_path))
    makefile.append("")

    for needed_target in target["targets_to_uninstall"]:
        if targets[needed_target]["target_type"]!="static_lib":
            makefile.append("\t#Static lib "+needed_target)

            lib_path=os.path.join(prefix, target["static_libs_path"])
            makefile.append("\t-rm -f "+os.path.join(lib_path,\
                "lib"+targets[needed_target]["output_name"]+".a"))

            makefile.append("")
        elif targets[needed_target]["target_type"]!="shared_lib":
            makefile.append("\t#Shared lib "+needed_target)

            lib_path=os.path.join(prefix, target["shared_libs_path"])
            makefile.append("\t-rm -f "+os.path.join(lib_path,\
                "lib"+targets[needed_target]["output_name"]+".so"))

            makefile.append("")
        elif targets[needed_target]["target_type"]!="executable":
            makefile.append("\t#Executable "+needed_target)

            lib_path=os.path.join(prefix, target["executable_path"])
            makefile.append("\trm -f "+os.path.join(lib_path,\
                targets[needed_target]["output_name"]))

            makefile.append("")

    return makefile

def main_linux(targets, files_given, compiler_type, compiler_executable, archiver_type, archiver_executable, prefix):
    makefile=[]

    temp_file="temp.1224asda"

    if compiler_type=="":
        print("Warning: no compiler_type specified. Default choice is gcc with\
\"gcc\" executable")
        compiler_type="gcc"
        compiler_executable="gcc"
    elif compiler_type!="" and compiler_executable=="":
        print("Warning: compiler_type specified without compiler_executable. \
Default choise is name compiler_type")
        compiler_executable=compiler_type
    elif compiler_type=="" and compiler_executable!="":
        print("Error: compiler_type not specified, but compiler_executable given")
        exit(1)

    if not compiler_type in ["gcc", "clang", "mingw", "gcc-like"]:
        print("Warning: compiler_type was not recognized. Thinking, it has \
gcc-like syntax")

    if prefix=="":
        print("Warning: using default prefix \"/\"")
        prefix="/"

    for target in targets.keys():
        print()
        print("Processing target", target)

        if targets[target]["target_type"]=="static_lib":
            makefile=makefile+linux_static_lib(target, targets[target],\
                files_given, compiler_type, compiler_executable, archiver_type, archiver_executable, temp_file)
        elif targets[target]["target_type"]=="shared_lib":
            makefile=makefile+linux_shared_lib(target, targets[target],\
                files_given, compiler_type, compiler_executable, temp_file)
        elif targets[target]["target_type"]=="executable":
            makefile=makefile+linux_executable(target, targets,\
                files_given, compiler_type, compiler_executable, temp_file)
        elif targets[target]["target_type"]=="install":
            makefile=makefile+linux_install(target, targets,\
                files_given, prefix)
        elif targets[target]["target_type"]=="uninstall":
            makefile=makefile+linux_uninstall(target, targets,\
                files_given, prefix)

    makefile.append("")
    makefile.append("#Help targets")

    makefile.append("clean:")
    for target in targets.keys():
        if targets[target]["target_type"]=="static_lib":
            makefile=makefile+["\trm -f lib"+targets[target]["output_name"]+".a"]
        elif targets[target]["target_type"]=="shared_lib":
            makefile=makefile+["\trm -f lib"+targets[target]["output_name"]+".so"]
        elif targets[target]["target_type"]=="executable":
            makefile=makefile+["\trm -f "+targets[target]["output_name"]]
    makefile.append("\trm -rf build")

    makefile_prefix=[]
    first_str="all:"
    for target in targets.keys():
        if targets[target]["in_all_target"]:
            first_str=first_str+" \\\n "+target
    makefile_prefix.append(first_str)

    makefile=makefile_prefix+makefile

    os.system("rm -f "+temp_file)

    return makefile

def main():
    print("Configure started")

    args=scan_args()
    print()
    print("Input data")
    print("Compiler type:", args["compiler_type"])
    print("Compiler_executable:", args["compiler_executable"])
    print("Archiver type:", args["archiver_type"])
    print("Archiver_executable:", args["archiver_executable"])
    print("Prefix:", args["prefix"])

    f=open(args["target_file"])
    targets=ast.literal_eval("".join(f.readlines()))
    f.close()

    print()
    print("Walking through subdirs...")
    curr_path=os.getcwd()
    files_given=walk(curr_path, curr_path)
    print("Done")

    makefile=[]

    if platform.system()=="Linux":
        print()
        print("Detected linux")
        makefile=main_linux(targets, files_given, args["compiler_type"],\
            args["compiler_executable"], args["archiver_type"], args["archiver_executable"], args["prefix"])
    else:
        print()
        print("Sorry, your operating system is unsupported now")
        print("Recognized as:", platform.system())
        exit(1)

    f=open("Makefile", "w")
    for line in makefile:
        f.write(line+"\n")
    f.close()

if __name__=="__main__":
    main()
