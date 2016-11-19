#include <iostream>
#include "Map.h"

using namespace std;

int main()
{
    /// PROBAR INTERFAZ DE CLIENTE

    /// PROBAR INTERFAZ DE MAP
    Cliente c1 = crearCliente("1", "lcasarin");
    Cliente c2 = crearCliente("2", "acarrascoza");
    Cliente c3 = crearCliente("4", "priezer");
    //printCliente(c1);
    Map m = emptyM();
    addM(m,c1);
    addM(m,c2);
    addM(m,c3);
    //printCliente(lookupM(m,"20"));
    //removeM(m,"245");
    printMap(m);
    //ArrayList arr = domM(m);
    //imprimirArrayList(arr);
    return 0;
}
