#include <iostream>
#include <fstream>
#include <string>

#include "include.cpp"

std::string version = "0.1 DEV";

void help() {
  std::cout << "mkpro version: " << version << std::endl;
}

int main(int argc, char* argv[]) {
  if (argc == 1) {
    help();
    return 0;
  }

  if (argc >= 2) {
    if (std::string(argv[1]) == "cpp") {
      cpp cpp;
      int returnValue = cpp.makeCppProject(argc, argv);
      return returnValue;
    }
  }
  
  std::cerr << "No language of name " << std::string(argv[1]) << " supported\n";

  return 1;
}
