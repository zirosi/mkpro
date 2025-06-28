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

    returnValue = newSrcBuild(std::string(argv[2]));

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

  int addMainCpp(std::string srcPath) {
    std::string mainCppPath = srcPath + "/main.cpp";

    std::ofstream mainCppFile(mainCppPath);

    mainCppFile << "#include <iostream>\n\n";
    mainCppFile << "int main() {\n";
    mainCppFile << "  std::cout << \"hello world!\\n\";\n";
    mainCppFile << "  return 0;\n";
    mainCppFile << "}";

    mainCppFile.close();

    return 0;
  }

  int newSrcBuild(std::string projectName) {
    int returnValue = 0;

    std::string srcPath = projectName + "/src";

    int projectMade = makeProjectFolder(projectName);
    int srcMade = makeSrcFolder(projectName);
    int buildMade = makeBuildFolder(projectName);
    int mainMade = addMainCpp(srcPath);

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

};

#endif // !CPP
