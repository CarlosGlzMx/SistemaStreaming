#include <iostream>
#include "Sistema.h"

int main()
{
    // Creaci�n del objeto que maneja la aplicaci�n
    Sistema menu;
    // Ingreso al ciclo del men�
    menu.comenzar();
    // Llamada implicita del destructor de menu por el fin de main()
    return 0;
} 