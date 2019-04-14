#include <algorithm>
#include <iostream>
#include <string>
#include  <cmath>

bool isAnagram(std::string str1, std::string str2){
	if(str1.size() != str2.size())
		return false;

	std::transform(str1.begin(), str1.end(), str1.begin(), ::toupper);
	std::transform(str2.begin(), str2.end(), str2.begin(), ::toupper);

	std::remove_if(str1.begin(), str1.end(), ::isspace);
	std::remove_if(str2.begin(), str2.end(), ::isspace);

	std::sort(str1.begin(), str1.end());
	std::sort(str2.begin(), str2.end());

	return str1 == str2;
}

bool isPalindrome(std::string str){
	std::transform(str.begin(), str.end(), str.begin(), ::tolower);
	std::string str2{str};
	std::reverse(str2.begin(), str2.end());
	return str == str2;
}

std::string decimalToBinary(int num){
	std::string r = "";
	do{
		r.push_back('0'+num%2);
		num = num / 2;
	} while(num);
	std::reverse(r.begin(), r.end());
	return r;
}

//convert char c to digit int: c - '0'
//convert digit int d to char: '0' + d
int binaryToDecimal(std::string num){
	int r = 0;
	std::reverse(num.begin(), num.end());
	for(int i=0; i<num.size(); i++){
		r += (num.at(i) - '0') * std::pow(2, i);
	}
	return r;
}

