#ifndef CPP
#define CPP

#include <iostream>
#include <string>
#include <fstream>
#include <filesystem>
#include <set>

int newCppBuild(const std::string projectName) {
  int returnValue = 0;

  std::string buildPath = projectName + "/build";
  std::string mainCppPath = projectName + "/main.cpp";

  std::filesystem::create_directories(projectName);
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
  if (std::filesystem::exists(buildPath) == false) {
    std::cerr << "Could not make the build folder\n";
    std::filesystem::remove_all(projectName);
    returnValue = 1;
  }

  return returnValue;
}

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

int addMakefile(const std::string projectName, std::string base) {
  std::string mainCppPath;
  int returnValue = 0;

  if ( base == "newCppSrcBuild" ) {
    returnValue = newCppSrcBuild(projectName);
    mainCppPath = "src/main.cpp"; 
  } if ( base == "newCppBuild" ) {
    returnValue = newCppBuild(projectName);
    mainCppPath = "main.cpp"; 
  }

  std::string makefilePath = projectName + "/makefile";

  std::ofstream makefileFile(makefilePath);

  makefileFile << "main:\n";
  makefileFile << "  g++ " << mainCppPath << " -o build/main";

  makefileFile.close();
  
  return returnValue;
}

int addCmakelists(const std::string projectName, std::string base) {
  std::string mainCppPath;
  int returnValue = 0;

  if ( base == "newCppSrcBuild" ) {
    returnValue = newCppSrcBuild(projectName);
    mainCppPath = "src/main.cpp"; 
  } else if ( base == "newCppBuild" )  {
    returnValue = newCppBuild(projectName);
    mainCppPath = "main.cpp";
  }

  std::string cmakelistsPath = projectName + "/CmakeLists.txt";

  std::ofstream cmakelistsFile(cmakelistsPath);

  cmakelistsFile << "cmake_minimum_required (VERSION 3.1)\n\n";
  cmakelistsFile << "project(" << projectName << ")\n\n";
  cmakelistsFile << "add_executable(" << projectName << " " << mainCppPath << ")";

  return returnValue;
}

int checkArgs(std::set<std::string> args, const std::string projectName) {
  const std::set<std::string> SrcBuildMakeArgs = {"--make"};
  const std::set<std::string> SrcBuildCMakeArgs = {"--cmake"};
  const std::set<std::string> BuildArgs = {"--nosrc"};
  const std::set<std::string> BuildMakeArgs = {"--nosrc", "--make"};
  const std::set<std::string> BuildCmakeArgs = {"--nosrc", "--cmake"};

  if (args == BuildArgs) {
    int returnValue = newCppBuild(projectName);
    return returnValue;
  } if ( args == BuildMakeArgs ) {
    int returnValue = addMakefile(projectName, "newCppBuild");
    return returnValue;
  } if ( args == BuildCmakeArgs ) {
    int returnValue = addCmakelists(projectName, "newCppBuild");
    return returnValue;
  } if (args == SrcBuildMakeArgs) {
    int returnValue = addMakefile(projectName, "newCppSrcBuild");
    return returnValue;
  } if (args == SrcBuildCMakeArgs) {
    int returnValue = addCmakelists(projectName, "newCppSrcBuild");
    return returnValue;
  } else {
    std::cerr << "Incorrect argument(s)\n";
    return 1;
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

    int returnValue = checkArgs(args, projectName);

  } else {
    returnValue = 1;
  }

  return returnValue;
}

#endif // !CPP
