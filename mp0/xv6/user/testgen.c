#include "kernel/types.h"

#include "kernel/fcntl.h"
#include "kernel/stat.h"
#include "user/user.h"
void mkfile(char *filename) {
    int fd = open(filename, O_CREATE | O_RDWR);
    write(fd, "hi", 3);
    close(fd);
}

void mkd(char *dirname) {
    if (mkdir(dirname) < 0) {
        fprintf(2, "mkdir %s failed.", dirname);
        exit(1);
    }
}

/*
    Test Suite 0
*/
void test0() {
    mkd("os2023");

    mkd("os2023/d1");
    mkd("os2023/d2");
    mkd("os2023/d3");

    mkd("os2023/d2/a");
    mkd("os2023/d2/b");
    mkfile("os2023/d2/c");

    mkd("os2023/d3/a");
    mkfile("os2023/d3/b");
}

void test1() {
    mkd("a");
    mkd("a/0");
    mkd("a/1");
    mkd("a/2");
    mkd("a/3");
    mkd("a/4");
    mkd("a/5");
    mkd("a/6");
    mkd("a/7");
    mkd("a/8");
    mkd("a/9");
    mkd("a/10");
}

// Custom testcases shared by classmate Lin from https://ideone.com/6QzEhw
void test2() {
    mkd("b");
    mkd("b/a");
    mkd("b/a/a");
    mkd("b/a/a/aa");
    mkd("b/a/a/aa/a");
    mkfile("b/a/a/aa/p");
    mkd("b/a/a/aa/b");
    mkfile("b/a/a/aa/c");
    mkd("b/a/a/aa/d");
    mkfile("b/a/a/aa/e");
    mkd("b/a/a/aa/f");
    mkfile("b/a/a/aa/g");
    mkd("b/a/a/aa/h");
    mkfile("b/a/a/aa/i");
    mkd("b/a/a/aa/j");
    mkfile("b/a/a/aa/k");
    mkd("b/a/a/aa/l");
    mkfile("b/a/a/aa/m");
    mkd("b/a/a/aa/n");
    mkfile("b/a/a/aa/o");
    mkd("b/a/a/aa/q");
}

void test3() {
    mkd("c");
    mkd("c/a");
    mkd("c/a/a");
    mkd("c/a/a/a");
    mkd("c/a/a/a/a");
    mkfile("c/a/a/a/p");
    mkd("c/a/a/a/b");
    mkfile("c/a/a/a/c");
    mkd("c/a/a/a/d");
    mkfile("c/a/a/a/e");
    mkd("c/a/a/a/f");
    mkfile("c/a/a/a/g");
    mkd("c/a/a/a/h");
    mkfile("c/a/a/a/i");
    mkd("c/a/a/a/j");
    mkfile("c/a/a/a/k");
    mkd("c/a/a/a/l");
    mkfile("c/a/a/a/m");
    mkd("c/a/a/a/n");
    mkfile("c/a/a/a/o");
    mkd("c/a/a/a/q");
}

void test4() {
    mkd("d");
    mkfile("d/a");
    mkfile("d/b");
    mkfile("d/c");
    mkd("d/d");
    mkfile("d/e");
    mkfile("d/f");
    mkfile("d/g");
    mkfile("d/h");
    mkfile("d/i");
    mkfile("d/j");
    mkfile("d/k");
    mkfile("d/l");
    mkfile("d/m");
    mkfile("d/n");
    mkfile("d/o");
    mkd("d/d/d");
    mkd("d/d/a");
    mkd("d/d/c");
    mkfile("d/ddd");
    mkd("d/azs");
}
 
void test5() {
    mkd("e");
    mkfile("e/aaddssa");
    mkfile("e/aaddssb");
    mkfile("e/aaddssc");
    mkfile("e/aaddssd");
    mkfile("e/aaddsse");
    mkfile("e/aaddssf");
    mkfile("e/aaddssg");
    mkfile("e/aaddssh");
    mkfile("e/aaddssi");
    mkfile("e/aaddssj");
    mkfile("e/aaddssk");
    mkfile("e/aaddssl");
    mkfile("e/aaddssm");
    mkfile("e/aaddssn");
    mkfile("e/aaddsso");
    mkfile("e/aaddssp");
    mkfile("e/aaddssq");
    mkfile("e/aaddssr");
    mkfile("e/aaddsss");
    mkfile("e/aaddsst");
}

