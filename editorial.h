#include EDITORIAL.H
#define EDITORIAL.H
#include <iostream>

class NodoPila
{
    private:
        int valor;
        NodoPila *siguiente;
        friend class Pila;
    public:
        NodoPila();
        NodoPila(int v, NodoPila *sig = NULL);
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
        void apilar(int v);
        void desapilar();
        int mostrar();
};

#endif
