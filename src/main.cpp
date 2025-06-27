#include <iostream>
#include <fstream>
#include <string>

#include "include.cpp"

std::string version = "1.0.0 DEV";

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
      int returnValue = cpp(argc, argv);
      return returnValue;
    }
  }
  
  std::cerr << "No language of name " << std::string(argv[1]) << " supported\n";

  return 1;
}
