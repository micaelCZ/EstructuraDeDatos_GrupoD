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

Punto dir = {1, 0};

    int puntuacion = 0;
    int logros = 0;
    int velocidad = 100;

    // Carga la fuente
    Font fuente;
    fuente.loadFromFile("Montserrat-Black.ttf");











































































































// Funci�n principal
int main() {
    SoundBuffer bufferComer, bufferColision, bufferHito;
    Sound sonidoComer, sonidoColision, sonidoHito;
    cargarSonidos(bufferComer, bufferColision, bufferHito, sonidoComer, sonidoColision, sonidoHito);

    Music musicaFondo;
    cargarMusica(musicaFondo);

    RenderWindow ventana;
    RectangleShape pixel;
    crearVentana(ventana, pixel);

    vector<Punto> serpiente;
    vector<Punto> comidas;
    Punto comida;
    inicializarSerpienteYComida(serpiente, comidas, comida);

    Font fuente;
    cargarFuente(fuente);

    Text textoPuntuacion;
    crearTextoPuntuacion(textoPuntuacion, fuente);

    Text textoVelocidad;
    crearTextoVelocidad(textoVelocidad, fuente);

    Text botonJugar, botonCerrar, botonReintentar, botonFinalizar;
    crearBotones(botonJugar, botonCerrar, botonReintentar, botonFinalizar, fuente, ventana);

    Text botonNormal, botonDificil, botonMuyDificil;
    crearBotonesDificultad(botonNormal, botonDificil, botonMuyDificil, fuente, ventana);

    Text textoInicio1, textoInicio2;
    crearTextoInicio(textoInicio1, textoInicio2, fuente, ventana);

    bool juegoIniciado = false;
    bool juegoTerminado = false;
    bool comidaEnSerpiente;

    Punto dir = {1, 0};
    int puntuacion = 0;
    int logros = 0;
    int velocidad = 100;

    while (ventana.isOpen()) {
        Event evento;
        while (ventana.pollEvent(evento)) {
            if (evento.type == Event::Closed)
                ventana.close();
            else if (evento.type == Event::MouseButtonPressed) {
                if (botonJugar.getGlobalBounds().contains(ventana.mapPixelToCoords(Mouse::getPosition(ventana)))) {
                    iniciarJuego(juegoIniciado, juegoTerminado, serpiente, comidas, comida, dir, puntuacion, logros);
                }
                if (botonCerrar.getGlobalBounds().contains(ventana.mapPixelToCoords(Mouse::getPosition(ventana)))) {
                    ventana.close();
                }
                if (juegoTerminado && botonReintentar.getGlobalBounds().contains(ventana.mapPixelToCoords(Mouse::getPosition(ventana)))) {
                    iniciarJuego(juegoIniciado, juegoTerminado, serpiente, comidas, comida, dir, puntuacion, logros);
                }
                if (juegoTerminado && botonFinalizar.getGlobalBounds().contains(ventana.mapPixelToCoords(Mouse::getPosition(ventana)))) {
                    ventana.close();
                }
            }
            else if (evento.type == Event::KeyPressed) {
                Punto nuevaDir;
                switch (evento.key.code) {
                    case Keyboard::Up:    nuevaDir = { 0, -1}; break;
                    case Keyboard::Down:  nuevaDir = { 0,  1}; break;
                    case Keyboard::Left:  nuevaDir = {-1,  0}; break;
                    case Keyboard::Right: nuevaDir = { 1,  0}; break;
                    default: break;
                }
                // Comprueba si la nueva direcci�n es opuesta a la direcci�n actual
                if (nuevaDir.x != -dir.x || nuevaDir.y != -dir.y) {
                    dir = nuevaDir;
                }
            }
        }

        if (!juegoIniciado) {
            ventana.clear();
            ventana.draw(textoInicio1);
            ventana.draw(textoInicio2);
            ventana.draw(botonJugar);
            ventana.draw(botonCerrar);
            ventana.display();
            continue;
        }

        Punto siguiente = {serpiente.back().x + dir.x, serpiente.back().y + dir.y};
        bool comio = false;
        for (int i = 0; i < comidas.size(); i++) {
            if (siguiente.x == comidas[i].x && siguiente.y == comidas[i].y) {
                sonidoComer.play();
                do {
                    comidaEnSerpiente = false;
                    comida = {rand() % 40, rand() % 30}; // Nueva posici�n aleatoria de la comida
                    for (Punto p : serpiente) {
                        if (p.x == comida.x && p.y == comida.y) {
                            comidaEnSerpiente = true;
                            break;
                        }
                    }
