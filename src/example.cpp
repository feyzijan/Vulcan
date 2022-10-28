
 // cat class -------------------------
#include <iostream>
 #include "example.h"
  // acessors
  // constructor
  Cat::Cat(int initAge)
  {
   itsAge = initAge; 
  }
  // destructor takes no action
  Cat:: ~Cat()
  { 
  }
  int Cat::GetAge() const
  {
    return itsAge;
  }
  void Cat::SetAge(int Age)
  {
    itsAge = Age;
  }
  void Cat::Meow() const
  {
   std::cout << "  Meow ... \n"; 
  }
  
