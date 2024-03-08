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

// Función para crear el texto de la velocidad
void crearTextoVelocidad(Text& textoVelocidad, Font& fuente) {
    textoVelocidad.setFont(fuente);
    textoVelocidad.setString("\n\n+50 puntos: Velocidad aumentada\n+100 puntos: Logro desbloqueado\n+150 puntos: Otra bola mas de comida");
    textoVelocidad.setCharacterSize(24);
    textoVelocidad.setFillColor(Color::White);
    textoVelocidad.setPosition(10, 40); // Posiciona el texto debajo del texto de la puntuación
}

// Función para crear los botones
void crearBotones(Text& botonJugar, Text& botonCerrar, Text& botonReintentar, Text& botonFinalizar, Font& fuente, RenderWindow& ventana) {
    botonJugar.setFont(fuente);
    botonJugar.setString("Jugar");
    botonJugar.setCharacterSize(50);
    botonJugar.setFillColor(Color::Green);
    botonJugar.setPosition(ventana.getSize().x / 2 - botonJugar.getGlobalBounds().width / 2 - 250, ventana.getSize().y / 2 + 250); // Mueve el botón más abajo

    botonCerrar.setFont(fuente);
    botonCerrar.setString("Cerrar");
    botonCerrar.setCharacterSize(50);
    botonCerrar.setFillColor(Color::Red);
    botonCerrar.setPosition(ventana.getSize().x / 2 - botonCerrar.getGlobalBounds().width / 2 + 250, ventana.getSize().y / 2 + 250); // Mueve el botón más abajo

    botonReintentar.setFont(fuente);
    botonReintentar.setString("Reintentar");
    botonReintentar.setCharacterSize(50);
    botonReintentar.setFillColor(Color::Yellow);
    botonReintentar.setPosition(ventana.getSize().x / 2 - botonReintentar.getGlobalBounds().width / 2 - 200, ventana.getSize().y / 2 + 200);

    botonFinalizar.setFont(fuente);
    botonFinalizar.setString("Finalizar");
    botonFinalizar.setCharacterSize(50);
    botonFinalizar.setFillColor(Color::Red);
    botonFinalizar.setPosition(ventana.getSize().x / 2 - botonFinalizar.getGlobalBounds().width / 2 + 200, ventana.getSize().y / 2 + 200);
}

// Función para crear los botones de dificultad
void crearBotonesDificultad(Text& botonNormal, Text& botonDificil, Text& botonMuyDificil, Font& fuente, RenderWindow& ventana) {
    botonNormal.setFont(fuente);
    botonNormal.setString("Normal (Velocidad normal)");
    botonNormal.setCharacterSize(50);
    botonNormal.setFillColor(Color::White);
    botonNormal.setPosition(ventana.getSize().x / 2 - botonNormal.getGlobalBounds().width / 2, ventana.getSize().y / 2 - 100);

    botonDificil.setFont(fuente);
    botonDificil.setString("Dificil (Velocidad rápida)");
    botonDificil.setCharacterSize(50);
    botonDificil.setFillColor(Color::White);
    botonDificil.setPosition(ventana.getSize().x / 2 - botonDificil.getGlobalBounds().width / 2, ventana.getSize().y / 2);

    botonMuyDificil.setFont(fuente);
    botonMuyDificil.setString("Muy dificil (Velocidad muy rapida)");
    botonMuyDificil.setCharacterSize(50);
    botonMuyDificil.setFillColor(Color::White);
    botonMuyDificil.setPosition(ventana.getSize().x / 2 - botonMuyDificil.getGlobalBounds().width / 2, ventana.getSize().y / 2 + 100);
}

// Función para crear el texto de la pantalla de inicio
void crearTextoInicio(Text& textoInicio1, Text& textoInicio2, Font& fuente, RenderWindow& ventana) {
    textoInicio1.setFont(fuente);
    textoInicio1.setString("JUEGO DE LA SERPIENTE\n\n Proyecto Tercer Parcial\n\n              NRC 14128");
    textoInicio1.setCharacterSize(30);
    textoInicio1.setFillColor(Color::White);
    textoInicio1.setPosition(ventana.getSize().x / 2 - textoInicio1.getGlobalBounds().width / 2, ventana.getSize().y / 13);

    textoInicio2.setFont(fuente);
    textoInicio2.setString("Desarrollado por:\n\nColina Morales Mateo Ruben\nCedeno Zapata Jhois Micael\nChancusig Guaman Erick Ariel\nRamirez Cevallos Carlos Estefano");
    textoInicio2.setCharacterSize(30);
    textoInicio2.setFillColor(Color::White);
    textoInicio2.setPosition(ventana.getSize().x / 2 - 300 - textoInicio2.getGlobalBounds().width / 2, ventana.getSize().y / 2.3);
}
// Función para iniciar el juego
void iniciarJuego(bool& juegoIniciado, bool& juegoTerminado, vector<Punto>& serpiente, vector<Punto>& comidas, Punto& comida, Punto& dir, int& puntuacion, int& logros) {
    juegoIniciado = true;
    juegoTerminado = false;
    serpiente.clear();
    serpiente.push_back({rand() % 40, rand() % 30}); // Posición inicial aleatoria de la serpiente
    comidas.clear();
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

    dir = {1, 0};
    puntuacion = 0;
    logros = 0;
}

