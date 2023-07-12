#include <iostream>
#include <memory>

using std::unique_ptr;
using std::make_unique;

void changeUniquePtr(unique_ptr<int> &uptr) {
    *uptr = 310;
}

int main() {
    unique_ptr<int> uptr = make_unique<int>(0); 
    
    changeUniquePtr(uptr);
    
    std::cout << "New prt value: " << *uptr << std::endl;
    return 0;
}