void test6() {
    mkd("e1");
    mkfile("e1/aaddssa");
    mkfile("e1/aaddssb");
    mkfile("e1/aaddssc");
    mkfile("e1/aaddssd");
    mkfile("e1/aaddsse");
    mkfile("e1/aaddssf");
    mkfile("e1/aaddssg");
    mkfile("e1/aaddssh");
    mkfile("e1/aaddssi");
    mkfile("e1/aaddssj");
    mkfile("e1/aaddssk");
    mkfile("e1/aaddssl");
    mkfile("e1/aaddssm");
    mkfile("e1/aaddssn");
    mkfile("e1/aaddsso");
    mkfile("e1/aaddssp");
    mkfile("e1/aaddssq");
    mkfile("e1/aaddssr");
    mkfile("e1/aaddsss");
    mkfile("e1/aaddsst");
}

void test7() {
    mkd("1");
    mkd("1/aaddssa");
    mkd("1/aaddssb");
    mkd("1/aaddssc");
    mkd("1/aaddssd");
    mkd("1/aaddsse");
    mkd("1/aaddssf");
    mkd("1/aaddssg");
    mkd("1/aaddssh");
    mkd("1/aaddssi");
    mkd("1/aaddssj");
    mkd("1/aaddssk");
    mkd("1/aaddssl");
    mkd("1/aaddssm");
    mkd("1/aaddssn");
    mkd("1/aaddsso");
    mkd("1/aaddssp");
    mkd("1/aaddssq");
    mkd("1/aaddssr");
    mkd("1/aaddsss");
    mkd("1/aaddsst");
}

/*
    Test Suite 1
*/
void test8() {
    mkd("12");
    mkd("12/aaddssa");
    mkd("12/aaddssb");
    mkd("12/aaddssc");
    mkd("12/aaddssd");
    mkd("12/aaddsse");
    mkd("12/aaddssf");
    mkd("12/aaddssg");
    mkd("12/aaddssh");
    mkd("12/aaddssi");
    mkd("12/aaddssj");
    mkd("12/aaddssk");
    mkd("12/aaddssl");
    mkd("12/aaddssm");
    mkd("12/aaddssn");
    mkd("12/aaddsso");
    mkd("12/aaddssp");
    mkd("12/aaddssq");
    mkd("12/aaddssr");
    mkd("12/aaddsss");
    mkd("12/aaddsst");
}

void test9() {
    mkd("12345678");
    mkd("12345678/1");
    mkd("12345678/2");
    mkd("12345678/3");
    mkd("12345678/4");
    mkd("12345678/5");
    mkd("12345678/6");
    mkd("12345678/7");
    mkd("12345678/8");
    mkd("12345678/9");
    mkd("12345678/a");
    mkd("12345678/c");
    mkd("12345678/b");
    mkd("12345678/d");
    mkd("12345678/e");
    mkd("12345678/f");
    mkd("12345678/h");
    mkd("12345678/g");
    mkd("12345678/i");
    mkd("12345678/k");
    mkd("12345678/j");
}
 
void test10() {
    mkd("gggggggg");
    mkfile("gggggggg/g");
    mkfile("gggggggg/a");
    mkfile("gggggggg/b");
    mkfile("gggggggg/c");
    mkfile("gggggggg/1");
    mkfile("gggggggg/3");
    mkfile("gggggggg/5");
    mkfile("gggggggg/7");
    mkfile("gggggggg/9");
    mkfile("gggggggg/2");
    mkfile("gggggggg/4");
    mkfile("gggggggg/6");
    mkfile("gggggggg/8");
    mkfile("gggggggg/k");
    mkfile("gggggggg/j");
    mkfile("gggggggg/h");
    mkfile("gggggggg/e");
    mkfile("gggggggg/f");
    mkfile("gggggggg/z");
    mkfile("gggggggg/w");
}