// Función principal
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
                    // Muestra la pantalla de selección de dificultad
                    ventana.clear();
                    ventana.draw(botonNormal);
                    ventana.draw(botonDificil);
                    ventana.draw(botonMuyDificil);
                    ventana.display();
                    while (true) {
                        Event eventoDificultad;
                        while (ventana.pollEvent(eventoDificultad)) {
                            if (eventoDificultad.type == Event::MouseButtonPressed) {
                                if (botonNormal.getGlobalBounds().contains(ventana.mapPixelToCoords(Mouse::getPosition(ventana)))) {
                                    velocidad = 100; // Velocidad normal
                                    iniciarJuego(juegoIniciado, juegoTerminado, serpiente, comidas, comida, dir, puntuacion, logros);
                                    break;
                                }
                                else if (botonDificil.getGlobalBounds().contains(ventana.mapPixelToCoords(Mouse::getPosition(ventana)))) {
                                    velocidad = 70; // Velocidad rápida
                                    iniciarJuego(juegoIniciado, juegoTerminado, serpiente, comidas, comida, dir, puntuacion, logros);
                                    break;
                                }
                                else if (botonMuyDificil.getGlobalBounds().contains(ventana.mapPixelToCoords(Mouse::getPosition(ventana)))) {
                                    velocidad = 40; // Velocidad muy rápida
                                    iniciarJuego(juegoIniciado, juegoTerminado, serpiente, comidas, comida, dir, puntuacion, logros);
                                    break;
                                }
                            }
                        }
                        if (juegoIniciado) break;
                    }
                }
                else if (botonCerrar.getGlobalBounds().contains(ventana.mapPixelToCoords(Mouse::getPosition(ventana)))) {
                    ventana.close();
                }
                else if (juegoTerminado && botonReintentar.getGlobalBounds().contains(ventana.mapPixelToCoords(Mouse::getPosition(ventana)))) {
                    iniciarJuego(juegoIniciado, juegoTerminado, serpiente, comidas, comida, dir, puntuacion, logros);
                }
                else if (juegoTerminado && botonFinalizar.getGlobalBounds().contains(ventana.mapPixelToCoords(Mouse::getPosition(ventana)))) {
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
                // Comprueba si la nueva dirección es opuesta a la dirección actual
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
                    comida = {rand() % 40, rand() % 30}; // Nueva posición aleatoria de la comida
                    for (Punto p : serpiente) {
                        if (p.x == comida.x && p.y == comida.y) {
                            comidaEnSerpiente = true;
                            break;
                        }
                    }
                    // Comprueba si la comida se genera dentro de los rectángulos de los textos
                    if (textoPuntuacion.getGlobalBounds().contains(comida.x * 20, comida.y * 20) || textoVelocidad.getGlobalBounds().contains(comida.x * 20, comida.y * 20)) {
                        comidaEnSerpiente = true;
                    }
               } while (comidaEnSerpiente);
                comidas[i] = comida;

                puntuacion += 10;
                if (puntuacion % 50 == 0 && velocidad > 30) { // Aumenta la velocidad cada 50 puntos
                    velocidad -= 5; // Disminuye el tiempo de espera, lo que aumenta la velocidad
                }
                if (puntuacion % 100 == 0) { // Desbloquea un logro cada 100 puntos
                    logros++;
                    sonidoHito.play();
                }
                if (puntuacion % 150 == 0) { // Agrega una bola extra de comida cada 150 puntos
                    comidas.push_back({rand() % 40, rand() % 30});
                }
                comio = true;
                break;
            }
        }
        if (!comio) {
            serpiente.erase(serpiente.begin());
        }

        if (colisionConSerpiente(siguiente, serpiente) || colisionConBorde(siguiente, ventana)) {
            sonidoColision.play();
            // Fin del juego
            juegoIniciado = false;
            juegoTerminado = true;
            Text textoFinal;
            textoFinal.setFont(fuente);
            textoFinal.setString("PUNTUACION FINAL: " + to_string(puntuacion) + "\nLOGROS: " + to_string(logros) + "\n\nGracias por jugar!");
            textoFinal.setCharacterSize(50);
            textoFinal.setFillColor(Color::White);
            textoFinal.setPosition(ventana.getSize().x / 2 - textoFinal.getGlobalBounds().width / 2, ventana.getSize().y / 4);
            ventana.clear();
            ventana.draw(textoFinal);
            ventana.draw(botonReintentar);
            ventana.draw(botonFinalizar);
            ventana.display();
            while (juegoTerminado) {
                Event eventoFinal;
                while (ventana.pollEvent(eventoFinal)) {
                    if (eventoFinal.type == Event::MouseButtonPressed) {
                        if (botonReintentar.getGlobalBounds().contains(ventana.mapPixelToCoords(Mouse::getPosition(ventana)))) {
                            iniciarJuego(juegoIniciado, juegoTerminado, serpiente, comidas, comida, dir, puntuacion, logros);
                        }
                        if (botonFinalizar.getGlobalBounds().contains(ventana.mapPixelToCoords(Mouse::getPosition(ventana)))) {
                            ventana.close();
                        }
                    }
                }
                if (juegoIniciado) break;
            }
            continue;
        }
        serpiente.push_back(siguiente);

        ventana.clear();
        pixel.setFillColor(Color::Green);
        for (Punto p : serpiente) {
            pixel.setPosition(p.x * 20, p.y * 20);
            ventana.draw(pixel);
        }
        pixel.setFillColor(Color::Red);
        for (Punto p : comidas) {
            pixel.setPosition(p.x * 20, p.y * 20);
            ventana.draw(pixel);
        }

        // Actualiza y dibuja la puntuación
        textoPuntuacion.setString("Puntuacion: " + to_string(puntuacion) + "\nLogros: " + to_string(logros));
        ventana.draw(textoPuntuacion);

        // Dibuja el texto de la velocidad
        textoVelocidad.setString("\n\n+50 puntos: Velocidad aumentada\n+100 puntos: Logro desbloqueado\n+150 puntos: Otra bola mas de comida");
        ventana.draw(textoVelocidad);

        ventana.display();

        sleep(milliseconds(velocidad));
    }

    return 0;
}

