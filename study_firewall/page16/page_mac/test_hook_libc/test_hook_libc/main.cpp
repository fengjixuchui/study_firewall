//
//  main.cpp
//  test_hook_libc
//
//  Created by 刘海龙 on 2020/2/11.
//  Copyright © 2020 刘海龙. All rights reserved.
//

#include <iostream>
#include <dlfcn.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, const char * argv[]) {
    // insert code here...
    void* handle = dlopen("/Users/haidragon/study_firewall/page_mac/vapour/libc_hook_open.dylib", RTLD_NOW);
    
    printf("%p",handle);
    int fd, size;
    char s[] = "/Users/haidragon/study_firewall/page_mac/vapour/libc_hook_open.dylib!\n", buffer[500];
    fd = open("/Users/haidragon/study_firewall/page_mac/vapour/test.md", O_WRONLY|O_CREAT);
    write(fd, s, sizeof(s));
    close(fd);
    fd = open("/Users/haidragon/study_firewall/page_mac/vapour/test.md", O_RDONLY);
    size = read(fd, buffer, sizeof(buffer));
    close(fd);
    printf("%s", buffer);
    getchar();
    getchar();
    getchar();
    getchar();
    std::cout << "Hello, World!\n";
    return 0;
}
