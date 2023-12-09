import os, subprocess, sys

import globals

def run(project=""):
    ret = 0
    default_project = False
    project_cmd = []
    cwd = os.getcwd()

    if project != "" and project in globals.EXE_PATH:
        if globals.IsWindows():
            project_cmd = ["cmd.exe", "/c", "{}\\run.bat".format(globals.TOOLS_DIR), globals.EXE_PATH[project], project]
        else:
            project_cmd = ["{}/{}{}".format(os.getcwd(),  globals.EXE_PATH[project], project)]
            cwd = globals.EXE_PATH[project]
    else:
        default_project = True
        if globals.IsWindows():
            project_cmd = ["cmd.exe", "/c", "{}\\run.bat".format(globals.TOOLS_DIR), globals.EXE_PATH[globals.DEFAULT], globals.DEFAULT]
        else:
            project_cmd = ["{}/{}{}".format(os.getcwd(),  globals.EXE_PATH[globals.DEFAULT], globals.DEFAULT)]
            cwd = globals.EXE_PATH[globals.DEFAULT]

    print("\n************** Begin project : <{}>".format("DEFAULT PROJECT" if default_project else sys.argv[i]))
    ret = subprocess.call(project_cmd, cwd=cwd)
    print("************** End project : <{}>".format("DEFAULT PROJECT" if default_project else sys.argv[i]))
    return ret

len_cmd = len(sys.argv)

if len_cmd > 1:
    i = 1
    ret = 0
    
    while i < len_cmd:
        ret = run(sys.argv[i])

        if ret != 0:
            sys.exit(ret)
        i += 1
else:
    ret = run()

    sys.exit(ret)