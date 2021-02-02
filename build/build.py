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

PNG_URL = "https://sourceforge.net/projects/libpng/files/libpng16/1.6.37/lpng1637.zip"
PNG_DIR = "lpng1637\\"


Z_URL = "https://sourceforge.net/projects/libpng/files/zlib/1.2.11/zlib1211.zip"
Z_DIR = "zlib-1.2.11\\"



PWD_DIR = os.getcwd() + "\\"
TEMP_DIR = PWD_DIR + "temp\\"

ROOT_DIR = PWD_DIR + "..\\"

BIN_DIR= ROOT_DIR + "bin\\"
LIB_DIR= ROOT_DIR + "lib\\"
INCLUDE_DIR= ROOT_DIR + "include\\"
PROJECT_DIR= ROOT_DIR + "prj\\"

msvcCompiler = None


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

def InstallZ():
        if not os.path.exists(TEMP_DIR + Z_DIR):
            if not DownloadURL(Z_URL, TEMP_DIR):
                return
        zPathRoot = TEMP_DIR + Z_DIR
        
        RunCMake(zPathRoot)
        CopyFile(zPathRoot + "bin\\bin\\zlibd1.dll", BIN_DIR)
        CopyFile(zPathRoot + "bin\\lib\\zlibd.lib", LIB_DIR)
        CopyDirectory(zPathRoot + "bin\\include\\", INCLUDE_DIR + "zlib\\")
        return True


def InstallPNG():
       
        zRes = InstallZ();
        
        if zRes and not os.path.exists(TEMP_DIR + PNG_DIR):
            if not DownloadURL(PNG_URL, TEMP_DIR):
                return
        
        pngPathRoot = TEMP_DIR + PNG_DIR
        zRootPath =  TEMP_DIR + Z_DIR
        RunCMake(pngPathRoot, options=["-DZLIB_INCLUDE_DIR=" + INCLUDE_DIR + "zlib\\"
                                       , "-DZLIB_LIBRARY=" + LIB_DIR + "zlibd.lib"
                                       , "-DCMAKE_BUILD_TYPE=Debug"])

        CopyFile(pngPathRoot + "bin\\bin\\libpng16d.dll", BIN_DIR)
        CopyFile(pngPathRoot + "bin\\lib\\libpng16d.lib", LIB_DIR)
        CopyDirectory(pngPathRoot + "bin\\include\\", INCLUDE_DIR + "png\\")




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

def RunCMake(sourcePath = "", installDir = "", prjPath = "", options = None, buildTests = False):
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

    if not sourcePath:
        sourcePath = ".\\"

    if not prjPath:
        prjPath = sourcePath + "prj\\"

    if not installDir:
        installDir = sourcePath + "bin\\"   

    cmakeCmd = ["cmake.exe",
                "-G", generator,
                "-S", sourcePath,
                "-B", prjPath,
                "-DBUILD_SHARED_LIBS=ON",
                "-DCMAKE_INSTALL_PREFIX=" + installDir
                ]
    if buildTests:
        cmakeCmd.append("-DBUILD_TESTS=ON");

    if options is not None:
        cmakeCmd = cmakeCmd + options

    subprocess.check_call(cmakeCmd, stderr=subprocess.STDOUT, shell=True)

    config="Debug"        
    cmakeCmd = ["cmake.exe",
                "--build", prjPath,
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

installPath = "";
isBuildTests = False;
proxy = None
 
for currentArgument, currentValue in arguments:
    if currentArgument == "--proxy":
        proxy = currentValue
    elif currentArgument == "--tests":
        isBuildTests = True
    elif currentArgument == "--install-dir":
        if currentValue[-1] is not '\\' or not '/':
                BIN_DIR = currentValue + '\\'
        else:
                BIN_DIR = currentValue
        installPath = BIN_DIR

try:
        CreateDirectory(TEMP_DIR)
        CreateDirectory(BIN_DIR)
        CreateDirectory(LIB_DIR)
        CreateDirectory(INCLUDE_DIR)


        InstallPNG()


        InstallGLFW()
        InstallGLEW()

        

        RunCMake(ROOT_DIR, installDir = installPath, buildTests = isBuildTests)

        DeleteDirectory(TEMP_DIR)

        if isBuildTests:
                RunExecutable( BIN_DIR + "tests")
except ValueError as err:
        print(err.args)
