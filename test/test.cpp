//
// Created by rick on 2022/5/20.
//
#include <iostream>

using namespace std;

namespace demo {

    template<typename T, int N> class A {
    public:
        A(T t) {
            this->t = t;
        }

        void print() {
            cout << this->t << endl;
        }

        A<T, N>  operator += (A &b) {
            this->t = this->t + b.t;
            return *this;
        }
        A<T, N>  operator << (A &b) {
            this->t = this->t + b.t;
            return *this;
        }

    private:
        T t;
    };

}

int main() {
    cout << "Hello World" << endl;
    auto a =  demo::A<int, 32>(1);
    auto b =  a << a  << a << a << a;

    b.print();
}
