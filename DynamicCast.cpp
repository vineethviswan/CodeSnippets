#include <iostream>
#include <exception>

class Base {
public:
	virtual void print() {
		std::cout << "Base Class\n";
	}
};

class Derived1 : public Base {
	void print() {
		std::cout << "Derived1 Class\n";
	}
};

class Derived2 : public Base {
	void print() {
		std::cout << "Derived2 Class\n";
	}
};

int main() {

	Derived1 d1;
	Base *bp = dynamic_cast<Base*>(&d1);
	bp->print();

	Derived2 d2;
	bp = &d2;
	bp->print();

	Derived2 *d2p = dynamic_cast<Derived2*>(bp);
	if (d2p == nullptr)
		std::cout << "Casting Failed..\n";
	else
		std::cout << "Casting Successfull..\n";

	Derived1 d1ref;
	Base &bref = dynamic_cast<Derived1&>(d1ref);

	try {
		Derived1 d2ref = dynamic_cast<Derived1&>(d1ref);
		std::cout << "Ref. Casting successful..\n";
	}
	catch (std::exception &e) {
		std::cout << e.what() << "\n";
	}
}