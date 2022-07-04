import os


def isSourceFile(filePath):
    filename, file_extension = os.path.splitext(filePath)
    if file_extension == ".cpp" or file_extension == ".c":
        return True
    return False


def getSourceFiles(sourceDir):
    totalFiles = []
    filesInDir = os.listdir(sourceDir)
    for f in filesInDir:
        filePath = os.path.join(sourceDir, f)
        if(os.path.isdir(filePath)):
            files = getSourceFiles(filePath)
            for fl in files:
                totalFiles.append(fl)
        else:
            if(isSourceFile(filePath)):
                totalFiles.append(filePath)
    return totalFiles


def getIncludeDirs(sourceDir):
    totalFiles = []
    filesInDir = os.listdir(sourceDir)
    for f in filesInDir:
        filePath = os.path.join(sourceDir, f)
        if(os.path.isdir(filePath)):
            files = getIncludeDirs(filePath)
            for fl in files:
                totalFiles.append(fl)
            totalFiles.append(filePath)
    return totalFiles


def createBuildScript(lFlags, cFlags, sourceDir):
    file = open('build.ninja', 'w')

    file.write("lflags = " + lFlags + '\n')
    file.write('rule cxx\n')
    file.write('  command = g++ -c $in -o $out ' + cFlags + '\n')
    file.write('rule cc\n')
    file.write('  command = gcc -c $in -o $out $includeFlags\n')
    file.write('rule lnk\n')
    file.write('  command = g++ -o $out $in $lflags\n')

    objDirs = []

    sourceFiles = getSourceFiles(sourceDir)

    for f in sourceFiles:
        none, fileExtension = os.path.splitext(f)
        fileName = os.path.basename(none)

        objDir = "obj/" + fileName + ".o"
        objDirs.append(objDir)
        if fileExtension == ".cpp":
            file.write("build " + objDir + ": cxx " + f + "\n")
        elif fileExtension == ".c":
            file.write("build " + objDir + ": cc " + f + "\n")


    file.write("build out: lnk")
    for oDir in objDirs:
        file.write(" " + oDir)
    file.write("\n")


def main():
    createBuildScript("-framework OpenGL $$(pkg-config --libs glfw3) $$(pkg-config --libs glew)", "-std=c++17 $$(pkg-config --cflags glfw3) $$(pkg-config --cflags glew) $$(pkg-config --cflags glm)", "./src")


main()
