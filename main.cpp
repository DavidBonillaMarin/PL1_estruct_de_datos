#include <iostream>
#include "editorial.h"
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


    cout << "Creamos la cola Vacía" << endl;
    Cola c; c.mostrarCola();
    cout << "Encolo 0" << endl;
    c.encolar('0'); c.mostrarCola();;
    cout << "Encolo 1" << endl;
    c.encolar('1'); c.mostrarCola();;
    cout << "Encolo 2" << endl;
    c.encolar('2'); c.mostrarCola();
    cout << "Primero" << c.inicio()<<endl;
    cout << "Ultimo" << c.fin()<<endl;
    cout << "Longitud Cola: " << c.get_longitud()<<endl;
    cout << "Desencolo" << endl;
    c.desencolar(); c.mostrarCola();
    cout << "Longitud Cola: " << c.get_longitud()<<endl;
    c.~Cola();
    return 0;
}
