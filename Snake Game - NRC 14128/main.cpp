#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <iostream>

using namespace std;
using namespace sf;

struct Punto {
    int x, y;
};

// Función para verificar si la cabeza de la serpiente colisiona con su cuerpo
bool colisionConSerpiente(const Punto& cabeza, const vector<Punto>& serpiente) {
    for (auto& parte : serpiente) {
        if (parte.x == cabeza.x && parte.y == cabeza.y)
            return true;
    }
    return false;
}

// Función para verificar si la cabeza de la serpiente colisiona con el borde de la ventana
bool colisionConBorde(const Punto& cabeza, const RenderWindow& ventana) {
    return static_cast<unsigned int>(cabeza.x) < 0 || static_cast<unsigned int>(cabeza.y) < 0 || static_cast<unsigned int>(cabeza.x) >= ventana.getSize().x / 20 || static_cast<unsigned int>(cabeza.y) >= ventana.getSize().y / 20;
}

// Función para cargar los sonidos
void cargarSonidos(SoundBuffer& bufferComer, SoundBuffer& bufferColision, SoundBuffer& bufferHito, Sound& sonidoComer, Sound& sonidoColision, Sound& sonidoHito) {
    if (!bufferComer.loadFromFile("comer.wav")) {
        cout << "Error al cargar el archivo de sonido 'comer.wav'" << endl;
        exit(-1);
    }
    sonidoComer.setBuffer(bufferComer);

    if (!bufferColision.loadFromFile("colision.wav")) {
        cout << "Error al cargar el archivo de sonido 'colision.wav'" << endl;
        exit(-1);
    }
    sonidoColision.setBuffer(bufferColision);

    if (!bufferHito.loadFromFile("logro.wav")) {
        cout << "Error al cargar el archivo de sonido 'logro.wav'" << endl;
        exit(-1);
    }
    sonidoHito.setBuffer(bufferHito);
}

// Función para cargar la música de fondo
void cargarMusica(Music& musicaFondo) {
    if (!musicaFondo.openFromFile("musica.wav")) {
        cout << "Error al cargar el archivo de música 'musica.wav'" << endl;
        exit(-1);
    }
    musicaFondo.setLoop(true); // hace que la música se repita
    musicaFondo.play();
}

// Función para crear la ventana en modo de pantalla completa
void crearVentana(RenderWindow& ventana, RectangleShape& pixel) {
    ventana.create(VideoMode::getDesktopMode(), "Juego de Serpiente", Style::Fullscreen);
    pixel.setSize(Vector2f(20, 20));
    pixel.setOutlineThickness(1);
    pixel.setOutlineColor(Color::Black);
}

// Función para inicializar la serpiente y la comida
void inicializarSerpienteYComida(vector<Punto>& serpiente, vector<Punto>& comidas, Punto& comida) {
    serpiente.push_back({rand() % 40, rand() % 30}); // Posición inicial aleatoria de la serpiente

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
}

// Función para cargar la fuente
void cargarFuente(Font& fuente) {
    fuente.loadFromFile("Montserrat-Black.ttf");
}


void crearTextoPuntuacion(Text& textoPuntuacion, Font& fuente) {
    textoPuntuacion.setCharacterSize(30);
    textoPuntuacion.setFillColor(Color::Black);
    textoPuntuacion.setPosition(100, 100);
}

void crearTextoVelocidad(Text& textoVelocidad, Font& fuente) {
    textoVelocidad.setCharacterSize(36);
    textoVelocidad.setFillColor(Color::Red);
    textoVelocidad.setPosition(200, 200);
}

