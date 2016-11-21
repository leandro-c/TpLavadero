#include "Map.h"

///////////////////////////////////////////////
/// OPERACIONES SOBRE AVL
///////////////////////////////////////////////

// Prop.: crea una hoja con determinado cliente
AVL leafAVL(Cliente c) {
    AVLNode* node = new AVLNode;
    node->height = 1;
    node->left   = NULL;
    node->right  = NULL;
    node->kv     = c;
    return node;
}

// Prop.: devuelve la altura de un AVL
int heightAVL(AVL t) {
    return t == NULL ? 0 : t->height;
}

// Prop.: hace una rotación simple
AVL sJoinAVL(Cliente kv, AVL ti, AVL td) {
    AVL node      = leafAVL(kv);
    node->height  = 1 + max(heightAVL(ti), heightAVL(td));
    node->left    = ti;
    node->right   = td;
    return node;
}

/// PRECOND: ti es dos más profundo que td (y por lo tanto es no vacio)
// Prop.: realiza una rotación a izquierda
AVL lJoinAVL(Cliente kv, AVL ti, AVL td) {
    Cliente kvi = ti->kv;
    AVL tii     = ti->left;
    AVL tid     = ti->right;
    int hii     = heightAVL(tii);
    int hid     = heightAVL(tid);
    if (hii >= hid) {
        return sJoinAVL(kvi, tii, sJoinAVL(kv, tid, td));
    }

    Cliente kvid = tid->kv;
    AVL tidi     = tid->left;
    AVL tidd     = tid->right;
    return sJoinAVL(kvid, sJoinAVL(kvi, tii, tidi), sJoinAVL(kv, tidd, td));
}

/// PRECOND: td es dos más profundo que ti (y por lo tanto es no vacio)
// Prop.: realiza una rotación a derecha
AVL rJoinAVL(Cliente kv, AVL ti, AVL td) {
    Cliente kvd = td->kv;
    AVL tdi     = td->left;
    AVL tdd     = td->right;
    int hdi = heightAVL(tdi);
    int hdd = heightAVL(tdd);
    if (hdi <= hdd) {
        return sJoinAVL(kvd, sJoinAVL(kv, ti, tdi), tdd);
    }

    Cliente kvdi = tdi->kv;
    AVL tdii = tdi->left;
    AVL tdid = tdi->right;
    return sJoinAVL(kvdi, sJoinAVL(kv, ti, tdii), sJoinAVL(kvd, tdid, tdd));
}

/**
PRECOND:
  * ti y td son BSTs
  * las claves de ti son menores que kv
  * las claves de td son mayores que kv
  * ti y td son AVLs
  * PERO ti y td pueden tener mas altura que lo necesario!!! (pero no deben!)
     (ojo: ti dos mas que td, o td dos mas que ti, pues antes eran AVLs...)
**/
// Prop.: realiza una rotación en base a las alturas
AVL joinAVL(Cliente c, AVL ti, AVL td) {
    int hi = heightAVL(ti);
    int hd = heightAVL(td);
    if (abs(hi-hd) <= 1) {
        return sJoinAVL(c, ti, td);
    } else if (hi == hd + 2) {
        return lJoinAVL(c, ti, td);
    } else if (hd == hi + 2) {
        return rJoinAVL(c, ti, td);
    }
    // nunca puede darse otro caso
    cout << "Se viola el invariante de representación!" << endl;
}

/// PRECOND: el AVL no está vacío
// Prop.: asigna el minimo al primer parametro y devuelve "t" sin ese minimo
AVL splitMaxAVL(Cliente& c, AVL t) {
    if(t->right == NULL) {
        Cliente cliente = t->kv;
        AVL left        = t->left;
        delete t->right;
        delete t;
        c  = cliente;
        return left;
    } else {
        AVL td = splitMaxAVL(c, t->right);
        return joinAVL(t->kv, t->left, td);
    }
}

///////////////////////////////////////////////
/// INTERFAZ DE MAP Y AUXILIARES
///////////////////////////////////////////////

// Prop.: crea un Map vacio
//Costo: 0(1) --Justificacion: Delvuelve solamente NULL
Map emptyM() {
//    AVLNode* m = new AVLNode;
//    m->height = 0;
//    m->kv = NULL;
//    m->left = NULL;
    return NULL;
}

// Prop.: devuelve un value dado una key
//Costo: 0(log n) --Justificacion: busca en una parte del arbol, segun la su cuit ,busca en su parte izq o derecha.
Cliente lookupM(Map& m, string key) {
    if(m == NULL){return NULL;}//lo del maybe estaria implicito , pero hago esto en caso de que el map este en null

    if(getCuit(m->kv) == key){
        return m->kv;
    }else{
        if(getCuit(m->kv) > key){
            return lookupM(m->left,key);
        }else{
            return lookupM(m->right,key);
        }
    }

}
// Prop.: asocia un key con un value
//Costo: 0(log n) --Justificacion: inserta en una parte del arbol, y no tiene que recorerlo todo para hacerlo.
void addM(Map& m, Cliente cliente) {

    if(m == NULL){
        m = leafAVL(cliente);
    }else{
        if(getCuit(m->kv) < getCuit(cliente)){
           addM(m->right,cliente);
        }else{
            addM(m->left,cliente);
        }
    }
    m = joinAVL(m->kv, m->left, m->right);
}

// Prop.: indica si la respuesta del lookup es válida
bool isNothing(Cliente c) {
    return c == NULL;
}

// Prop.: elimina un value dado una key
//Costo: 0(log n) --Justificacion: borra en una parte del arbol, y no tiene que recorerlo todo para hacerlo.
void removeM(Map& m, string key) {
    if(m == NULL) {
        return;
    }

    if(getCuit(m->kv) == key) {
       if(m->left == NULL) {
          Map cr = m->right;
          delete m;
          m = cr;
          return;
       } else {
          m = splitMaxAVL(m->kv, m);
       }
    } else if(getCuit(m->kv) > key) {
        removeM(m->right,key);
    } else if(getCuit(m->kv) < key) {
        removeM(m->left,key);
    }

    m = joinAVL(m->kv, m->left, m->right);
}

// Prop.: devuelve la lista de claves de un Map
//Costo: 0(n^2 ) --Justificacion: recorre en sus dos arboles para poder crear un solo array con todas las hojas.
ArrayList domM(Map& m) {
    ArrayList a = crearArrayList();
    if(m != NULL){
        add(a, getCuit(m->kv));
        addAll(a,domM(m->right));
        addAll(a,domM(m->left));
    }
    return a;
}

// Prop.: libera la memoria de un Map
void destroyM(Map& m) {
    if(m != NULL){
        destroyM(m->left);
        destroyM(m->right);
        delete m;
        m = NULL;
    }

}

///////////////////////////////////////////////
/// PRINT DEL MAP (para ver AVL como usuario)
/// NOTAR QUE ROMPE ENCAPSULAMIENTO
/// PERO AYUDA A VER EL ARBOL HASTA TENER
/// BIEN LA IMPLEMENTACION
///////////////////////////////////////////////

void emptySpace(int i) {
    for(; i > 0; i--) {
        cout << "-";
    }
}

void printMapAux(Map m, int i) {
    if(m == NULL) {
        emptySpace(i);
        cout << "NULL";
        return;
    }

    emptySpace(i);
    cout << "ROOT ";
    cout << getCuit(m->kv) << endl;

    emptySpace(i);
    printMapAux(m->left, i+1);
    cout << endl;

    emptySpace(i);
    printMapAux(m->right, i+1);
    cout << endl;
}

void printMap(Map m) {
     printMapAux(m, 0);
}
