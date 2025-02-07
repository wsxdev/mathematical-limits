#include <iostream>
#include <string>
#include <cmath>
#include "tinyexpr.h"

using namespace std;

// Función para preprocesar la expresión y agregar '*' donde sea necesario
string preprocesarExpresion(const string& expresion) {
    string resultado;
    for (size_t i = 0; i < expresion.length(); ++i) {
        char actual = expresion[i];
        resultado += actual;

        // Si el carácter actual es un número y el siguiente es una variable (x, y, etc.)
        if (isdigit(actual) && (i + 1 < expresion.length()) && isalpha(expresion[i + 1])) {
            resultado += '*';  // Agrega el operador de multiplicación
        }
        // Si el carácter actual es una variable y el siguiente es un número
        else if (isalpha(actual) && (i + 1 < expresion.length()) && isdigit(expresion[i + 1])) {
            resultado += '*';  // Agrega el operador de multiplicación
        }
    }
    return resultado;
}

// Función para evaluar el límite de una función dada
double evaluarLimite(const string& expresion, double punto, double tolerancia = 1e-6) {
    // Variable para la función
    double x = punto;

    // Compilar la expresión
    te_variable vars[] = {{"x", &x}};  // Definimos la variable 'x'
    int error;
    te_expr* expr = te_compile(expresion.c_str(), vars, 1, &error);

    if (!expr) {
        cerr << "Error: No se pudo compilar la expresión." << endl;
        return nan("");
    }

    // Evaluar la función directamente en el punto dado
    double evaluacionDirecta = te_eval(expr);

    // Si la evaluación directa es válida, devolver ese valor
    if (!isnan(evaluacionDirecta) && !isinf(evaluacionDirecta)) {
        te_free(expr);  // Liberar memoria
        return evaluacionDirecta;
    }

    // Si la evaluación directa falla, intentar acercarse desde ambos lados
    x = punto - tolerancia;
    double izquierda = te_eval(expr);

    x = punto + tolerancia;
    double derecha = te_eval(expr);

    // Liberar memoria
    te_free(expr);

    // Si los valores son aproximadamente iguales, devolver el promedio
    if (abs(izquierda - derecha) < tolerancia) {
        return (izquierda + derecha) / 2;
    } else {
        return nan("");  // Indeterminado o no existe
    }
}

// Función principal
int main() {
    string expresion;
    double punto;

    system("clear");
    cout << "| CALCULO DE LIMITES MATEMATICOS |\n\n";
    cout << "Para insertar la funcion use 'x' como variable, por ejemplo: x^2 + 3*x - 1\n";
    cout << "Ingrese la funcion: ";
    getline(cin, expresion);

    // Guardar la expresión original para mostrarla en la salida
    string expresionOriginal = expresion;

    // Preprocesar la expresión para agregar '*' donde sea necesario
    expresion = preprocesarExpresion(expresion);

    cout << "Ingrese el punto al que tiende x: ";
    cin >> punto;

    double limite = evaluarLimite(expresion, punto);

    if (isnan(limite)) {
        cout << "El limite es indeterminado o no existe." << endl;
    } else {
        system("clear");
        cout << "RESULTADO\n";
        cout << "La funcion es: y = " << expresionOriginal << endl;  // Mostrar la expresión original
        cout << "El limite en el punto " << punto << " es: " << limite << endl;
    }

    return 0;
}