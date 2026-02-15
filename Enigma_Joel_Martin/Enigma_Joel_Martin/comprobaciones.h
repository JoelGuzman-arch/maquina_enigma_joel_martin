#pragma once

#include <string>

inline bool esLetraMayuscula(char c) {
    return c >= 'A' && c <= 'Z';
}

bool esRotorValido(const std::string& rotor);

