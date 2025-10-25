#include "editorial.h"
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <set>
using namespace std;

//pasa por los distintos estados del pedido
string estadoToString(EstadoPedido estado) {
    switch (estado) {
        case EstadoPedido::Iniciado: return "Iniciado";
        case EstadoPedido::Almacen:  return "Almacen";
        case EstadoPedido::Imprenta: return "Imprenta";
        case EstadoPedido::Listo:    return "Listo";
        case EstadoPedido::Caja:     return "Caja";
        case EstadoPedido::Vacio:    return "Vacio";
        default:                     return "Desconocido";
    }
}

// Devuelve aleatoriamente una materia de entre varias posibles
string Materias() {
    string materias[] = {"Lengua", "Musica", "Matematicas", "Tecnologia", "Historia", "Fisica"};
    int total = sizeof(materias) / sizeof(materias[0]);
    int indice = rand() % total;
    return materias[indice];
}

// Constructor de la clase Stock: genera libros aleatorios con c�digos, materias y unidades
Stock::Stock() {
    total_libros = MAX_TITULOS;
    for (int i = 0; i < total_libros; i++) {
        int codigo_1 = rand() % 900 + 100;
        int codigo_2 = rand() % 90 + 10;
        char letra = 'A' + rand() % 26;

        stringstream ss_cod;
        ss_cod << codigo_1 << letra << codigo_2;

        libros[i].cod_libro = ss_cod.str();
        libros[i].materia = Materias();
        libros[i].unidades = rand() % 20 + 5;
    }
}
// Destructor de la clase Stock (actualmente no realiza ninguna acci�n)
Stock::~Stock() { }
// Comprueba si existe suficiente stock de un libro dado
bool Stock::hayStock(string cod_libro, int unidades_pedidas) {
    for (int i = 0; i < total_libros; i++) {
        if (libros[i].cod_libro == cod_libro) {
            return libros[i].unidades >= unidades_pedidas;
        }
    }
    return false;
}

// Resta una cantidad de unidades del stock de un libro y repone si es necesario
void Stock::restarStock(string cod_libro, int unidades_a_restar) {
    for (int i = 0; i < total_libros; i++) {
        if (libros[i].cod_libro == cod_libro) {
            libros[i].unidades -= unidades_a_restar;

            cout << " Se han restado " << unidades_a_restar
                 << " unidades del libro " << cod_libro
                 << " Stock restante: " << libros[i].unidades << endl;

            if (libros[i].unidades <= 0) {
                cout << "El libro " << cod_libro << " se ha agotado. Reponiendo stock..." << endl;
                reponerStock(cod_libro);
            }
            return;
        }
    }
    cout << " No se encontr� el libro " << cod_libro << " para restar stock." << endl;
}

// A�ade unidades al stock de un libro cuando se ha agotado
void Stock::reponerStock(string cod_libro) {
    for (int i = 0; i < total_libros; i++) {
        if (libros[i].cod_libro == cod_libro) {
            libros[i].unidades += TAM_LOTE;

            cout << " Repuesto el stock del libro " << cod_libro
                 << " Nuevo stock: " << libros[i].unidades << " unidades." << endl;
            return;
        }
    }
    cout << " No se pudo reponer el stock del libro " << cod_libro
         << " porque no existe en el inventario." << endl;
}

// Muestra por consola la lista de libros disponibles con su materia y unidades
void Stock::mostrar() {
    cout << "== STOCK ==" << endl;
    cout << left << setw(10) << "Codigo"
         << "| " << setw(12) << "Materia"
         << "| " << "Unidades" << endl;
    cout << string(34, '-') << endl;

    for (int i = 0; i < total_libros; i++) {
        cout << left << setw(10) << libros[i].cod_libro
             << "| " << setw(12) << libros[i].materia
             << "| " << libros[i].unidades << endl;
    }
    cout << endl;
}

// Devuelve un libro aleatorio del stock disponible
LibroStock Stock::getLibroAleatorio() {
    int indice = rand() % total_libros;
    return libros[indice];
}
// Constructor de NodoPila: crea un nodo con un pedido y un puntero al siguiente
NodoPila::NodoPila(Pedido v, NodoPila *sig) {
    valor = v;
    siguiente = sig;
}

// Destructor de NodoPila (no realiza acciones espec�ficas)
NodoPila::~NodoPila() { }

// Constructor de Pila: inicializa la pila vac�a
Pila::Pila() {
    cima = nullptr;
}

// Destructor de Pila: libera todos los nodos desapilando uno a uno
Pila::~Pila() {
    while(cima) desapilar();
}