void test11() {
    mkd("aaaaaaaaaa");
    mkd("aaaaaaaaaa/aaaaaaaaaa");
    mkd("aaaaaaaaaa/aaaaaaaaaa/aaaaaaaaaa");
    mkd("aaaaaaaaaa/aaaaaaaaaa/aaaaaaaaaa/aaaaaaaaaa");
    mkd("aaaaaaaaaa/aaaaaaaaaa/aaaaaaaaaa/aaaaaaaaaa/aaaaaaaaaa");
    mkd("aaaaaaaaaa/aaaaaaaaaa/aaaaaaaaaa/aaaaaaaaaa/aaaaaaaaab");
    mkd("aaaaaaaaaa/aaaaaaaaaa/aaaaaaaaaa/aaaaaaaaaa/aaaaaaaaac");
    mkd("aaaaaaaaaa/aaaaaaaaaa/aaaaaaaaaa/aaaaaaaaaa/aaaaaaaaad");
    mkd("aaaaaaaaaa/aaaaaaaaaa/aaaaaaaaaa/aaaaaaaaaa/aaaaaaaaae");
    mkd("aaaaaaaaaa/aaaaaaaaaa/aaaaaaaaaa/aaaaaaaaaa/aaaaaaaaaf");
    mkd("aaaaaaaaaa/aaaaaaaaaa/aaaaaaaaaa/aaaaaaaaaa/aaaaaaaaag");
    mkd("aaaaaaaaaa/aaaaaaaaaa/aaaaaaaaaa/aaaaaaaaaa/aaaaaaaaah");
    mkd("aaaaaaaaaa/aaaaaaaaaa/aaaaaaaaaa/aaaaaaaaaa/aaaaaaaaai");
    mkd("aaaaaaaaaa/aaaaaaaaaa/aaaaaaaaaa/aaaaaaaaaa/aaaaaaaaaj");
    mkd("aaaaaaaaaa/aaaaaaaaaa/aaaaaaaaaa/aaaaaaaaaa/aaaaaaaaak");
    mkd("aaaaaaaaaa/aaaaaaaaaa/aaaaaaaaaa/aaaaaaaaaa/aaaaaaaaal");
    mkd("aaaaaaaaaa/aaaaaaaaaa/aaaaaaaaaa/aaaaaaaaaa/aaaaaaaaam");
    mkd("aaaaaaaaaa/aaaaaaaaaa/aaaaaaaaaa/aaaaaaaaaa/aaaaaaaaan");
    mkd("aaaaaaaaaa/aaaaaaaaaa/aaaaaaaaaa/aaaaaaaaaa/aaaaaaaaao");
    mkd("aaaaaaaaaa/aaaaaaaaaa/aaaaaaaaaa/aaaaaaaaaa/aaaaaaaaap");
    mkd("aaaaaaaaaa/aaaaaaaaaa/aaaaaaaaaa/aaaaaaaaaa/aaaaaaaaaq");
}
 
void test12() {
    mkd("1aaaaaaaaa");
    mkd("1aaaaaaaaa/aaaaaaaaaa");
    mkd("1aaaaaaaaa/aaaaaaaaaa/aaaaaaaaaa");
    mkd("1aaaaaaaaa/aaaaaaaaaa/aaaaaaaaaa/aaaaaaaaaa");
    mkfile("1aaaaaaaaa/aaaaaaaaaa/aaaaaaaaaa/aaaaaaaaaa/aaaaaaaaaa");
    mkfile("1aaaaaaaaa/aaaaaaaaaa/aaaaaaaaaa/aaaaaaaaaa/aaaaaaaaab");
    mkfile("1aaaaaaaaa/aaaaaaaaaa/aaaaaaaaaa/aaaaaaaaaa/aaaaaaaaac");
    mkfile("1aaaaaaaaa/aaaaaaaaaa/aaaaaaaaaa/aaaaaaaaaa/aaaaaaaaad");
    mkfile("1aaaaaaaaa/aaaaaaaaaa/aaaaaaaaaa/aaaaaaaaaa/aaaaaaaaae");
    mkfile("1aaaaaaaaa/aaaaaaaaaa/aaaaaaaaaa/aaaaaaaaaa/aaaaaaaaaf");
    mkfile("1aaaaaaaaa/aaaaaaaaaa/aaaaaaaaaa/aaaaaaaaaa/aaaaaaaaag");
    mkfile("1aaaaaaaaa/aaaaaaaaaa/aaaaaaaaaa/aaaaaaaaaa/aaaaaaaaah");
    mkfile("1aaaaaaaaa/aaaaaaaaaa/aaaaaaaaaa/aaaaaaaaaa/aaaaaaaaai");
    mkfile("1aaaaaaaaa/aaaaaaaaaa/aaaaaaaaaa/aaaaaaaaaa/aaaaaaaaaj");
    mkfile("1aaaaaaaaa/aaaaaaaaaa/aaaaaaaaaa/aaaaaaaaaa/aaaaaaaaak");
    mkfile("1aaaaaaaaa/aaaaaaaaaa/aaaaaaaaaa/aaaaaaaaaa/aaaaaaaaal");
    mkfile("1aaaaaaaaa/aaaaaaaaaa/aaaaaaaaaa/aaaaaaaaaa/aaaaaaaaam");
    mkfile("1aaaaaaaaa/aaaaaaaaaa/aaaaaaaaaa/aaaaaaaaaa/aaaaaaaaan");
    mkfile("1aaaaaaaaa/aaaaaaaaaa/aaaaaaaaaa/aaaaaaaaaa/aaaaaaaaao");
    mkfile("1aaaaaaaaa/aaaaaaaaaa/aaaaaaaaaa/aaaaaaaaaa/aaaaaaaaap");
    mkfile("1aaaaaaaaa/aaaaaaaaaa/aaaaaaaaaa/aaaaaaaaaa/aaaaaaaaaq");
}
 
