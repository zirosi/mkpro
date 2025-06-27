#ifndef CPP
#define CPP

#include <iostream>
#include <string>
#include <fstream>
#include <filesystem>
#include <set>

int newCppSrcBuild(const std::string projectName) {
  int returnValue = 0;

  std::string srcPath = projectName + "/src";
  std::string mainCppPath = srcPath + "/main.cpp";
  std::string buildPath = projectName + "/build";

  std::filesystem::create_directories(projectName);
  std::filesystem::create_directories(srcPath);
  std::filesystem::create_directories(buildPath);

  std::ofstream mainCppFile(mainCppPath);

  mainCppFile << "#include <iostream>\n\n";
  mainCppFile << "int main() {\n";
  mainCppFile << "  std::cout << \"hello world!\\n\";\n";
  mainCppFile << "  return 0;\n";
  mainCppFile << "}";

  mainCppFile.close();
  
  if (std::filesystem::exists(projectName) == false) {
    std::cerr << "Could not make the project folder\n";
    returnValue = 1;
  }
  if (std::filesystem::exists(srcPath) == false) {
    std::cerr << "Could not make the src folder\n";
    std::filesystem::remove_all(projectName);
    returnValue = 1;
  }
  if (std::filesystem::exists(buildPath) == false) {
    std::cerr << "Could not make the build folder\n";
    std::filesystem::remove_all(projectName);
    returnValue = 1;
  }

  return returnValue;
}

int newCppSrcBuildMake(const std::string projectName) {
  newCppSrcBuild(projectName);
  
  std::string makefilePath = projectName + "/makefile";

  std::ofstream makefileFile(makefilePath);

  makefileFile << "main:\n";
  makefileFile << "  g++ src/main.cpp -o build/main";

  makefileFile.close();
  
  return 0;
}

int checkArgs(std::set<std::string> args, const std::string projectName) {
  const std::set<std::string> SrcBuildMakeArgs = {"--make"};

  if (args == SrcBuildMakeArgs) {
    int returnValue = newCppSrcBuildMake(projectName);
    return returnValue;
  }

  return 1;
}

int cpp(int argc, char* argv[]) {
  int returnValue = 0;
  std::set<std::string> args;

  int projectName_Argc = 2;
  const std::string projectName = std::string(argv[projectName_Argc]);
  
  if (argc == 3) {
    int returnValue = newCppSrcBuild(projectName);
  } else if (argc >= 3) {
    for (int i = 3; i < argc; i++) {
      args.insert(std::string(argv[i]));
    }

    checkArgs(args, projectName);

  } else {
    returnValue = 1;
  }

  return returnValue;
}

#endif // !CPP