// Comprueba si la pila est� vac�a
bool Pila::esVacia() {
    return cima == nullptr;
}

// Inserta un nuevo pedido en la parte superior de la pila
void Pila::apilar(Pedido v) {
    pnodo nuevo = new NodoPila(v, cima);
    cima = nuevo;
}

// Elimina el elemento superior de la pila y lo devuelve
Pedido Pila::desapilar() {
    if (cima) {
        Pedido valor = cima->valor;
        pnodo nodo = cima;
        cima = nodo->siguiente;
        delete nodo;
        return valor;
    } else {
        cout << "La pila est� vac�a.\n";
        return Pedido();
    }
}

// Muestra por consola todos los pedidos almacenados en la pila
int Pila::mostrar() {
    if (esVacia()) {
        cout << "(vacia)" << endl;
    } else {
        cout << left << setw(5) << "Lib"
             << "| " << setw(8) << "Id"
             << "| " << setw(10) << "Codigo"
             << "| " << setw(12) << "Materia"
             << "| " << setw(3) << "U"
             << "| " << setw(8) << "Estado"
             << "| " << endl;
        cout << string(57, '-') << endl;

        pnodo actual = cima;
        while (actual) {
            Pedido p = actual->valor;
            cout << left << setw(5) << actual->valor.id_editorial
                 << "| " << setw(8) << actual->valor.id_pedido
                 << "| " << setw(10) << actual->valor.cod_libro
                 << "| " << setw(12) << actual->valor.materia
                 << "| " << setw(3) << actual->valor.unidades
                 << "| " << setw(8) << estadoToString(actual->valor.estado)
                 << "| " << endl;
            actual = actual->siguiente;
        }
    }
    return 0;
}

// Devuelve el pedido que est� en la cima de la pila sin eliminarlo
Pedido Pila::getCima() {
    if (cima) {
        return cima->valor;
    }
    return Pedido();
}

// Devuelve el n�mero total de elementos que hay en la pila
int Pila::getTamano() {
    int cont = 0;
    pnodo actual = cima;
    while(actual) {
        cont++;
        actual = actual->siguiente;
    }
    return cont;
}

// Vac�a completamente la pila (la "caja") eliminando todos los pedidos
void Pila::vaciarCaja() {
    cout << "Caja llena. Enviando pedidos y vaciando caja..." << endl;
    while (!esVacia()) {
        desapilar();
    }
}

// Constructor de NodoCola: crea un nodo con un pedido y un puntero al siguiente
NodoCola::NodoCola(Pedido e, NodoCola*sig) {
    elemento = e;
    siguiente = sig;
}

// Destructor de NodoCola (no realiza ninguna accion)
NodoCola::~NodoCola() { }

// Constructor de Cola: inicializa una cola vac�a
Cola::Cola() {
    primero = NULL;
    ultimo = NULL;
    longitud = 0;
}

// Destructor de Cola: vac�a la cola liberando toda la memoria
Cola::~Cola() {
    while(!es_vacia()) {
        desencolar();
    }
}

// A�ade un nuevo pedido al final de la cola
void Cola::encolar(Pedido elemento) {
    NodoCola *nuevo_nodo = new NodoCola(elemento);
    if(es_vacia()) {
        primero = nuevo_nodo;
        ultimo = nuevo_nodo;
    } else {
        ultimo->siguiente = nuevo_nodo;
        ultimo = nuevo_nodo;
    }
    longitud++;
}

// Elimina y devuelve el primer elemento de la cola
Pedido Cola::desencolar() {
    if (!es_vacia()) {
        Pedido elemento_devuelto = primero->elemento;
        NodoCola *aux = primero;

        if (primero == ultimo) {
            primero = NULL;
            ultimo = NULL;
        } else {
            primero = primero->siguiente;
        }
        delete aux;
        longitud--;
        return elemento_devuelto;
    } else {
        cout << "Error: la cola est� vac�a." << endl;
        return Pedido();
    }
}

// Devuelve el primer elemento de la cola sin eliminarlo
Pedido Cola::inicio() {
    if (!es_vacia()) {
        return primero->elemento;
    }
    return Pedido();
}

// Devuelve el �ltimo elemento de la cola sin eliminarlo
Pedido Cola::fin() {
    if (!es_vacia()) {
        return ultimo->elemento;
    }
    return Pedido();
}

// Devuelve el n�mero total de elementos en la cola
int Cola::get_longitud() {
    return longitud;
}

// Comprueba si la cola est� vac�a
bool Cola::es_vacia() {
    return (primero == NULL);
}