void test13() {
    mkd("2");
    mkd("2/aaaaaaaaaa");
    mkd("2/aaaaaaaaaa/aaaaaaaaaa");
    mkd("2/aaaaaaaaaa/aaaaaaaaaa/aaaaaaaaaa");
    mkd("2/aaaaaaaaaa/aaaaaaaaaa/aaaaaaaaaa/aaaaaaaaaa");
    mkd("2/aaaaaaaaaa/aaaaaaaaaa/aaaaaaaaaa/aaaaaaaaab");
    mkd("2/aaaaaaaaaa/aaaaaaaaaa/aaaaaaaaaa/aaaaaaaaac");
    mkd("2/aaaaaaaaaa/aaaaaaaaaa/aaaaaaaaaa/aaaaaaaaad");
    mkd("2/aaaaaaaaaa/aaaaaaaaaa/aaaaaaaaaa/aaaaaaaaae");
    mkd("2/aaaaaaaaaa/aaaaaaaaaa/aaaaaaaaaa/aaaaaaaaaf");
    mkd("2/aaaaaaaaaa/aaaaaaaaaa/aaaaaaaaaa/aaaaaaaaag");
    mkd("2/aaaaaaaaaa/aaaaaaaaaa/aaaaaaaaaa/aaaaaaaaah");
    mkd("2/aaaaaaaaaa/aaaaaaaaaa/aaaaaaaaaa/aaaaaaaaai");
    mkd("2/aaaaaaaaaa/aaaaaaaaaa/aaaaaaaaaa/aaaaaaaaaj");
    mkd("2/aaaaaaaaaa/aaaaaaaaaa/aaaaaaaaaa/aaaaaaaaak");
    mkd("2/aaaaaaaaaa/aaaaaaaaaa/aaaaaaaaaa/aaaaaaaaal");
    mkd("2/aaaaaaaaaa/aaaaaaaaaa/aaaaaaaaaa/aaaaaaaaam");
    mkd("2/aaaaaaaaaa/aaaaaaaaaa/aaaaaaaaaa/aaaaaaaaan");
    mkd("2/aaaaaaaaaa/aaaaaaaaaa/aaaaaaaaaa/aaaaaaaaao");
    mkd("2/aaaaaaaaaa/aaaaaaaaaa/aaaaaaaaaa/aaaaaaaaap");
    mkd("2/aaaaaaaaaa/aaaaaaaaaa/aaaaaaaaaa/aaaaaaaaaq");
}
 
void test14() {
    mkd("3");
}

void test15() {
    mkfile("4");
}

void test_suite_0() {
    test0();
    test1();
    test2();
    test3();
    test4();
    test5();
    test6();
    test7();
}

void test_suite_1() {
    test8();
    test9();
    test10();
    test11();
    test12();
    test13();
    test14();
    test15();
}

int main(int argc, char *argv[]) {
    // NOTE: may encounter ialloc error if running suite 0 and suite 1 simultaneously (recommend run 0 and then 1)
    test_suite_0();
    test_suite_1();
    exit(0);
}
