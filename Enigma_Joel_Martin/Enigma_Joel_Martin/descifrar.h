#pragma once


/**
 * @brief Descifra un mensaje utilizando tres rotores.
 *
 * La función lee los rotores desde archivos, pide un mensaje cifrado
 * y lo procesa letra por letra para obtener el mensaje original.
 * Para que funcione correctamente, las posiciones iniciales de los
 * rotores deben ser las mismas que se usaron al cifrar.
 */

void descifrar(int primera_posicion_indice, int segunda_posicion_indice, int tercera_posicion_indice);



