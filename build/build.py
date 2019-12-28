from distutils.spawn import find_executable

import requests, zipfile, io, os, shutil
import re
import subprocess

GLEW_URL = "https://sourceforge.net/projects/glew/files/glew/2.1.0/glew-2.1.0-win32.zip"

TEMP_DIR = "temp\\"

BIN_DIR= "..\\bin\\"
LIB_DIR= "..\\lib\\"
INCLUDE_DIR= "..\\include\\"
PROJECT_DIR= "..\\prj\\"


def DownloadURL(url, dest):
        response = requests.get(url, stream=True)
        zip = zipfile.ZipFile(io.BytesIO(response.content))
        dirName = zip.namelist()[0]
        if not os.path.isdir(dest + dirName):
                zip.extractall(dest)
        return dirName


def CreateDirectory(directory):
        if not os.path.exists(directory):
                os.makedirs(directory)


def DeleteDirectory(directory):
        if os.path.exists(directory):
                shutil.rmtree(directory, ignore_errors=True)

def CopyFile(src, dest):
        shutil.copy(src, dest)

def CopyDirectory(srcDir, destDir):
    if not os.path.exists(destDir):
        shutil.copytree(srcDir, destDir)


def DeleteDirectory(directory):
        if os.path.exists(directory):
                shutil.rmtree(directory)

def InstallGLEW():
        glewDir = DownloadURL(GLEW_URL, TEMP_DIR)

        CopyFile(TEMP_DIR + glewDir + "bin\\Release\\x64\\glew32.dll", BIN_DIR)
        CopyFile(TEMP_DIR + glewDir + "lib\\Release\\x64\\glew32.lib", LIB_DIR)
        CopyDirectory(TEMP_DIR + glewDir + "include\\GL", INCLUDE_DIR + "GL")

def GetVisualStudioVersion():
    msvcCompiler = find_executable('cl')
    if msvcCompiler:
        match = re.search(
            "(\d+).(\d+)", 
            os.environ.get("VisualStudioVersion", ""))
        if match:
            return int(match.groups()[0])
    return None

def RunCMake():
    visualStudioVersion = GetVisualStudioVersion()
    if visualStudioVersion is None:
        print "Please run build.py script in Visual Studio Developer Command Prompt"
        return
    print 'VS version "{ver}"'.format(ver=visualStudioVersion)


    if visualStudioVersion is 16:
        generator = "Visual Studio 16 2019"
    elif visualStudioVersion is 15:
        generator = "Visual Studio 15 2017 Win64"
    else:
        print "Visual studio version is not supported"
        return

    cmakeCmd = ["cmake.exe",
                "-G", generator,
                "-S", "..\\",
                "-B", PROJECT_DIR
                ]
    
    subprocess.check_call(cmakeCmd, stderr=subprocess.STDOUT, shell=True)

    config="Debug"        
    cmakeCmd = ["cmake.exe",
                "--build", PROJECT_DIR,
                "--config", config,
                "--target", "install"
                ]
    
    subprocess.check_call(cmakeCmd, stderr=subprocess.STDOUT, shell=True)


CreateDirectory(TEMP_DIR)
CreateDirectory(BIN_DIR)
CreateDirectory(LIB_DIR)
CreateDirectory(INCLUDE_DIR)

InstallGLEW()

RunCMake()

DeleteDirectory(TEMP_DIR)
