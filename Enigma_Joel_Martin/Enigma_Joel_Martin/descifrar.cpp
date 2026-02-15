#include "includes.h"
#include "rotor.h"
#include "descifrar.h"

/**
 * @brief Descifra un mensaje utilizando tres rotores.
 *
 * La función lee los rotores desde archivos, pide un mensaje cifrado
 * y lo procesa letra por letra para obtener el mensaje original.
 * Para que funcione correctamente, las posiciones iniciales de los
 * rotores deben ser las mismas que se usaron al cifrar.
 */

void descifrar(int primera_posicion_indice, int segunda_posicion_indice
    , int tercera_posicion_indice) {

    //  Lee los archivos de rotor
    std::string primer_rotor = leerRotor("Rotor1.txt");
    std::string segundo_rotor = leerRotor("Rotor2.txt");
    std::string tercer_rotor = leerRotor("Rotor3.txt");

    // Si algún rotor no se pudo leer correctamente, se cancela el proceso
    if (primer_rotor.empty() || segundo_rotor.empty() || tercer_rotor.empty()) {
        std::cout << "Error al cargar los rotors." << std::endl;
        return;
    }

    // Estos rotores se usan para hacer el proceso contrario al cifrado y así recuperar el mensaje original.


    std::string primer_rotor_inverso = crearInverso(primer_rotor);
    std::string segundo_rotor_inverso = crearInverso(segundo_rotor);
    std::string tercer_rotor_inverso = crearInverso(tercer_rotor);

    // Cambiado para Error 2: Extraer notches de los rotores originales (no inversos), sin operador ternario
    int pos_separador_primero = -1;
    for (int i = 0; i < primer_rotor.length(); ++i) {
        if (primer_rotor[i] == '|') {
            pos_separador_primero = i;
            break;
        }
    }

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

    int pos_separador_segundo = -1;
    for (int i = 0; i < segundo_rotor.length(); ++i) {
        if (segundo_rotor[i] == '|') {
            pos_separador_segundo = i;
            break;
        }
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

    int pos_separador_tercero = -1;
    for (int i = 0; i < tercer_rotor.length(); ++i) {
        if (tercer_rotor[i] == '|') {
            pos_separador_tercero = i;
            break;
        }
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

    // Cambiado para Error 3: Leer directamente a mensaje_procesado sin redundancia, aplicando filtro único
    std::string mensaje_procesado;
    std::ifstream archivo_entrada("cifrado.txt");
    if (archivo_entrada.is_open()) {
        std::string linea;
        while (std::getline(archivo_entrada, linea)) {
            for (int indice_caracter = 0; indice_caracter < linea.length(); ++indice_caracter) {
                char caracter_en_linea = linea[indice_caracter];
                char letra = toUpper(caracter_en_linea);
                if (letra >= 'A' && letra <= 'Z') {
                    mensaje_procesado += letra;
                }
            }
        }
        archivo_entrada.close();
    }
    else {
        std::cout << "Error, No se pudo abrir cifrado.txt" << std::endl;
        return;
    }

    // Descifrar letra por letra
    std::string mensaje_descifrado;
    int longitud_procesado = mensaje_procesado.length();

    for (int i = 0; i < longitud_procesado; i++) {
        char caracter = mensaje_procesado[i];

        // El primer rotor avanza siempre una posición
        primera_posicion_indice = (primera_posicion_indice + 1) % 26;

        // Cambiado para Error 2: Usar indice_notch_primero en lugar de hardcodeado
        if (primera_posicion_indice == indice_notch_primero) {
            segunda_posicion_indice
                = (segunda_posicion_indice
                    + 1) % 26;

            // Cambiado para Error 2: Usar indice_notch_segundo en lugar de hardcodeado
            if (segunda_posicion_indice
                == indice_notch_segundo) {
                tercera_posicion_indice = (tercera_posicion_indice + 1) % 26;
            }
        }

        // Cambiado para Error 3: Paso por rotores inversos en orden 3->2->1 con ajuste de offset para reversibilidad
        int entrada = caracter - 'A';

        int entrada_efectiva3 = (entrada + tercera_posicion_indice) % 26;
        int salida_mapeada3 = inverso_rotor_tercero[entrada_efectiva3] - 'A';
        int salida3 = (salida_mapeada3 - tercera_posicion_indice + 26) % 26;

        int entrada_efectiva2 = (salida3 + segunda_posicion_indice
            ) % 26;
        int salida_mapeada2 = inverso_rotor_segundo[entrada_efectiva2] - 'A';
        int salida2 = (salida_mapeada2 - segunda_posicion_indice
            + 26) % 26;

        int entrada_efectiva1 = (salida2 + primera_posicion_indice) % 26;
        int salida_mapeada1 = inverso_rotor_primero[entrada_efectiva1] - 'A';
        int salida1 = (salida_mapeada1 - primera_posicion_indice + 26) % 26;

        // Convierte el resultado final en una letra
        char letra_descifrada = 'A' + salida1;
        mensaje_descifrado += letra_descifrada;
    }

    // Proceso de guardado del archivo descifrado.txt
    std::ofstream archivo("descifrado.txt");
    if (archivo.is_open()) {
        archivo << mensaje_descifrado;
        archivo.close();
        std::cout << "[OK] Mensaje descifrado a \"descifrado.txt\" (" << mensaje_descifrado.length() << " letras)" << std::endl;
    }
}
