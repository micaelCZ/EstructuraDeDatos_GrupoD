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

// Función para crear el texto de la puntuación
void crearTextoPuntuacion(Text& textoPuntuacion, Font& fuente) {
    textoPuntuacion.setFont(fuente);
    textoPuntuacion.setCharacterSize(24);
    textoPuntuacion.setFillColor(Color::White);
    textoPuntuacion.setPosition(10, 10);
}



































































































