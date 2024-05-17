#include <functional>
#include <lib/application.h>

#include <iostream>
#include <stdexcept>


int main(int argc, char** argv) {
  using namespace task;

  char** const default_arguments = new char*[2];
  default_arguments[0] = "task.exe";
  default_arguments[1] = "test_file.txt";

  try {
    switch (argc) {
    case 1:
      Application::getImplementation().run(2, default_arguments);
      break;
    case 2:
      Application::getImplementation().run(argc, argv);
      break;
    default:
      throw std::runtime_error("invalid arguments count");
    }
    
  } catch (const std::runtime_error& err) {
    std::cout << err.what();
    return 1;
  } catch (const std::exception& err) {
    std::cout << err.what();
    return 1;
  }

  delete[] default_arguments;

  return 0;
}
