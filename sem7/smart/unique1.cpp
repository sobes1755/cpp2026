#include <iostream>
#include <memory>
#include <cstdio>

int
main()
{

    std::unique_ptr<FILE, int(*)(FILE*)> fptr1(
        std::fopen("hello.txt", "w"), 
        std::fclose
    );

    if (fptr1) {
        std::fprintf(fptr1.get(), "Hello, ");
    }
    
    // std::unique_ptr<FILE, int(*)(FILE*)> fptr2 = fptr1;  // use of deleted function...
    std::unique_ptr<FILE, int(*)(FILE*)> fptr2 = std::move(fptr1);

    if (fptr2) {
        std::fprintf(fptr2.get(), "World!");
    }

    swap(fptr1, fptr2);

    if (fptr1) {
        std::fprintf(fptr1.get(), "\n");
    }

}