void crearBotones(Text& botonJugar, Text& botonCerrar, Text& botonReintentar, Text& botonFinalizar, Font& fuente, RenderWindow& ventana) {
    botonJugar.setFont(fuente);
    botonJugar.setCharacterSize(42);
    botonJugar.setFillColor(Color::Blue);
    botonJugar.setPosition(ventana.getSize().x / 2 - botonJugar.getGlobalBounds().width / 2 - 100, ventana.getSize().y / 2 + 250);

    botonCerrar.setFont(fuente);
    botonCerrar.setCharacterSize(36);
    botonCerrar.setFillColor(Color::Green);
    botonCerrar.setPosition(ventana.getSize().x / 2 - botonCerrar.getGlobalBounds().width / 2 + 150, ventana.getSize().y / 2 + 250);

    botonReintentar.setFont(fuente);
    botonReintentar.setCharacterSize(48);
    botonReintentar.setFillColor(Color::Yellow);
    botonReintentar.setPosition(ventana.getSize().x / 2 - botonReintentar.getGlobalBounds().width / 2 - 50, ventana.getSize().y / 2 + 200);

    botonFinalizar.setFont(fuente);
    botonFinalizar.setCharacterSize(48);
    botonFinalizar.setFillColor(Color::Blue);
    botonFinalizar.setPosition(ventana.getSize().x / 2 - botonFinalizar.getGlobalBounds().width / 2 + 100, ventana.getSize().y / 2 + 200);
}

void crearBotonesDificultad(Text& botonNormal, Text& botonDificil, Text& botonMuyDificil, Font& fuente, RenderWindow& ventana) {
    botonNormal.setFont(fuente);
    botonNormal.setString("Normal (Velocidad normal)");
    botonNormal.setCharacterSize(48);
    botonNormal.setFillColor(Color::Blue);
    botonNormal.setPosition(ventana.getSize().x / 2 - botonNormal.getGlobalBounds().width / 2 - 200, ventana.getSize().y / 2 - 100);

    botonDificil.setFont(fuente);
    botonDificil.setString("Difícil (Velocidad rápida)");
    botonDificil.setCharacterSize(45);
    botonDificil.setFillColor(Color::Green);
    botonDificil.setPosition(ventana.getSize().x / 2 - botonDificil.getGlobalBounds().width / 2, ventana.getSize().y / 2);

    botonMuyDificil.setFont(fuente);
    botonMuyDificil.setString("Muy difícil (Velocidad muy rápida)");
    botonMuyDificil.setCharacterSize(50);
    botonMuyDificil.setFillColor(Color::Yellow);
    botonMuyDificil.setPosition(ventana.getSize().x / 2 - botonMuyDificil.getGlobalBounds().width / 2 + 100, ventana.getSize().y / 2 + 100);
}

void crearTextoInicio(Text& textoInicio1, Text& textoInicio2, Font& fuente, RenderWindow& ventana) {
    textoInicio1.setFont(fuente);
    textoInicio1.setString("BIENVENIDO AL JUEGO DE LA SERPIENTE");
    textoInicio1.setCharacterSize(60);
    textoInicio1.setFillColor(Color::Blue);
    textoInicio1.setPosition(ventana.getSize().x / 2 - textoInicio1.getGlobalBounds().width / 2, ventana.getSize().y / 9);
    textoInicio2.setFont(fuente);
    textoInicio2.setString("Proyecto de Final de Semestre\nDesarrollado por:\n\nJugador 1\nJugador 2\nJugador 3");
    textoInicio2.setCharacterSize(48);
    textoInicio2.setFillColor(Color::Green);
    textoInicio2.setPosition(ventana.getSize().x / 2 - textoInicio2.getGlobalBounds().width / 2, ventana.getSize().y / 2.3);
}


void iniciarJuego(bool& juegoIniciado, bool& juegoTerminado, vector<Punto>& serpiente, vector<Punto>& comidas, Punto& comida, Punto& dir, int& puntuacion, int& logros) {

    juegoIniciado = false;


    juegoTerminado = false;


    serpiente.clear();


    serpiente.push_back({ 0, 0 });


    comidas.clear();


    comida = { 10, 10 };


    comidas.push_back(comida);


    dir = { 1, 1 };

    puntuacion = 100;

    logros = 5;
}




// Función principal
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
                do { // Comprueba si la comida se genera dentro de la serpiente y la vuelve a generar si es asi
                    comidaEnSerpiente = false;
                    comida = {rand() % 40, rand() % 30}; // Nueva posicion aleatoria de la comida
                    for (Punto p : serpiente) {
                        if (p.x == comida.x && p.y == comida.y) {
                            comidaEnSerpiente = true;
                            break;
                        }
                    }
