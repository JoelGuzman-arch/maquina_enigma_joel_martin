#include <iostream>
#include <fstream>
#include <string>
#include "comprobaciones.h"

void editar_rotor() {
    std::cout << "EDITAR ROTOR:" << std::endl;
    std::cout << "1. Rotor1.txt" << std::endl;
    std::cout << "2. Rotor2.txt" << std::endl;
    std::cout << "3. Rotor3.txt" << std::endl;
    std::cout << "4. Volver al menu principal" << std::endl;
    std::cout << "Elige rotor (1-4): ";

    int rotor_num;
    std::cin >> rotor_num;
    std::cin.ignore(1000, '\n'); // Limpia el buffer para que getline funcione correctamente

    if (rotor_num == 4) return;
    if (rotor_num < 1 || rotor_num > 3) {
        std::cout << "[ERROR] Opcion invalida." << std::endl;
        return;
    }

    std::string nombre_archivo;
    if (rotor_num == 1) nombre_archivo = "Rotor1.txt";
    else if (rotor_num == 2) nombre_archivo = "Rotor2.txt";
    else nombre_archivo = "Rotor3.txt";

    std::cout << "Nuevo cableado (26 letras A-Z únicas): ";
    std::string nuevo_cableado;
    std::getline(std::cin, nuevo_cableado);

    // REUTILIZA TU FUNCIÓN esRotorValido()
    if (!esRotorValido(nuevo_cableado)) {
        std::cout << "[ERROR] Permutación incorrecta — calen 26 lletres úniques A-Z" << std::endl;
        return;
    }

    std::cout << "Posición notch (letra A-Z, ENTER para Z): ";
    std::string letra_notch;
    std::getline(std::cin, letra_notch);

    char notch = 'Z';  // Por defecto
    if (!letra_notch.empty() && esLetraMayuscula(letra_notch[0])) {
        notch = letra_notch[0];
    }

    // GUARDAR AL ARCHIVO
    std::ofstream archivo(nombre_archivo);
    if (archivo.is_open()) {
        archivo << nuevo_cableado << std::endl;
        archivo << notch << std::endl;
        archivo.close();
        std::cout << "[OK] Rotor guardado en " << nombre_archivo << std::endl;
    }
    else {
        std::cout << "[ERROR] No se pudo guardar " << nombre_archivo << std::endl;
    }
}
