#ifndef CPP
#define CPP

#include <iostream>
#include <string>
#include <fstream>
#include <filesystem>
#include <set>

class cpp {
public:
  int makeCppProject(int argc, char** argv) {
    int returnValue = 0;
    std::set<std::string> args;

    for (int i = 3; i < argc; i++) {
      args.insert(std::string(argv[i]));
    }
  
    if (argc <= 3) {
      returnValue = newSrcBuild(std::string(argv[2]));
    } if (argc > 3) {
      checkArgs(args, std::string(argv[2]));
    }

    return returnValue;
  }

private:
  int checkExsist(std::string folder) {
    int returnValue = 0;

    if (std::filesystem::exists(folder) == false) {
      returnValue = 1;
    }

    return returnValue;
  }

  int checkExsist(std::string folder, std::string message) {
    int returnValue = 0;

    if (std::filesystem::exists(folder) == false) {
      std::cerr << message << std::endl;
      returnValue = 1;
    }

    return returnValue;
  }

  int makeProjectFolder(std::string projectName) {
    int returnValue = 0;

    std::filesystem::create_directories(projectName);

    returnValue = checkExsist(projectName, "Could not create the project folder");

    return returnValue;
  }
  
  int makeSrcFolder(std::string projectName) {
    int returnValue = 0;

    if (checkExsist(projectName) == 1) {
      std::cerr << "Could not make the src folder because there is no project folder\n";
      return 1;
    }
     
    std::string srcPath = projectName + "/src";
    std::filesystem::create_directories(srcPath);
    returnValue = checkExsist(srcPath, "Could not make the src folder");

    return returnValue;
  }

  int makeBuildFolder(std::string projectName) {
    int returnValue = 0;

    if (checkExsist(projectName) == 1) {
      std::cerr << "Could not make the build folder becuase there is no project folder\n";
      return 1;
    }

    std::string buildPath = projectName + "/build";
    std::filesystem::create_directories(buildPath);
    returnValue = checkExsist(buildPath, "Could not make the build folder");

    return returnValue;
  }

  int addMainCpp(std::string mainCppPath) {
    int returnValue = 0;

    std::ofstream mainCppFile(mainCppPath);

    mainCppFile << "#include <iostream>\n\n";
    mainCppFile << "int main() {\n";
    mainCppFile << "  std::cout << \"hello world!\\n\";\n";
    mainCppFile << "  return 0;\n";
    mainCppFile << "}";

    mainCppFile.close();

    if (checkExsist(mainCppPath) == 1) {
      returnValue = 1;
    }

    return returnValue;
  }

  int addMakefile(std::string projectName, std::string mainCppPath, std::string buildPath) {
    int returnValue = 0;

    std::string makefilePath = projectName + "/makefile";

    std::ofstream makefileFile(makefilePath);

    makefileFile << "main:\n";
    makefileFile << "  g++ " << mainCppPath << " -o " << buildPath;
  
    makefileFile.close();

    returnValue = checkExsist(makefilePath);

    return returnValue;
  }

  int addCmakelists(std::string projectName, std::string mainCppPath, std::string buildPath) {
    int returnValue = 0;

    std::string cmakelistsPath = projectName + "/CmakeLists.txt";

    std::ofstream cmakelistsFile(cmakelistsPath);

    cmakelistsFile << "cmake_minimum_required(VERSION 3.15)\n\n";
    cmakelistsFile << "project( " << projectName << " )\n\n";
    cmakelistsFile << "add_executable( " << projectName << " " << mainCppPath << " )";

    cmakelistsFile.close();

    returnValue = checkExsist(cmakelistsPath);

    return returnValue;
  }

  int newSrcBuild(std::string projectName) {
    int returnValue = 0;

    std::string mainCppPath = projectName + "/src/main.cpp"; 

    int projectMade = makeProjectFolder(projectName);
    int srcMade = makeSrcFolder(projectName);
    int buildMade = makeBuildFolder(projectName);
    int mainMade = addMainCpp(mainCppPath);

    if (projectMade == 1) {
      returnValue = 1;
    }
    if (srcMade == 1) {
      returnValue = 1;
    }
    if (buildMade == 1) {
      returnValue = 1;
    }

    return returnValue;
  }
  
  int checkArgs(std::set<std::string> args, std::string projectName) {
    int returnValue = 0;

    std::set<std::string> SrcBuildMakeArgs = {"--make"};
    std::set<std::string> SrcBuildCmakeArgs = {"--cmake"};

    if (args == SrcBuildMakeArgs) {
      if (newSrcBuild(projectName) == addMakefile(projectName, "src/main.cpp", "build/main.out") && newSrcBuild(projectName) == 0) {
        returnValue = 0;
      }
    }
    if (args == SrcBuildCmakeArgs) {
      if (newSrcBuild(projectName) == addCmakelists(projectName, "src/main.cpp", "build/main.out") && newSrcBuild(projectName) == 0) {
        returnValue = 0;
      }
    }

    return returnValue;
  }
};

#endif // !CPP
