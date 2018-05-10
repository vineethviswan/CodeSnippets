#include <iostream>
#include <memory>
#include <string>

class Connection
{
public:
	Connection(const std::string &conn) {
		mConnectionName = conn;
		std::cout << "Constructor..\n";
	}
	~Connection() {
		std::cout << "Destructor..\n";
	}
	std::string getConnection() { return mConnectionName; }
private:
	std::string mConnectionName;
};

void print(std::shared_ptr<Connection> ptr) {
	std::cout << ptr->getConnection() << "\n";
	std::cout << ptr.use_count() << "\n";
}

int main() {

	{
		std::shared_ptr<Connection> conn = std::make_shared<Connection>("One");
		std::cout << conn.use_count() << "\n";

		std::shared_ptr<Connection> conn2(conn);
		std::cout << conn.use_count() << "\n";

		std::weak_ptr<Connection> weakConn = conn;
		std::cout << conn.use_count() << "\n";

		std::cout << "After Passing to Fn\n";
		print(conn);
		std::cout << conn.use_count() << "\n";
	}

}