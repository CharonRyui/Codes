#include <iostream>
using namespace std;
int main() {
    int x;
    int y;
    // while (cin >> x) {
    //     if (cin.fail()) cout << "i am failed!" << endl;
    // };
    // char s = cin.get();
    // cout << "failbit: " << cin.fail() << "  peek: " << cin.peek() << "bad: " << cin.badbit << endl;
    // cin >> y;
    // cout << x << "-----" << y << endl;

    cin >> x;
    if (cin.fail()) cout << "i am failed" << endl;
    //char s = cin.get();
    cout << cin.peek() << endl;;
    cin >> y;
    if (cin.fail()) cout << "i am failed" << endl;
    cout << x << " " << y << endl;//s << " " << y << endl;
}