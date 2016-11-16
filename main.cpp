#include <iostream>
#include "Map.h"

using namespace std;

int main()
{
    /// PROBAR INTERFAZ DE CLIENTE

    /// PROBAR INTERFAZ DE MAP
    ClienteSt* c = new ClienteSt;
    c->cuit = "31-511227-4";
    c->nombre = "lcasarin";
    printCliente(c);
    return 0;
}
