#include <iostream>
#include "Sistema.h"

int main()
{
    // Creación del objeto que maneja la aplicación
    Sistema menu;
    // Ingreso al ciclo del menú
    menu.comenzar();
    // Llamada implicita del destructor de menu por el fin de main()
    return 0;
} 