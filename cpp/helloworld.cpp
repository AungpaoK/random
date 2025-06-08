#include <iostream>
#include <cstring>

int argumentsProcessing (int argc, char *argv[]) {
  int i;
  for (i = 0; i < argc; i++){
    std::cout << "Position [" << i << "] Value: " << argv[i] << "\n";
  };

  int sum = 0;
  int num;
  for (i = 1; i < argc; i++){
    std::size_t pos{};
    try {
      num = std::stoi(argv[i], &pos);
      if (pos != std::strlen(argv[i])){
        std::cerr << "Input skipped at index [" << i << "] Reason: letter detected(\"" << argv[i] << "\") \n";
        continue;
      }
      sum = sum + num;
    }
    catch (const std::invalid_argument& e){
      std::cerr << "Invalid input at index [" << i << "]\n";
    }
  };
  return sum;
}

int main (int argc, char *argv[]){

  int sum = argumentsProcessing(argc, argv);
  std::cout << "Sum: " << sum << "\n";

  return 0;

}
