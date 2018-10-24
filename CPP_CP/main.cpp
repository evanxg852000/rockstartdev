#include <iostream>

#include "core.hpp"

using namespace std;

void print(const int& i){
	cout<< i<< endl;
}

int main(int argc, char const *argv[]){
	int i=12;
	const int& refi = i;

	//refi= 24;

	print()

	cout << refi<< endl;


    cout << add(2,3) << endl; 
    return 0;
}

