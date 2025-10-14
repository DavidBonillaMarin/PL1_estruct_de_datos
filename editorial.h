#ifndef EDITORIAL_H
#define EDITORIAL_H

#include <string>

enum class EstadoPedido {
    Iniciado,
    Almacen,
    Imprenta,
    Listo,
    Caja
};

struct Pedido {
    std::string id_editorial;
    std::string id_pedido;
    std::string cod_libro;
    std::string materia;
    int unidades;
    EstadoPedido estado = EstadoPedido::Iniciado;
};

// Aquí también irían los prototipos de funciones, ej.:
// void procesarPedido(Pedido& p);
// bool enviarAPedido(Pedido p);

#endif
