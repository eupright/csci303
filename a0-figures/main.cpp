//including other code
#include <iostream>
#include <string>

//including a namespace
using namespace std;


/* the function I used for printing repeated characters before switching to the string() function
void print_multiple(int& num, string to_print) {
    for(short int i = 0; i < num; i++){
        cout << to_print;
} }
*/

void make_triangle(short int& size){
    short int spaces = 0;
    for(short int i = size; i > 0; i -= 2, spaces++){
        cout << string(spaces, ' ') << string(i, '*') << string(spaces,' ') << endl;
    }
}

void make_diamond(short int& size){
    short int i;
    if(size%2 == 0){
        i = 2;
    } else {
        i = 1;
    }
    short int spaces = (size - i)/2;
    for(; i < size; i += 2, spaces--){
        cout << string(spaces, ' ') << string(i, '*') << string(spaces, ' ') << endl;
    }
    make_triangle(size);
}

void make_arrow(short int& size) {
    short int i;
    short int small_size = size - 2;
    for (i = small_size; i > 0; i--) {
        cout << " " << string(small_size, '*') << " " << endl;
    }
    make_triangle(size);
}

//the entry point of the program
int main(int argc, char *argv[]) {
    short int n = stoi(argv[1]);
    //cout << argv[1] << endl;
    //short int n = 6;


    cout << "The Triangle:" << endl;
    make_triangle(n);
    cout << endl;

    cout << "The Diamond:" << endl;
    make_diamond(n);
    cout << endl;

    cout << "The Arrow:" << endl;
    make_arrow(n);
    cout << endl;


    return 0;
}
