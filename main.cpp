#include <iostream>
#include "../include/eleven.h"

using namespace std;

int main() {
    //constructors
    Eleven first{1, 2, 3, 4, 5};
    cout << "first obj (init): ";
    first.print(cout) << endl;

    Eleven second(3, 7);
    cout << "second obj (init): ";
    second.print(cout) << endl;

    Eleven third("123A");
    cout << "third obj (str): ";
    third.print(cout) << endl;

    Eleven copyThird(third);
    cout << "fourth obj (copied): ";
    copyThird.print(cout) << endl;

    Eleven moved(std::move(second));
    cout << "fifth obj (moved): ";
    moved.print(cout) << endl;

    //summa/minus/catch err minus
    Eleven summa = first.add(third);
    cout << "summa: ";
    summa.print(cout) << endl;

    try {
        Eleven diff = first.minus(second);
        cout << "diff: ";
        diff.print(cout) << endl;
    } catch (const exception& e) {
        cerr << e.what() << endl;
    }

    try {
        Eleven errdiff = second.minus(first);
        cout << "diff: ";
        errdiff.print(cout) << endl;
    } catch (const exception& e) {
        cerr << e.what() << endl;
    }

    //copy
    Eleven make_copy = first.copy();
    cout << "first obj copy: ";
    make_copy.print(cout) << endl;

    //eq/lq/gq
    cout << "first == copy -> " << (first.eq(make_copy) ? "true" : "false") << endl;
    cout << "summa < third -> " << (summa.lq(third) ? "true" : "false") << endl;
    cout << "summa > first -> " << (summa.gq(first) ? "true" : "false") << endl;

    //exception
    try {
        Eleven invalid_input("123X");
    } catch (const exception& e) {
        cerr << e.what() << endl;
    }
    return 0;
}
