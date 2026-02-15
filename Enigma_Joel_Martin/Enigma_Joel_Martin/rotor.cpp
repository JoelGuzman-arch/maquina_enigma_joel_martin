#include "includes.h"
#include "comprobaciones.h"
#include "rotor.h"

// Cambiado para evitar referencias: Parámetro pasado por valor en lugar de const std::string&
std::string leerRotor(std::string nombre_archivo) {
    std::ifstream archivo_rotor(nombre_archivo);

    if (!archivo_rotor.is_open()) {
        std::cerr << "Error: No se pudo abrir el archivo " << nombre_archivo << std::endl;
        return "";
    }

    std::string cableado_rotor;
    std::getline(archivo_rotor, cableado_rotor);

    std::string linea_notch;
    std::getline(archivo_rotor, linea_notch);

    char notch_leida;

    if (linea_notch.empty() || linea_notch.length() != 1 || !esLetraMayuscula(linea_notch[0])) {
        notch_leida = 'Z';
    }
    else {
        notch_leida = linea_notch[0];
    }

    archivo_rotor.close();

    if (!esRotorValido(cableado_rotor)) {
        std::cerr << "Error: El rotor en " << nombre_archivo << " no es valido (debe ser 26 letras mayusculas)." << std::endl;
        return "";
    }

    return cableado_rotor + "|" + notch_leida;
}

// Cambiado para evitar referencias: Parámetro pasado por valor en lugar de const std::string&
std::string crearInverso(std::string rotor) {
    int pos_pipe = -1;
    for (int i = 0; i < rotor.length(); ++i) {
        if (rotor[i] == '|') {
            pos_pipe = i;
            break;
        }
    }
    std::string solo_cableado;
    if (pos_pipe != -1) {
        for (int i = 0; i < pos_pipe; ++i) {
            solo_cableado += rotor[i];
        }
    }
    else {
        solo_cableado = rotor;
    }

    std::string rotor_inverso(26, ' ');

    for (int indice_posicion = 0; indice_posicion < 26; ++indice_posicion) {
        int salida_original = solo_cableado[indice_posicion] - 'A';
        rotor_inverso[salida_original] = 'A' + indice_posicion;
    }

    return rotor_inverso;
}

char toUpper(char caracter_entrada) {
    if (caracter_entrada >= 'a' && caracter_entrada <= 'z') {
        return caracter_entrada - 'a' + 'A';
    }
    return caracter_entrada;
}

