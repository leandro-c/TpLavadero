#include <iostream>

using namespace std;

struct ClienteSt {
    string cuit;
    string nombre;
};

typedef ClienteSt* Cliente;

// Prop.: crea un cliente dado un cuit y un nombre
Cliente crearCliente(string cuit, string nombre);

// Prop.: devuelve el cuit de un cliente
string getCuit(Cliente c);

// Prop.: devuelve el nombre de un cliente
string getNombre(Cliente c);

// Prop.: libera la memoria de un cliente
void destroyCliente(Cliente& c);

// Prop.: imprime a un cliente
void printCliente(Cliente c);


