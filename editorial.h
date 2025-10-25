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
// Representa los posibles estados de un pedido dentro del sistema
enum EstadoPedido {
    Vacio,
    Iniciado,
    Almacen,
    Imprenta,
    Listo,
    Caja
};
// Estructura que define los datos de un pedido
struct Pedido {
    int id_editorial;      // Identificador de la editorial del pedido
    string id_pedido;      // Código único del pedido
    string cod_libro;      // Código del libro pedido
    string materia;        // Materia o categoría del libro
    int unidades;          // Número de unidades pedidas
    EstadoPedido estado;   // Estado actual del pedido

    Pedido() {
        id_editorial = -1;
        unidades = 0;
        estado = EstadoPedido::Vacio; //estado inicial vacio
    }
};

struct LibroStock {
    string cod_libro; //codigo del libro
    string materia; //materia del libro
    int unidades; //unidades del libro en el stock
};

class Stock {
    private:
        LibroStock libros[MAX_TITULOS]; //array con los libros en el stock
        int total_libros; //numero total de libros en el stock (esta capado a 10= TAM_LOTE)

    public:
        Stock();
        ~Stock();
        bool hayStock(string cod_libro, int unidades_pedidas); //comprueba si hay suficientes libros en el stock
        void restarStock(string cod_libro, int unidades_a_restar); //resta las unidades pedidas al stock
        void reponerStock(string cod_libro); //añade al stock +=TAM_LOTE
        void mostrar(); //muestra el stock

        // Función auxiliar para que generarPedidos() pida libros que SI existen
        LibroStock getLibroAleatorio();
};

// Nodo individual de una pila de pedidos
class NodoPila {
    private:
        Pedido valor; //almacena el pedido en el nodo
        NodoPila *siguiente; //puntero del nodo
        friend class Pila;

    public:
        NodoPila(Pedido v, NodoPila *sig = nullptr);
        ~NodoPila();
};

typedef NodoPila *pnodo; //alias del puntero

// Clase que implementa una pila de pedidos
class Pila {
    private:
        pnodo cima; //puntero al nodo superior de la pila

    public:
        Pila();
        ~Pila();
        bool esVacia(); //comprueba si la pila esta vacia
        void apilar(Pedido v); //añade un pedido a la pila
        Pedido desapilar(); //elimina y devuelve el pedido de la cima
        int mostrar(); //muestra los pedidos de la pila
        Pedido getCima(); //devuelve el pedido de la cima
        int getTamano(); //devuelve el numero de pedidos de la pila
        void vaciarCaja(); //vacia la pila
};
// Nodo individual de una cola de pedidos
class NodoCola {
    friend class Cola;
    private:
        NodoCola *siguiente; // Puntero al siguiente nodo
        Pedido elemento;     // Pedido almacenado en el nodo
    public:
        NodoCola(Pedido e, NodoCola*sig = NULL);
        ~NodoCola();
};

class Cola {
    private:
        NodoCola * primero; //puntero al primer nodo de la cola
        NodoCola * ultimo; // puntero al ultimo nodo de la cola
        int longitud; //numero de pedidos en cola

    public:
        Cola();
        ~Cola();
        void encolar(Pedido e);   // Añade un pedido al final de la cola
        Pedido inicio();          // Devuelve el primer pedido
        Pedido fin();             // Devuelve el último pedido
        Pedido desencolar();      // Elimina y devuelve el primer pedido
        bool es_vacia();          // Comprueba si la cola está vacía
        void mostrar();           // Muestra los pedidos en la cola
        int get_longitud();       // Devuelve el número de pedidos en la cola
};

string estadoToString(EstadoPedido estado);

string Materias();

Pedido generarPedidos(Stock& mi_stock);

void ejecutarPasoDeSimulacion(Cola& qIniciado, Cola& qAlmacen, Cola& qImprenta, Cola& qListo, Pila cajas[], Stock& stock);

#endif
