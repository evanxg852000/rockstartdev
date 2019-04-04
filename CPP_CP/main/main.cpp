#include <iostream>

#include "core.hpp"

using namespace std;

void print(const int& i){
	cout<< i<< endl;
}

int main(int argc, char const *argv[]){
	int i=12;
	const int& refi = i;

	print(refi);

	cout << refi<< endl;

    cout << add(2,3) << endl; 
    return 0;
}


// ======== Crow Exemple ==========

// #include "vendor/crow.hpp"

// using namespace std;

// int main(int argc, char* argv[]) {
//   crow::SimpleApp app;

//   CROW_ROUTE(app, "/")
//     ([](){
//       return "<div><h1>Hello, Crow.</h1></div>";
//     });

//   char* port = getenv("PORT");
//   uint16_t iPort = static_cast<uint16_t>(port != nullptr? stoi(port): 18080);
//   cout << "PORT = " << iPort << "\n";
//   app.port(iPort).multithreaded().run();
// }