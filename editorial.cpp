//encolar,desencolar,apilar y desapilar
#include "editorial.h"

NodoPila::NodoPila()
{
    valor=0;
    siguiente=NULL;
//ctor
}
NodoPila::NodoPila(int v, NodoPila *sig)
{
    valor = v;
    siguiente = sig;
}
NodoPila::~NodoPila()
{
//dtor
}
Pila::Pila()
{cima = NULL;}

Pila::~Pila()
{ while(cima) desapilar();}

bool Pila::esVacia()
{ return cima == NULL; }

void Pila::apilar(int v)
{ pnodo nuevo = new NodoPila(v, cima);
//comienzo de la pila nevo nodo
    cima = nuevo;
}
void Pila::desapilar()
{ pnodo nodo; //puntero aux para manipular el nodo
    if(cima)
        nodo = cima;
        cima = nodo->siguiente;
    delete nodo;
}
int Pila::mostrar()
{   if(esVacia()) {
        cout << "Pila vacia"<<endl;
}
    else{
        cout << "Cima pila: "<< cima->valor<<endl;
}
        return 0;
}
