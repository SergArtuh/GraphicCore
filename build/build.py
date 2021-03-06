from distutils.spawn import find_executable

import requests, zipfile, io, os, shutil
import re
import subprocess
import sys
import getopt

GLEW_URL = "https://sourceforge.net/projects/glew/files/glew/2.1.0/glew-2.1.0-win32.zip"
GLEW_URL_MIRROR = "https://sourceforge.net/projects/glew/files/glew/2.1.0/glew-2.1.0-win32.zip/download?use_mirror=netcologne"
GLEW_DIR = "glew-2.1.0\\"

GLFW_URL = "https://github.com/glfw/glfw/releases/download/3.3.1/glfw-3.3.1.bin.WIN64.zip"
GLFW_DIR = "glfw-3.3.1.bin.WIN64\\"

TEMP_DIR = "temp\\"

BIN_DIR= "..\\bin\\"
LIB_DIR= "..\\lib\\"
INCLUDE_DIR= "..\\include\\"
PROJECT_DIR= "..\\prj\\"

msvcCompiler = None

buildTests = False;
proxy = None

proxy = None

def DownloadURL(url, dest):
        try:
             if proxy == None:
                     response = requests.get(url)
             else:
                    proxies = { "https": proxy, "http": proxy}
                    response = requests.get(url, proxies=proxies)
                    

        except requests.exceptions.RequestException as e:
            raise Exception( "Fail to download from URL: " + url )

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
            if not DownloadURL(GLEW_URL_MIRROR, TEMP_DIR):
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
        raise Exception( "Please run build.py script in Visual Studio Developer Command Prompt")

    print 'VS version "{ver}"'.format(ver=visualStudioVersion)


    if visualStudioVersion is 16:
        generator = "Visual Studio 16 2019"
    elif visualStudioVersion is 15:
        generator = "Visual Studio 15 2017 Win64"
    else:
        raise Exception( "Visual studio version is not supported" )

    cmakeCmd = ["cmake.exe",
                "-G", generator,
                "-S", "..\\",
                "-B", PROJECT_DIR,
                "-DBUILD_SHARED_LIBS=ON",
                "-DINSTALL_DIR=" + BIN_DIR
                ]
    if buildTests:
            cmakeCmd.append("-DBUILD_TESTS=ON");
    
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

try:
        arguments, values = getopt.getopt(sys.argv[1:],['"ho:v"'], ['tests', 'install-dir=', 'proxy='])
except getopt.GetoptError as err:
        print(err)
        sys.exit(2)
 
for currentArgument, currentValue in arguments:
    if currentArgument == "--proxy":
        proxy = currentValue
    elif currentArgument == "--tests":
        buildTests = True
    elif currentArgument == "--install-dir":
        if currentValue[-1] is not '\\' or not '/':
                BIN_DIR = currentValue + '\\'
        else:
                BIN_DIR = currentValue

try:
        CreateDirectory(TEMP_DIR)
        CreateDirectory(BIN_DIR)
        CreateDirectory(LIB_DIR)
        CreateDirectory(INCLUDE_DIR)

        InstallGLFW()
        InstallGLEW()

        RunCMake()

        DeleteDirectory(TEMP_DIR)

        if buildTests:
                RunExecutable( BIN_DIR + "llr_tests")
except ValueError as err:
        print(err.args)
