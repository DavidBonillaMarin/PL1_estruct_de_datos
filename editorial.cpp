#include "editorial.h"
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <set>

using namespace std;

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

string Materias(){
    string materias[] = {"Lengua", "Musica", "Matematicas", "Tecnologia", "Historia", "Fisica"};
    int total = sizeof(materias) / sizeof(materias[0]);
    int indice = rand() % total;
    return materias[indice];
}

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

Stock::~Stock() { }

bool Stock::hayStock(string cod_libro, int unidades_pedidas) {
    for (int i = 0; i < total_libros; i++) {
        if (libros[i].cod_libro == cod_libro) {
            return libros[i].unidades >= unidades_pedidas;
        }
    }
    return false;
}
void Stock::restarStock(string cod_libro, int unidades_a_restar) {
    for (int i = 0; i < total_libros; i++) {
        if (libros[i].cod_libro == cod_libro) {
            libros[i].unidades -= unidades_a_restar;
            return;
        }
    }
}

void Stock::reponerStock(string cod_libro) { //para cuando un pedido va a imprenta
    for (int i = 0; i < total_libros; i++) {
        if (libros[i].cod_libro == cod_libro) {
            libros[i].unidades += TAM_LOTE;
            return;
        }
    }
}

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

LibroStock Stock::getLibroAleatorio() {
    int indice = rand() % total_libros;
    return libros[indice];
}


NodoPila::NodoPila(Pedido v, NodoPila *sig)
{
    valor = v;
    siguiente = sig;
}

NodoPila::~NodoPila(){}

Pila::Pila()
    {cima = nullptr;}
Pila::~Pila()
    { while(cima) desapilar();}

bool Pila::esVacia()
{ return cima == nullptr; }

void Pila::apilar(Pedido v) {
    pnodo nuevo = new NodoPila(v, cima);
    cima = nuevo;
}
Pedido Pila::desapilar() {
    if (cima) {
        Pedido valor = cima->valor;
        pnodo nodo = cima;
        cima = nodo->siguiente;
        delete nodo;
        return valor;
    } else {
        cout << "La pila está vacía.\n";
        return Pedido();
    }
}
int Pila::mostrar() {
    if (esVacia()) {
        cout << "(vacia)" << endl;
    } else {
        cout << left << setw(5) << "Lib"
             << "| " << setw(8) << "Id"
             << "| " << setw(10) << "Codigo"
             << "| " << setw(12) << "Materia"
             << "| " << setw(3) << "U"
             << "| " << "Estado" << endl;
        cout << string(54, '-') << endl;

        pnodo actual = cima;
        while (actual) {
            Pedido p = actual->valor;
            cout << left << setw(5) << actual->valor.id_editorial
                 << "| " << setw(8) << actual->valor.id_pedido
                 << "| " << setw(10) << actual->valor.cod_libro
                 << "| " << setw(12) << actual->valor.materia
                 << "| " << setw(3) << actual->valor.unidades
                 << "| " << estadoToString(actual->valor.estado) << endl;
            actual = actual->siguiente;

        }
    }
    return 0;
}

Pedido Pila::getCima() {
    if (cima) {
        return cima->valor;
    }
    return Pedido();
}

int Pila::getTamano() {
    int cont = 0;
    pnodo actual = cima;
    while(actual) {
        cont++;
        actual = actual->siguiente;
    }
    return cont;
}

void Pila::vaciarCaja() {
    cout << "Caja llena. Enviando pedidos y vaciando caja..." << endl;
    while (!esVacia()) {
        desapilar();
    }
}

NodoCola::NodoCola(Pedido e, NodoCola*sig )
{
    elemento = e;
    siguiente = sig;
}
NodoCola::~NodoCola() { }

Cola::Cola(){
    primero = NULL;
    ultimo = NULL;
    longitud = 0;
}

Cola::~Cola() {
    while(!es_vacia()){
        desencolar();
    }
}

void Cola::encolar(Pedido elemento) {
    NodoCola *nuevo_nodo = new NodoCola(elemento);
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
Pedido Cola::desencolar()
{
    if (!es_vacia())
    {
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
    }
    else
    {
        cout << "Error: la cola está vacía." << endl;
        return Pedido();
    }
}

Pedido Cola::inicio() {
    if (!es_vacia()) {
        return primero->elemento;
    }
    return Pedido();
}

Pedido Cola::fin() {
    if (!es_vacia()) {
        return ultimo->elemento;
    }
    return Pedido();
}

int Cola::get_longitud()
{
    return longitud;
}

bool Cola::es_vacia()
{
    return (primero == NULL);
}

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
             << "| " << "Estado" << "|" << endl;
        cout << string(54, '-') << endl;

        while (aux) {
            cout << left << setw(5) << aux->elemento.id_editorial
                 << "| " << setw(8) << aux->elemento.id_pedido
                 << "| " << setw(10) << aux->elemento.cod_libro
                 << "| " << setw(12) << aux->elemento.materia
                 << "| " << setw(3) << aux->elemento.unidades
                 << "| " << estadoToString(aux->elemento.estado) << endl;
            aux = aux->siguiente;
        }
    }
    cout << endl;
}

Pedido generarPedidos(Stock& mi_stock) {
    static int contador_pedidos = 1;
    Pedido p;
    stringstream ss_id;
    ss_id << "P" << setw(5) << setfill('0') << contador_pedidos;
    p.id_pedido = ss_id.str();
    contador_pedidos++;

    LibroStock libro_pedido = mi_stock.getLibroAleatorio();
    p.cod_libro = libro_pedido.cod_libro;
    p.materia = libro_pedido.materia;

    p.id_editorial = rand() % LIBRERIAS;
    p.unidades = rand() % 20 + 1;
    p.estado = EstadoPedido::Iniciado;

    return p;
}

void ejecutarPasoDeSimulacion(Cola& qIniciado, Cola& qAlmacen, Cola& qImprenta, Cola& qListo, Pila cajas[], Stock& stock) {

    //FASE 4: de listo a caja
    int pedidos_en_listo = qListo.get_longitud(); //estp es para no pasar pedidos que lleguen nuevos
    for (int i = 0; i < pedidos_en_listo; i++) {
        Pedido p = qListo.inicio(); // mira el primer pedido sin sacarlo
        int id_lib = p.id_editorial;

        if (cajas[id_lib].getTamano() < CAP_CAJA) {  //comprueba la capacidad de la caja de esa librería
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

        stock.reponerStock(p.cod_libro); //hay que reponerlo aqui?
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
        num_a_mover = qIniciado.get_longitud(); //es decir si el tam es menor q 12 entonces el num a mover será ese numero (p ej 8)
    }

    for (int i = 0; i < num_a_mover; i++) {
        Pedido p = qIniciado.desencolar();
        p.estado = EstadoPedido::Almacen;
        qAlmacen.encolar(p);
    }
}
