#!/usr/bin/env python

import re
import subprocess
from argparse import ArgumentParser

# from pycparser import parse_file, c_parser, c_generator, c_ast

global_variables_begin_label = r"[^\S\n\r]*// _GLOBAL_VARIABLES_BEGIN_.*\n"
global_variables_end_label = r"[^\S\n\r]*// _GLOBAL_VARIABLES_END_.*\n"
setup_begin_label = r"[^\S\n\r]*// _SETUP_BEGIN_.*\n"
setup_end_label = r"[^\S\n\r]*// _SETUP_END_.*\n"
loop_begin_label = r"[^\S\n\r]*// _LOOP_BEGIN_.*\n"
loop_end_label = r"[^\S\n\r]*// _LOOP_END_.*\n"
file_path = [
    "./src/devices/Cordinator.cpp",
    "./src/devices/Router.cpp",
]


def main():
    parser: ArgumentParser = ArgumentParser(add_help=True)
    parser.add_argument(
        "-c", "--cordinator", help="cordinator file path hoge/huga/*.ino", required=True
    )
    parser.add_argument(
        "-r", "--router", help="router file path hoge/huga/*.ino", required=True
    )
    parser.add_argument("-b", "--build_dir", help="build directory path", required=False, default="build")
    argv = parser.parse_args()

    ino_str: str
    for i, ino_file_path in enumerate([argv.cordinator, argv.router]):
        with open(ino_file_path, "r") as ino:
            ino_str = ino.read()
        insert_code = re.search(
            r"([\s\S]*)void\s*setup\s*\(\s*\)\s*{([\s\S]*)}\s*void\s*loop\s*\(\s*\)\s*{([\s\S]*)}\s*",
            ino_str,
        )
        if insert_code == None:
            print("error:", argv.ino, "format is wrong.")
            exit(1)

        with open(file_path[i], "r") as f:
            before_lines = f.readlines()
            after_lines = []
        ln_cnt = 0
        while ln_cnt < len(before_lines):
            after_lines.append(before_lines[ln_cnt])
            if re.search(global_variables_begin_label, before_lines[ln_cnt]) != None:
                after_lines.append(insert_code.groups()[0] + "\n")
                while re.search(global_variables_end_label, before_lines[ln_cnt]) == None:
                    ln_cnt += 1
                    if ln_cnt == len(before_lines):
                        print("error failed to parse file:", file_path[i])
                        exit(1)
                continue
            if re.search(setup_begin_label, before_lines[ln_cnt]) != None:
                after_lines.append(insert_code.groups()[1] + "\n")
                while re.search(setup_end_label, before_lines[ln_cnt]) == None:
                    ln_cnt += 1
                    if ln_cnt == len(before_lines):
                        print("error failed to parse file:", file_path[i])
                        exit(1)
                continue
            if re.search(loop_begin_label, before_lines[ln_cnt]) != None:
                after_lines.append(insert_code.groups()[2] + "\n")
                while re.search(loop_end_label, before_lines[ln_cnt]) == None:
                    ln_cnt += 1
                    if ln_cnt == len(before_lines):
                        print("error failed to parse file:", file_path[i])
                        exit(1)
                continue
            ln_cnt += 1
        with open(file_path[i], "w") as f:
            f.writelines(after_lines)
    
    # build
    cmd: str = "cd {} && sudo cmake --build . --target install".format(argv.build_dir)
    subprocess.run("cd build && sudo cmake --build . --target install", shell=True)

if __name__ == "__main__":
    main()
