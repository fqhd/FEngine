import os

def isSourceFile(filePath):
	filename, file_extension = os.path.splitext(filePath)
	if file_extension == ".cpp" or file_extension == ".c" or file_extension == ".m":
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


def createBuildScript(lFlags, cFlags, sourceDir):
    file = open('build.ninja', 'w')
    file.write("cflags = " + cFlags + '\n')
    file.write("lflags = " + lFlags + '\n')
    file.write('rule cxx\n')
    file.write('  command = g++ -c $in -o $out $cflags\n')
    file.write('rule lnk\n')
    file.write('  command = g++ -o $out $in $lflags\n')

    objDirs = []

    sourceFiles = getSourceFiles("./src")

    for f in sourceFiles:
        fileName = os.path.basename(f)
        objDir = "obj/" + fileName[:-4] + ".o"
        objDirs.append(objDir)
        file.write("build " + objDir + ": cxx " + f + "\n")

    file.write("build out: lnk")
    for oDir in objDirs:
        file.write(" " + oDir)
    file.write("\n")


def main():
    createBuildScript("-framework OpenGL", "-std=c++17", "./src")

main()
