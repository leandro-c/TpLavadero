#include "Cliente.h""

Cliente crearCliente(string cuit, string nombre) {
    /// COMPLETAR
    ClienteSt* c = new ClienteSt;
    c->cuit = cuit;
    c->nombre = nombre;
    return c;
}

string getCuit(Cliente c) {
    /// COMPLETAR
    return c->cuit;
}

string getNombre(Cliente c) {
    /// COMPLETAR
    return c->nombre;
}

void destroyCliente(Cliente& c) {
   delete c;
   c = NULL;
}

void printCliente(Cliente c) {
if(c ==NULL){
    cout << "NULL" << endl;
}else{
    cout << "Cliente {" << endl;
    cout << "  cuit: " << c->cuit << endl;
    cout << "  nombre: " << c->nombre << endl;
    cout << "}" << endl;
    }
}

