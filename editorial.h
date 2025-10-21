#ifndef EDITORIAL_H
#define EDITORIAL_H

#include <iostream>
#include <string>

using namespace std;

#define MAX_TITULOS 10
#define N_PEDIDOS_PASO 12
#define TAM_LOTE 10
#define LIBRERIAS 6
#define CAP_CAJA 5

enum EstadoPedido {
    Vacio,
    Iniciado,
    Almacen,
    Imprenta,
    Listo,
    Caja
};

struct Pedido {
    int id_editorial;
    string id_pedido;
    string cod_libro;
    string materia;
    int unidades;
    EstadoPedido estado;

    Pedido() {
        id_editorial = -1;
        unidades = 0;
        estado = EstadoPedido::Vacio;
    }
};

struct LibroStock {
    string cod_libro;
    string materia;
    int unidades;
};

class Stock {
private:
    LibroStock libros[MAX_TITULOS];
    int total_libros;

public:
    Stock();
    ~Stock();

    bool hayStock(string cod_libro, int unidades_pedidas);
    int restarStock(string cod_libro, int unidades_a_restar);
    void reponerStock(string cod_libro);
    void mostrar();

    // Función auxiliar para que generarPedidos() pida libros que SI existen
    LibroStock getLibroAleatorio();
};


class NodoPila
{
private:
    Pedido valor;
    NodoPila *siguiente;
    friend class Pila;

public:
    NodoPila(Pedido v, NodoPila *sig = nullptr);
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
        void apilar(Pedido v);
        Pedido desapilar();
        int mostrar();
        Pedido getCima();
        int getTamano();

};

class NodoCola
{
    friend class Cola;
private:
    NodoCola *siguiente;
    Pedido elemento;
public:
    NodoCola(Pedido e, NodoCola*sig = NULL);
    ~NodoCola();
};

class Cola
{
private:
    NodoCola * primero;
    NodoCola * ultimo;
    int longitud;
public:
    Cola();
    ~Cola();
    void encolar(Pedido e);
    Pedido inicio();
    Pedido fin();
    Pedido desencolar();
    bool es_vacia();
    void mostrar();
    int get_longitud();
};
string estadoToString(EstadoPedido estado);
string Materias();
int restarStock(string cod_libro, int unidades_a_restar);
Pedido generarPedidos(Stock& mi_stock);
#endif
