#include "includes.h"
#include "rotor.h"
#include "cifrar.h"

/**
 * @brief Cifra un mensaje utilizando tres rotores.
 *
 * La funcion lee los rotores desde archivos, toma un mensaje en texto plano
 * y lo procesa letra por letra para obtener el mensaje cifrado.
 * Las posiciones iniciales de los rotores deben ser guardadas para
 * poder descifrar el mensaje posteriormente.
 */

void cifrar(std::string mensaje_original, int primera_posicion_indice, int segunda_posicion_indice, int tercera_posicion_indice) {

    // Lee los archivos de rotor
    std::string primer_rotor = leerRotor("Rotor1.txt");
    std::string segundo_rotor = leerRotor("Rotor2.txt");
    std::string tercer_rotor = leerRotor("Rotor3.txt");

    // Si algun rotor no se pudo leer correctamente, se cancela el proceso, se usan las funciones .empty para saber si están vacios.
    if (primer_rotor.empty() || segundo_rotor.empty() || tercer_rotor.empty()) {
        std::cout << "Error al cargar los rotores." << std::endl;
        return;
    }

    // Separar el cableado del notch (guardados como "cableado|notch")
    int pos_separador_primero = -1;
    for (int i = 0; i < primer_rotor.length(); ++i) {
        if (primer_rotor[i] == '|') {
            pos_separador_primero = i;
            break;
        }
    }
    std::string cableado_primer_rotor;
    if (pos_separador_primero != -1) {
        for (int i = 0; i < pos_separador_primero; ++i) {
            cableado_primer_rotor += primer_rotor[i];
        }
    }

    int pos_separador_segundo = -1;
    for (int i = 0; i < segundo_rotor.length(); ++i) {
        if (segundo_rotor[i] == '|') {
            pos_separador_segundo = i;
            break;
        }
    }
    std::string cableado_segundo_rotor;
    if (pos_separador_segundo != -1) {
        for (int i = 0; i < pos_separador_segundo; ++i) {
            cableado_segundo_rotor += segundo_rotor[i];
        }
    }

    int pos_separador_tercero = -1;
    for (int i = 0; i < tercer_rotor.length(); ++i) {
        if (tercer_rotor[i] == '|') {
            pos_separador_tercero = i;
            break;
        }
    }
    std::string cableado_tercer_rotor;
    if (pos_separador_tercero != -1) {
        for (int i = 0; i < pos_separador_tercero; ++i) {
            cableado_tercer_rotor += tercer_rotor[i];
        }
    }

    // validar notches manualmente
    std::string notch_primer_rotor;
    if (pos_separador_primero != -1) {
        for (int i = pos_separador_primero + 1; i < primer_rotor.length(); ++i) {
            notch_primer_rotor += primer_rotor[i];
        }
    }
    int indice_notch_primero;
    if (notch_primer_rotor.empty() || notch_primer_rotor[0] < 'A' || notch_primer_rotor[0] > 'Z') {
        indice_notch_primero = 25;  // Default 'Z'
    }
    else {
        indice_notch_primero = notch_primer_rotor[0] - 'A';
    }

    std::string notch_segundo_rotor;
    if (pos_separador_segundo != -1) {
        for (int i = pos_separador_segundo + 1; i < segundo_rotor.length(); ++i) {
            notch_segundo_rotor += segundo_rotor[i];
        }
    }
    int indice_notch_segundo;
    if (notch_segundo_rotor.empty() || notch_segundo_rotor[0] < 'A' || notch_segundo_rotor[0] > 'Z') {
        indice_notch_segundo = 25;  // Default 'Z'
    }
    else {
        indice_notch_segundo = notch_segundo_rotor[0] - 'A';
    }

    std::string notch_tercer_rotor;
    if (pos_separador_tercero != -1) {
        for (int i = pos_separador_tercero + 1; i < tercer_rotor.length(); ++i) {
            notch_tercer_rotor += tercer_rotor[i];
        }
    }
    int indice_notch_tercero;
    if (notch_tercer_rotor.empty() || notch_tercer_rotor[0] < 'A' || notch_tercer_rotor[0] > 'Z') {
        indice_notch_tercero = 25;  // Default 'Z'
    }
    else {
        indice_notch_tercero = notch_tercer_rotor[0] - 'A';
    }

    // Se convierte todo a mayusculas y se eliminan los caracteres que no sean letras entre A y Z.
    std::string mensaje_procesado;
    int longitud_original = mensaje_original.length();

    for (int i = 0; i < longitud_original; i++) {
        char letra = toUpper(mensaje_original[i]);
        if (letra >= 'A' && letra <= 'Z') {
            mensaje_procesado += letra;
        }
    }



    // Cifrar letra por letra
    std::string mensaje_cifrado;
    int longitud_procesado = mensaje_procesado.length();

    for (int i = 0; i < longitud_procesado; i++) {
        char caracter = mensaje_procesado[i];

        // El primer rotor avanza siempre una posicion
        primera_posicion_indice = (primera_posicion_indice + 1) % 26;

        if (primera_posicion_indice == indice_notch_primero) {
            segunda_posicion_indice
                = (segunda_posicion_indice
                    + 1) % 26;

            if (segunda_posicion_indice
                == indice_notch_segundo) {
                tercera_posicion_indice = (tercera_posicion_indice + 1) % 26;
            }
        }

        // Paso por los rotores hacia adelante (CIFRADO)
        int entrada = caracter - 'A';

        int entrada_efectiva1 = (entrada + primera_posicion_indice) % 26;
        int salida_mapeada1 = cableado_primer_rotor[entrada_efectiva1] - 'A';
        int salida1 = (salida_mapeada1 - primera_posicion_indice + 26) % 26;

        int entrada_efectiva2 = (salida1 + segunda_posicion_indice
            ) % 26;
        int salida_mapeada2 = cableado_segundo_rotor[entrada_efectiva2] - 'A';
        int salida2 = (salida_mapeada2 - segunda_posicion_indice
            + 26) % 26;

        int entrada_efectiva3 = (salida2 + tercera_posicion_indice) % 26;
        int salida_mapeada3 = cableado_tercer_rotor[entrada_efectiva3] - 'A';
        int salida3 = (salida_mapeada3 - tercera_posicion_indice + 26) % 26;

        // Convierte el resultado final en una letra
        char letra_cifrada = 'A' + salida3;
        mensaje_cifrado += letra_cifrada;
    }

    std::string salida_formateada;
    int longitud = mensaje_cifrado.length();
    for (int i = 0; i < longitud; i += 5) {
        if (i > 0) {
            salida_formateada += " ";
        }
        for (int j = 0; j < 5 && (i + j) < longitud; ++j) {
            salida_formateada += mensaje_cifrado[i + j];
        }
    }

    std::ofstream archivo("cifrado.txt");
    if (archivo.is_open()) {
        archivo << salida_formateada;
        archivo.close();
        std::cout << "[OK] Mensaje cifrado a \"cifrado.txt\" (" << mensaje_cifrado.length() << " letras)" << std::endl;
    }
}


