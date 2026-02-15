#include "includes.h"

#include "comprobaciones.h"
#include "rotor.h"
#include "descifrar.h"
#include "editar_rotores.h"
#include "cifrar.h"

int main() {


	while (true) {  // Bucle infinito hasta que se elija salir
		std::cout << "ENIGMA:" << std::endl;
		std::cout << "-------------------------------" << std::endl;
		std::cout << "1. Cifrar missatge" << std::endl;
		std::cout << "2. DesCifrar missatge" << std::endl;
		std::cout << "3. Editar rotores" << std::endl;
		std::cout << "4. Sortir" << std::endl;
		std::cout << "Elige una opcion: " << std::endl;

		std::string mensajeCifrar;
		int opcion;
		std::cin >> opcion;
		std::cin.ignore(1000, '\n'); // Limpia el buffer para que getline funcione correctamente



		switch (opcion) {
		case 1:  // Cifrar 
		{

			std::cout << "Introduce el mensaje a cifrar" << std::endl;
			std::getline(std::cin, mensajeCifrar);

			while (mensajeCifrar == "")
			{
				std::cout << "Error el mensaje no puede estar vacio";
				break;
			}

			std::string primera_posicion_rotor;
			std::cout << "Indica la posicion del primer rotor A-Z " << std::endl;
			std::getline(std::cin, primera_posicion_rotor);

			std::string segunda_posicion_rotor;
			std::cout << "Indica la posicion del segundo rotor (A-Z): " << std::endl;
			std::getline(std::cin, segunda_posicion_rotor);

			std::string tercera_posicion_rotor;
			std::cout << "Indica la posicion del tercer rotor (A-Z): " << std::endl;
			std::getline(std::cin, tercera_posicion_rotor);


			// Validación
			if (primera_posicion_rotor.length() != 1 || !esLetraMayuscula(primera_posicion_rotor[0]) ||
				segunda_posicion_rotor.length() != 1 || !esLetraMayuscula(segunda_posicion_rotor[0]) ||
				tercera_posicion_rotor.length() != 1 || !esLetraMayuscula(tercera_posicion_rotor[0])) {
				std::cout << "Error: Cada posicion debe ser exactamente una letra mayúscula." << std::endl;
				break;
			}

			int primera_posicion_indice = primera_posicion_rotor[0] - 'A';
			int segunda_posicion_indice
				= segunda_posicion_rotor[0] - 'A';
			int tercera_posicion_indice = tercera_posicion_rotor[0] - 'A';

			cifrar(mensajeCifrar, primera_posicion_indice, segunda_posicion_indice
				, tercera_posicion_indice);
			break;
		}



		case 2:  // Descifrar mensaje

		{
			std::string primera_posicion_rotor;
			std::cout << "Indica la posicion del primer rotor " << std::endl;
			std::getline(std::cin, primera_posicion_rotor);

			std::string segunda_posicion_rotor;
			std::cout << "Indica la posicion del segundo rotor " << std::endl;
			std::getline(std::cin, segunda_posicion_rotor);

			std::string tercera_posicion_rotor;
			std::cout << "Indica la posicion del tercer rotor " << std::endl;
			std::getline(std::cin, tercera_posicion_rotor);

			// Validacion de posiciones
			if (primera_posicion_rotor.length() != 1 || !esLetraMayuscula(primera_posicion_rotor[0]) ||
				segunda_posicion_rotor.length() != 1 || !esLetraMayuscula(segunda_posicion_rotor[0]) ||
				tercera_posicion_rotor.length() != 1 || !esLetraMayuscula(tercera_posicion_rotor[0])) {
				std::cout << "Error: Cada posicion debe ser exactamente una letra mayúscula." << std::endl;
				break;  // Volver al menú
			}

			// Convertir a índices y llamar a descifrar().
			int primera_posicion_indice = primera_posicion_rotor[0] - 'A';
			int segunda_posicion_indice
				= segunda_posicion_rotor[0] - 'A';
			int tercera_posicion_indice = tercera_posicion_rotor[0] - 'A';

			descifrar(primera_posicion_indice, segunda_posicion_indice
				, tercera_posicion_indice);
			break;

		}

		// Editar rotores
		case 3: {

			editar_rotor();
			break;

		}

		case 4:  // Saliendo
			std::cout << "Saliendo..." << std::endl;
			return 0;  // Salir del programa

		default:  // Opción inválida
			std::cout << "Opcion invalida. Intenta de nuevo." << std::endl;
			break;
		}

	}
	return 0;
}

