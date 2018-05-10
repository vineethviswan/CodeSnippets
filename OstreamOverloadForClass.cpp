//operator << as member function

#include <iostream>

class Test {
public:
	Test(int val) : mValue(val) {};
	std::ostream& operator<<(std::ostream &os) {
		os << this->mValue << "\n";
		return os;
	}
private:
	int mValue;
};

int main() {
	Test obj(10);
	obj << std::cout; //this why it shouldnt be a member function.
}

//-----------------------------------------------------------------------------------------


//operator << as friend function.
#include <iostream>

class Test {
public:
	Test(int val) : mValue(val) {};
	friend std::ostream& operator<< (std::ostream &os, Test &t);
private:
	int mValue;
};

std::ostream& operator<<(std::ostream &os, Test &t) {
	os << t.mValue << "\n";
	return os;
}

int main() {
	Test obj(10);
	std::cout << obj;
}