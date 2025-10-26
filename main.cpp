#include <iostream>
#include "editorial.h"
#include <cstdlib>

using namespace std;

int main()
{
    int opcion = -1;
    srand(time(nullptr));

    Stock mi_stock;

    Cola cola_iniciado;
    Cola cola_almacen;
    Cola cola_imprenta;
    Cola cola_listo;

    Pila cajas_librerias[LIBRERIAS];

    while (opcion!=0) {

        cout << left << "--- MENU ---" << endl
             << "1) Generar N pedidos" << endl
             << "2) Paso (una fase)" << endl
             << "3) Mostrar estado" << endl
             << "4) Paso completo (4 fases)" << endl
             << "5) Ver el interior de una caja" << endl
             << "0) Salir" << endl;
        cout <<"¿Que opcion desea ejecutar?: ";
        cin >> opcion;

        if (opcion == 1) {

            int N;
            cout << endl << "Introduce el numero de pedidos que desea crear: ";
            cin >> N;

            for (int i = 0; i < N; i++) {
                Pedido nuevo_pedido = generarPedidos(mi_stock);
                cola_iniciado.encolar(nuevo_pedido);
            }

            cout << endl << "Generados " << N << " pedidos en QIniciado." << endl;
            cout << "\nQIniciado:" << endl;
            cola_iniciado.mostrar();

        } else if (opcion == 2) {

            cout << endl << "Ejecutando un paso de simulacion..." << endl;

            ejecutarPasoDeSimulacion(cola_iniciado, cola_almacen, cola_imprenta, cola_listo, cajas_librerias, mi_stock);

            cout << "Paso ejecutado." << endl;
            cout << endl << "Elija la opcion 3 para ver el estado actual del sistema." << endl << endl;

        } else if (opcion == 3) {

            cout << endl << "--- ESTADO DEL SISTEMA ---" << endl << endl;

            mi_stock.mostrar();

            cout << "QIniciado:" << endl;
            cola_iniciado.mostrar();

            cout << "QAlmacen:" << endl;
            cola_almacen.mostrar();

            cout << "QImprenta:" << endl;
            cola_imprenta.mostrar();

            cout << "QListo:" << endl;
            cola_listo.mostrar();

            cout << "-- CAJAS (pilas por libreria) --" << endl;

            for(int i=0; i<LIBRERIAS; i++) {

                Pedido p_cima = cajas_librerias[i].getCima();

                cout << "Libreria " << i
                     << " -> tam=" << cajas_librerias[i].getTamano()
                     << " top-P=" << (p_cima.estado == EstadoPedido::Vacio ? "---" : p_cima.id_pedido)
                     << endl;
            }

            cout << endl;

        } else if (opcion == 4) {

            cout << endl << "Ejecutando 4 pasos de simulacion..." << endl;

            while (!cola_iniciado.es_vacia() || !cola_almacen.es_vacia() ||
                   !cola_imprenta.es_vacia() || !cola_listo.es_vacia()) {
                ejecutarPasoDeSimulacion(cola_iniciado, cola_almacen, cola_imprenta, cola_listo, cajas_librerias, mi_stock);
            }

            cout << "Paso ejecutado." << endl;
            cout << endl << "Elija la opcion 3 para ver el estado actual del sistema." << endl << endl;

        } else if (opcion == 5) {

            int id_lib;
            cout << endl << "Introduce el id de la libreria (0 a " << LIBRERIAS-1 << "): ";
            cin >> id_lib;

            if (id_lib >= 0 && id_lib < LIBRERIAS) {
                cout << "\n== Caja Libreria " << id_lib << " (top -> bottom) ==" << endl;
                cajas_librerias[id_lib].mostrar();
            } else {
                cout << "ID de libreria no valido." << endl;
            }
            cout << endl;
        }
    }
    cout << endl << "Saliendo del programa..." << endl;
    return 0;
}
