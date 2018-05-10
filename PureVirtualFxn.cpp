//pure virtual destructor

#include <iostream>
#include <string>

class Account {
public:
	Account(){
		std::cout << "Account - Constructor ()\n";
		std::cout << balance() << std::endl;
		print();
	}
	virtual ~Account() = 0;
	virtual long balance() { return 0L; }
	virtual void print() = 0; 
};


Account::~Account() {
	std::cout << "Account - Destructor ()\n";
}

void Account::print() {
	std::cout << "Account - print ()\n";
}

class Savings : public Account {
public:
	Savings() {
		std::cout << "Savings - Constructor ()\n";
	}
	~Savings() {
		std::cout << "Savings - Destructor ()\n";
	}
	void print() {
		std::cout << "Savings - print ()\n";
	}
};

int main() {
	{
		Savings savings;
		Account &accRef = savings;
		accRef.print();
	}
}