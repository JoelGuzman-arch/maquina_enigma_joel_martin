
#pragma once
#include "includes.h"


/**
 * @brief Cifra un mensaje utilizando tres rotores.
 *
 * La función lee los rotores desde archivos, toma un mensaje en texto plano
 * y lo procesa letra por letra para obtener el mensaje cifrado.
 * Las posiciones iniciales de los rotores deben ser guardadas para
 * poder descifrar el mensaje posteriormente.
 */

tercera_posicion_indice

void cifrar(std::string mensaje_original, int primera_posicion_indice, int segunda_posicion_indice
	, int tercera_posicion_indice);

