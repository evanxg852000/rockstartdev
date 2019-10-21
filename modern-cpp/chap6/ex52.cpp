void print_permutations(std::string str){
    std::sort(str.begin(), str.end());
    do{
        std::cout<< str << std::endl;
    } while(std::next_permutation(str.begin(), str.end()));
}

void next_permutation(std::string str, std::string perm){
    if(str.empty())
        std::cout<< perm << std::endl;
    else {
        for(size_t i=0; i < str.size(); i++) {
            next_permutation(str.substr(1), perm + str[0]);
            std::rotate(str.begin(), str.begin()+ 1, str.end());
        }
    }
}

void print_permutations_recursive(std::string str){
    next_permutation(str, "");
}


int main(int argc, char const *argv[]){
    std::cout << "non-recursive version" << std::endl;
    print_permutations("main");

    std::cout << "recursive version" << std::endl;
    print_permutations_recursive("main");

    return 0;
}
