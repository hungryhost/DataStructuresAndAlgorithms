#include "mainwindow.h"
#include "hashtable.h"
#include <QApplication>
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

/* THIS IS A MAIN.CPP FILE FOR LAB ¹2 (PART 2) GUI WITH TESTS FROM THE 1st PART
 * MIND THE USAGE OF TYPEDEF! */
// YURY BORODIN 2019

typedef HashT<std::string, std::string> HashTableStrStr;
int main(int argc, char *argv[])
{
    HashTableStrStr nf;
    HashTableStrStr nf2;
    HashTableStrStr nf3;
    HashTableStrStr nf4;

    bool f;
    nf.add("stud1","2wq");
    nf.add("stud1", "new");
    nf.add("stud1", "new2");
    int asize = nf.count();
    assert(asize == 1);
    nf.add("stud2", "213");
    nf.add("stud3", "213");
    std::string &s = nf["stud1"];
    std::string &s1 = nf["stud2"];
    std::string &s0 = nf["adadssa"];
    assert(s == "new2");
    assert(s1 == "213");
    nf.output("C:\\Users\\Yury Borodin\\Documents\\hashtable\\out.txt");
    nf2.input("C:\\Users\\Yury Borodin\\Documents\\hashtable\\out.txt");
    s = nf2["stud1"];
    s1 = nf2["stud2"];
    assert(s == "new2");
    assert(s1 == "213");
    assert(nf == nf2);
    HashTableStrStr nf5(nf);
    assert(nf5 == nf);
    nf5.add("stud5", "new");
    assert(!(nf5 == nf));
    int size = nf3.count();
    assert(size == 0);
    size = nf.count();
    assert(size == 3);
    nf.returnKeysByValue("213", "C:\\Users\\Yury Borodin\\Documents\\hashtable\\out.txt");
    nf3.input("C:\\Users\\Yury Borodin\\Documents\\hashtable\\out.txt");
    nf3.output("C:\\Users\\Yury Borodin\\Documents\\hashtable\\out.txt");
    s = nf3["stud2"];
    s1 = nf3["stud3"];
    assert(s == s1);
    nf3.del("stud2");
    assert(nf3.isInTable("stud2") == false);
    size = nf3.count();
    assert(size == 1);
    nf3.del("sada");
    size = nf3.count();
    assert(size == 1);
    nf3.delAll();
    f = nf4 == nf3;
    assert(f == true);
    std::cout << "all tests are passed\n";
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    _CrtDumpMemoryLeaks();
    return a.exec();
}
