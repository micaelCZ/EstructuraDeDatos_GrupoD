//crear funcion de colision si la serpiente choca con esta misma 
// importamos más bibliotecas que se utilizarán
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
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
// añadir funcion de colision con los bordes
bool colisionConBorde(const Punto& cabeza, const RenderWindow& ventana) {
    return static_cast<unsigned int>(cabeza.x) < 0 || static_cast<unsigned int>(cabeza.y) < 0 || static_cast<unsigned int>(cabeza.x) >= ventana.getSize().x / 20 || static_cast<unsigned int>(cabeza.y) >= ventana.getSize().y / 20;
}
int main() {
// Carga los sonidos
    SoundBuffer bufferComer;
    if (!bufferComer.loadFromFile("comer.wav")) {
        cout << "Error al cargar el archivo de sonido 'comer.wav'" << endl;
        return -1;
    }
    Sound sonidoComer;
    sonidoComer.setBuffer(bufferComer);

    SoundBuffer bufferColision;
    if (!bufferColision.loadFromFile("colision.wav")) {
        cout << "Error al cargar el archivo de sonido 'colision.wav'" << endl;
        return -1;
    }
    Sound sonidoColision;
    sonidoColision.setBuffer(bufferColision);

    SoundBuffer bufferHito;
    if (!bufferHito.loadFromFile("logro.wav")) {
        cout << "Error al cargar el archivo de sonido 'logro.wav'" << endl;
        return -1;
    }
    Sound sonidoHito;
    sonidoHito.setBuffer(bufferHito);

    // Carga la música de fondo
    
    Music musicaFondo;
    if (!musicaFondo.openFromFile("musica.wav")) {
        cout << "Error al cargar el archivo de música 'musica.wav'" << endl;
        return -1;
    }
    musicaFondo.setLoop(true); // hace que la música se repita
    musicaFondo.play();
    vector<Punto> serpiente;
    serpiente.push_back({rand() % 40, rand() % 30}); // Posición inicial aleatoria de la serpiente
   
    vector<Punto> comidas;
    Punto comida;
    bool comidaEnSerpiente;
    do {
    comidaEnSerpiente = false;
    comida = {rand() % 40, rand() % 30}; // Posición inicial aleatoria de la comida
    for (Punto p : serpiente) {
        if (p.x == comida.x && p.y == comida.y) {
            comidaEnSerpiente = true;
            break;
        }
    }
} while (comidaEnSerpiente);
comidas.push_back(comida);
