
 // example class
 #include <iostream>

  using namespace std;
  
  class Cat
  {
    public:
    // acessors
    Cat(int initialAge); // constructor
    ~Cat();              // destructor
    // public functions
    int GetAge() const;  
    void SetAge(int age);
    void Meow() const;
    // private are
    private :
    int itsAge;
    int Weight;
  };
  
