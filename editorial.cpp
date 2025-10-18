//encolar,desencolar,apilar y desapilar
#include "editorial.h"
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <sstream>
using namespace std;
NodoPila::NodoPila()
{
    valor="";
    siguiente=NULL;
//ctor
}
NodoPila::NodoPila(string v, NodoPila *sig)
{
    valor = v;
    siguiente = sig;
}
NodoPila::~NodoPila()
{
//dtor
}
Pila::Pila()
    {cima = nullptr;}
Pila::~Pila()
    { while(cima) desapilar();}

bool Pila::esVacia()
{ return cima == nullptr; }

void Pila::apilar() {
    string codigo = generarPedidos();
    pnodo nuevo = new NodoPila(codigo, cima);
    cima = nuevo;
}
void Pila::apilar(string v) {
    pnodo nuevo = new NodoPila(v, cima);
    cima = nuevo;
}
void Pila::desapilar() {
    if (cima) {
        pnodo nodo = cima;
        cima = nodo->siguiente;
        delete nodo;
    } else {
        cout << "La pila está vacía.\n";
    }
}
int Pila::mostrar() {
    if (esVacia()) {
        cout << "No hay pedidos actualmente." << endl;
    } else {
        cout << left << setw(15) << "id_editorial"
             << "| " << setw(15) << "id_pedido"
             << "| " << setw(10) << "codigo" << endl;
        cout << string(80, '-') << endl;

        pnodo actual = cima;
        while (actual) {
            string valor = actual->valor;

            size_t pos1 = valor.find('|');
            size_t pos2 = valor.find('|', pos1 + 1);

            string id_editorial = valor.substr(0, pos1);
            string id_pedido = valor.substr(pos1 + 1, pos2 - pos1 - 1);
            string codigo = valor.substr(pos2 + 1);

            cout << left << setw(15) << id_editorial
                 << "| " << setw(15) << id_pedido
                 << "| " << setw(10) << codigo << endl;

            actual = actual->siguiente;
        }
    }
    return 0;
}


NodoCola::NodoCola()
{
    elemento='0';
    siguiente=NULL;
}
NodoCola::NodoCola(char e, NodoCola*sig )
{
    elemento = e;
    siguiente = sig;
}
NodoCola::~NodoCola()
{
}

Cola::Cola()
{primero = NULL; ultimo = NULL;
    longitud = 0;
}
Cola::~Cola() { }
void Cola::encolar(char elemento)
{ NodoCola *nuevo_nodo = new
NodoCola(elemento);
    if(es_vacia())
    {   primero = nuevo_nodo;
        ultimo = nuevo_nodo;
    }
    else
    {   ultimo->siguiente = nuevo_nodo;
        ultimo = nuevo_nodo;
    }
    longitud++;
}
char Cola::desencolar()
{
    if (!es_vacia())
    {
        char elemento = primero->elemento;
        NodoCola *aux = primero;

        if ((primero == ultimo) && (primero->siguiente == NULL))
        {
            primero = NULL;
            ultimo = NULL;
        }
        else
        {
            primero = primero->siguiente;
        }

        delete aux;
        longitud--;
        return elemento;
    }
    else
    {
        cout << "Error: la cola está vacía." << endl;
        return '\0';
    }
}
char Cola::inicio()
{
    if (!es_vacia())
    {
        return primero->elemento;
    }
}

char Cola::fin()
{
    if (!es_vacia())
    {
        return ultimo->elemento;
    }
}

int Cola::get_longitud()
{
    return longitud;
}

bool Cola::es_vacia()
{
    return ((primero == NULL) && (ultimo == NULL));
}

void Cola::mostrarCola()
{
    NodoCola *aux = primero;
    if (es_vacia())
    {
        cout << "Cola Vacía" << endl;
    }
    else
    {
        cout << "Datos de la Cola:" << endl;
        while (aux)
        {
            cout << aux->elemento << endl;
            aux = aux->siguiente;
        }
    }
}

string generarPedidos() {
    int pedido = rand() % 100000;

    int id_editorial = rand() % 10;

    int codigo_1 = rand() % 1000;
    int codigo_2 = rand() % 100;

    char letra = 'A' + rand() % 26;

    stringstream ss;
    ss << id_editorial << "|" << "P" <<
    setw(5) << setfill('0') << pedido << "|" <<
    setw(3) << setfill('0') << codigo_1 <<
    letra <<
    setw(2) << setfill('0') << codigo_2;

    return ss.str();
}

