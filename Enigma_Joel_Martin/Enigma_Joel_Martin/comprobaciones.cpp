#include "includes.h"
#include "comprobaciones.h"

bool esRotorValido(const std::string& rotor) {
    if (rotor.length() != 26) return false;

    bool letras_vistas[26] = { false };

    for (int indice_caracter = 0; indice_caracter < 26; ++indice_caracter) {
        char caracter_rotor = rotor[indice_caracter];

        if (!esLetraMayuscula(caracter_rotor)) return false;

        int indice_letra = caracter_rotor - 'A';

        if (letras_vistas[indice_letra]) return false;

        letras_vistas[indice_letra] = true;
    }

    for (int indice_letra = 0; indice_letra < 26; ++indice_letra) {
        if (!letras_vistas[indice_letra]) return false;
    }

    return true;
}
