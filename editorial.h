#ifndef EDITORIAL_H
#define EDITORIAL_H
#include <iostream>
#include <string>
using namespace std;


class NodoPila
{
private:
    string valor;
    NodoPila *siguiente;
    friend class Pila;

public:
    NodoPila();
    NodoPila(string v, NodoPila *sig = nullptr);
    ~NodoPila();
};

typedef NodoPila *pnodo;

class Pila
{
    private:
        pnodo cima;
    public:
        Pila();
        ~Pila();
        bool esVacia();
        void apilar(string v);
        void desapilar();
        int mostrar();
};
class NodoCola
{
    friend class Cola;
private:
    NodoCola *siguiente;
    char elemento;
public:
    NodoCola();
    NodoCola(char e, NodoCola*sig = NULL);
    ~NodoCola();
};
class Cola
{
private:
    NodoCola * primero;
        NodoCola * ultimo;
        int longitud;
public:
    Cola(); ~Cola();
    void encolar(char);
    char inicio();
    char fin();
    char desencolar();
    bool es_vacia();
    void mostrarCola();
    int get_longitud();
};
#endif
