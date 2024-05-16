// sandbox.cpp: define el punto de entrada de la aplicación.
//

#include <iostream>

int main() {
     auto i = 0;
     auto j = 0;
     std::cout << "postfix: " << 2 * i++ << " new value of i: " << i << std::endl;
     std::cout << "prefix: " << 2 * ++j << " new value of j: " << j <<  std::endl;
     return 0;
}
