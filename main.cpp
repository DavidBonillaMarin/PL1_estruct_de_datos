#include <iostream>
#include "editorial.h"
using namespace std;
int main()
{
    srand(time(nullptr));
    Pila caja;

    for (int i = 0; i < 31; i++) {
        caja.apilar();
    }
    caja.mostrar();
    return 0;
}
