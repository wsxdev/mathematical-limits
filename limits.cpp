#include <iostream>
#include <string>

// Declaración de la función definida en exprtk_wrapper.cpp
double evaluarLimite(const std::string& expresion, double punto, double tolerancia = 1e-6);

int main() {
    std::string expresion;
    double punto;

    system("clear");
    std::cout << "| CALCULO DE LIMITES MATEMATICOS |\n\n";
    std::cout << "Para insertar la funcion use 'x' como variable, por ejemplo: x^2 + 3x - 1\n";
    std::cout << "Ingrese la funcion: ";
    std::getline(std::cin, expresion);

    std::cout << "Ingrese el punto al que tiende x: ";
    std::cin >> punto;

    double limite = evaluarLimite(expresion, punto);

    if (std::isnan(limite)) {
        std::cout << "El limite es indeterminado o no existe." << std::endl;
    } else {
        system("clear");
        std::cout << "RESULTADO\n";
        std::cout << "La funcion es: y = " << expresion << std::endl; 
        std::cout << "El limite en el punto " << punto << " es: " << limite << std::endl;
    }

    return 0;
}