// Muestra por consola todos los pedidos almacenados en la cola
void Cola::mostrar() {
    NodoCola *aux = primero;

    if (es_vacia()) {
        cout << "(vacia)" << endl;
    } else {
        cout << left << setw(5) << "Lib"
             << "| " << setw(8) << "Id"
             << "| " << setw(10) << "Codigo"
             << "| " << setw(12) << "Materia"
             << "| " << setw(3) << "U"
             << "| " << setw(8) << "Estado" << "|" << endl;
        cout << string(57, '-') << endl;

        while (aux) {
            cout << left << setw(5) << aux->elemento.id_editorial
                 << "| " << setw(8) << aux->elemento.id_pedido
                 << "| " << setw(10) << aux->elemento.cod_libro
                 << "| " << setw(12) << aux->elemento.materia
                 << "| " << setw(3) << aux->elemento.unidades
                 << "| " << setw(8) << estadoToString(aux->elemento.estado)
                 << "| " << endl;
            aux = aux->siguiente;
        }
    }
    cout << endl;
}

// Genera un nuevo pedido con datos aleatorios y un identificador incremental(P0001 -> P0002 -> P0003 etc)
Pedido generarPedidos(Stock& mi_stock) {
    static int contador_pedidos = 1;
    Pedido p;
    stringstream ss_id;
    ss_id << "P" << setw(5) << setfill('0') << contador_pedidos;
    p.id_pedido = ss_id.str();
    contador_pedidos++

    // Asigna un libro aleatorio del stock, una librer�a aleatoria, una cantidad de unidades,
    LibroStock libro_pedido = mi_stock.getLibroAleatorio();
    p.cod_libro = libro_pedido.cod_libro;
    p.materia = libro_pedido.materia;

    //marca el pedido con el estado "Iniciado".
    p.id_editorial = rand() % LIBRERIAS;
    p.unidades = rand() % 20 + 1;
    p.estado = EstadoPedido::Iniciado;

    return p;
}

// Ejecuta un paso de la simulaci�n del sistema de pedidos, moviendo los pedidos entre las distintas fases:
void ejecutarPasoDeSimulacion(Cola& qIniciado, Cola& qAlmacen, Cola& qImprenta, Cola& qListo, Pila cajas[], Stock& stock) {

    //FASE 4: de listo a caja
    int pedidos_en_listo = qListo.get_longitud(); //esto es para no pasar pedidos que lleguen nuevos
    for (int i = 0; i < pedidos_en_listo; i++) {
        Pedido p = qListo.inicio(); // mira el primer pedido sin sacarlo
        int id_lib = p.id_editorial;

        if (cajas[id_lib].getTamano() < CAP_CAJA) { //comprueba la capacidad de la caja de esa librer�a
            p = qListo.desencolar();
            p.estado = EstadoPedido::Caja;
            cajas[id_lib].apilar(p);
        } else {
            cout << "AVISO: La caja de la libreria " << id_lib << " esta llena." << endl;
            cajas[id_lib].vaciarCaja();

            p = qListo.desencolar();
            p.estado = EstadoPedido::Caja;
            cajas[id_lib].apilar(p);
        }
    }

    //FASE 3: de imprenta a listo
    while (!qImprenta.es_vacia()) {
        Pedido p = qImprenta.desencolar();

        p.estado = EstadoPedido::Listo;
        qListo.encolar(p);

        stock.reponerStock(p.cod_libro);
    }

    //FASE 2: de almacen a listo o imprenta
    int pedidos_en_almacen = qAlmacen.get_longitud();
    for (int i = 0; i < pedidos_en_almacen; i++) {
        Pedido p = qAlmacen.desencolar();

        if (stock.hayStock(p.cod_libro, p.unidades)) {
            stock.restarStock(p.cod_libro, p.unidades);
            p.estado = EstadoPedido::Listo;
            qListo.encolar(p);
        } else {
            p.estado = EstadoPedido::Imprenta;
            qImprenta.encolar(p);
        }
    }

    // FASE 1: de iniciado a almacen
    int num_a_mover = N_PEDIDOS_PASO;
    if (qIniciado.get_longitud() < num_a_mover) {
        num_a_mover = qIniciado.get_longitud(); //es decir si el tam es menor q 12 entonces el num a mover ser� ese numero (p ej 8)
    }

    for (int i = 0; i < num_a_mover; i++) {
        Pedido p = qIniciado.desencolar();
        p.estado = EstadoPedido::Almacen;
        qAlmacen.encolar(p);
    }
}
