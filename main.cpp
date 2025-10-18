#include <iostream>
#include "editorial.h"
using namespace std;
int main()
{
    int opcion;
    srand(time(nullptr));
    Pila caja;
    cout << left << "--- MENU ---" << endl
             << "1) Generar N pedidos" << endl
             << "2) Paso (una fase)" << endl
             << "3) Mostrar estado" << endl
             << "4) Paso completo (4 fases)" << endl
             << "5) Ver el interior de una caja" << endl
             << "6) Salir" << endl;
    cout <<"¿Que opcion desea ejecutar?: ";
    cin >> opcion;
    if (opcion == 1){
        int N;
        cout << "Introduce el numero de pedidos que desea crear: ";
        cin >> N;
        for (int i = 0; i < N; i++) {
            caja.apilar();

        }
        caja.mostrar();
}
        return 0;
}
