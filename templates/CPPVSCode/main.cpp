#include <cstdio>
#include <iostream>
#include <vector>
#include <string>

using namespace std;


struct Book {
    char name[256];
    int year;
    int pages;
    bool hardcover;
};

struct College {
    char name[256];
};

void print_names(College *colleges, size_t n){
    for(int i=0; i< n; i++){
        printf("%s College \n", colleges[i].name);
    }
}

int main(int argc, char const *argv[]){
    // vector<string> words {"Hello", "C++", "World", "from", "VS Code!"};
    // for(const auto& word : words) {
    //     std::cout << word << std::endl;
    // }



    Book neuromacer{ .pages = 257 };
    //neuromacer.pages = 257;
    printf("Neuromancer has %d pages \n", neuromacer.pages);

    int i = 12;
    int *my_ptr{ &i };

    printf("val of my_ptr is %p \n", my_ptr);

    *my_ptr = 20;
    printf("val of i is %d \n", i);


    College oxford[] = { "Magdalen", "Nuffield", "Kellogg"};
    print_names(oxford, sizeof(oxford)/ sizeof(College));

    return 0;
}

