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











































































































// Funcion principal
int main() {
    SoundBuffer bufferComer, bufferColision, bufferHito;
    Sound sonidoComer, sonidoColision, sonidoHito;
    cargarSonidos(bufferComer, bufferColision, bufferHito, sonidoComer, sonidoColision, sonidoHito);
    // Carga la musica de fondo
    Music musicaFondo;
    cargarMusica(musicaFondo);
    // Crea la ventana y el pixel
    RenderWindow ventana;
    RectangleShape pixel;
    crearVentana(ventana, pixel);
    // Inicializa la serpiente y la comida
    vector<Punto> serpiente;
    vector<Punto> comidas;
    Punto comida;
    inicializarSerpienteYComida(serpiente, comidas, comida);
    // Carga la fuente
    Font fuente;
    cargarFuente(fuente);
    // Crea el texto de la puntuacion
    Text textoPuntuacion;
    crearTextoPuntuacion(textoPuntuacion, fuente);
    // Crea el texto de la velocidad
    Text textoVelocidad;
    crearTextoVelocidad(textoVelocidad, fuente);
    // Crea los botones
    Text botonJugar, botonCerrar, botonReintentar, botonFinalizar;
    crearBotones(botonJugar, botonCerrar, botonReintentar, botonFinalizar, fuente, ventana);
    // Crea los botones de dificultad
    Text botonNormal, botonDificil, botonMuyDificil;
    crearBotonesDificultad(botonNormal, botonDificil, botonMuyDificil, fuente, ventana);
    // Crea el texto de la pantalla de inicio
    Text textoInicio1, textoInicio2;
    crearTextoInicio(textoInicio1, textoInicio2, fuente, ventana);
    // Inicializa las variables del juego
    bool juegoIniciado = false;
    bool juegoTerminado = false;
    bool comidaEnSerpiente;
    // Inicializa la direccion de la serpiente
    Punto dir = {1, 0};
    int puntuacion = 0;
    int logros = 0;
    int velocidad = 100;
    // Bucle principal
    while (ventana.isOpen()) {
        Event evento;
        while (ventana.pollEvent(evento)) {
            if (evento.type == Event::Closed) // Cierra la ventana si se presiona el boton de cerrar
                ventana.close();
            else if (evento.type == Event::MouseButtonPressed) { //Si se presiona un boton del mouse...
                if (botonJugar.getGlobalBounds().contains(ventana.mapPixelToCoords(Mouse::getPosition(ventana)))) { // ...y el boton de jugar...
                    iniciarJuego(juegoIniciado, juegoTerminado, serpiente, comidas, comida, dir, puntuacion, logros); //...inicia el juego y carga los valores iniciales
                }
                if (botonCerrar.getGlobalBounds().contains(ventana.mapPixelToCoords(Mouse::getPosition(ventana)))) { // Boton de cerrar
                    ventana.close();
                }
                if (juegoTerminado && botonReintentar.getGlobalBounds().contains(ventana.mapPixelToCoords(Mouse::getPosition(ventana)))) { // Boton de reintentar
                    iniciarJuego(juegoIniciado, juegoTerminado, serpiente, comidas, comida, dir, puntuacion, logros);
                }
                if (juegoTerminado && botonFinalizar.getGlobalBounds().contains(ventana.mapPixelToCoords(Mouse::getPosition(ventana)))) { // Boton de finalizar
                    ventana.close();
                }
            }
            else if (evento.type == Event::KeyPressed) { // Cambia la direccion de la serpiente si se presiona una tecla
                Punto nuevaDir;
                switch (evento.key.code) {
                    case Keyboard::Up:    nuevaDir = { 0, -1}; break; //Tecla Arriba
                    case Keyboard::Down:  nuevaDir = { 0,  1}; break; //Tecla Abajo
                    case Keyboard::Left:  nuevaDir = {-1,  0}; break; //Tecla Izquierda
                    case Keyboard::Right: nuevaDir = { 1,  0}; break; //Tecla Derecha
                    default: break;
                }
                // Comprueba si la nueva direccion es opuesta a la direccion actual
                if (nuevaDir.x != -dir.x || nuevaDir.y != -dir.y) {
                    dir = nuevaDir;
                }
            }
        }
        // Dibuja la pantalla de inicio si el juego no ha iniciado
        if (!juegoIniciado) {
            ventana.clear();
            ventana.draw(textoInicio1);
            ventana.draw(textoInicio2);
            ventana.draw(botonJugar);
            ventana.draw(botonCerrar);
            ventana.display();
            continue;
        }
        // Dibuja la pantalla de dificultad si el juego no ha iniciado
        Punto siguiente = {serpiente.back().x + dir.x, serpiente.back().y + dir.y};
        bool comio = false; // Indica si la serpiente comio una comida
        for (int i = 0; i < comidas.size(); i++) {
            if (siguiente.x == comidas[i].x && siguiente.y == comidas[i].y) {
                sonidoComer.play(); // Reproduce el sonido de comer
                do {
                    comidaEnSerpiente = false;
                    comida = {rand() % 40, rand() % 30}; // Nueva posicion aleatoria de la comida
                    for (Punto p : serpiente) {
                        if (p.x == comida.x && p.y == comida.y) {
                            comidaEnSerpiente = true;
                            break;
                        }
                    }
