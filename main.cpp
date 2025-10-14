#include <iostream>
#include "editorial.h"
#include "editorial.cpp"
using namespace std;
int main()
{
    cout << "Creamos la pila Vacía" << endl;
    Pila p; p.mostrar();
    cout << "Apilo 0" << endl;
    p.apilar(0); p.mostrar();
    cout << "Apilo 1" << endl;
    p.apilar(1); p.mostrar();
    cout << "Apilo 2" << endl;
    p.apilar(2); p.mostrar();
    cout << "Desapilo" << endl;
    p.desapilar(); p.mostrar();
    p.~Pila(); //es innecesario, se va a llamar al destructor al salir de la ejecución
    return 0;
}
