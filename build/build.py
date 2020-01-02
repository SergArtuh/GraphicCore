from distutils.spawn import find_executable

import requests, zipfile, io, os, shutil
import re
import subprocess

GLEW_URL = "https://sourceforge.net/projects/glew/files/glew/2.1.0/glew-2.1.0-win32.zip"
GLEW_DIR = "glew-2.1.0\\"

GLFW_URL = "https://github.com/glfw/glfw/releases/download/3.3.1/glfw-3.3.1.bin.WIN64.zip"
GLFW_DIR = "glfw-3.3.1.bin.WIN64\\"

TEMP_DIR = "temp\\"

BIN_DIR= "..\\bin\\"
LIB_DIR= "..\\lib\\"
INCLUDE_DIR= "..\\include\\"
PROJECT_DIR= "..\\prj\\"

msvcCompiler = None

def DownloadURL(url, dest):
        try:
             response = requests.get(url)

        except requests.exceptions.RequestException as e:
            print "Fail to download from URL: " + url
            return False

        zip = zipfile.ZipFile(io.BytesIO(response.content))
        dirName = zip.namelist()[0]
        zip.extractall(dest)
        return True


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

def InstallGLEW():
        if not os.path.exists(TEMP_DIR + GLEW_DIR):
            if not DownloadURL(GLEW_URL, TEMP_DIR):
                return

            CopyFile(TEMP_DIR + GLEW_DIR + "bin\\Release\\x64\\glew32.dll", BIN_DIR)
            CopyFile(TEMP_DIR + GLEW_DIR + "lib\\Release\\x64\\glew32.lib", LIB_DIR)
            CopyDirectory(TEMP_DIR + GLEW_DIR + "include\\GL", INCLUDE_DIR + "GL")


def InstallGLFW():
        if not os.path.exists(TEMP_DIR + GLFW_DIR):
            if not DownloadURL(GLFW_URL, TEMP_DIR):
                return

            CopyFile(TEMP_DIR + GLFW_DIR + "lib-vc2019\\glfw3.dll", BIN_DIR)
            CopyFile(TEMP_DIR + GLFW_DIR + "lib-vc2019\\glfw3dll.lib", LIB_DIR)
            CopyDirectory(TEMP_DIR + GLFW_DIR + "include\\GLFW", INCLUDE_DIR + "GLFW")

def GetVisualStudioVersion():
    global msvcCompiler
    if msvcCompiler is None:
            msvcExe = find_executable('cl')
            if msvcExe:
                match = re.search(
                    "(\d+).(\d+)", 
                    os.environ.get("VisualStudioVersion", ""))
                if match:
                    msvcCompiler = int(match.groups()[0])
    return msvcCompiler

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
                "-B", PROJECT_DIR,
                "-DBUILD_SHARED_LIBS=ON"
                ]
    
    subprocess.check_call(cmakeCmd, stderr=subprocess.STDOUT, shell=True)

    config="Debug"        
    cmakeCmd = ["cmake.exe",
                "--build", PROJECT_DIR,
                "--config", config,
                "--target", "install"
                ]
    
    subprocess.check_call(cmakeCmd, stderr=subprocess.STDOUT, shell=True)

def RunExecutable(cmd):
    subprocess.check_call(cmd, stderr=subprocess.STDOUT, shell=True)

CreateDirectory(TEMP_DIR)
CreateDirectory(BIN_DIR)
CreateDirectory(LIB_DIR)
CreateDirectory(INCLUDE_DIR)

InstallGLFW()
InstallGLEW()

RunCMake()

DeleteDirectory(TEMP_DIR)

RunExecutable( BIN_DIR + "llr_tests")
