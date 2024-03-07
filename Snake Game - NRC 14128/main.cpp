//crear funcion de colision si la serpiente choca con esta misma 
#include <iostream>

using namespace std;
using namespace sf;

struct Punto {
    int x, y;
};

bool colisionConSerpiente(const Punto& cabeza, const vector<Punto>& serpiente) {
    for (auto& parte : serpiente) {
        if (parte.x == cabeza.x && parte.y == cabeza.y)
            return true;
    }
    return false;
}

