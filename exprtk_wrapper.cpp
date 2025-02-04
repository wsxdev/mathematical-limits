#include <iostream>
#include <string>
#include <cmath>
#include "exprtk.hpp"

using namespace std;

// Función para evaluar el límite de una función dada
double evaluarLimite(const string& expresion, double punto, double tolerancia = 1e-6) {
    // Se define un tipo de expresión y un símbolo para la variable 'x'
    typedef exprtk::symbol_table<double> tablaSimbolos_t;
    typedef exprtk::expression<double> expresion_t;
    typedef exprtk::parser<double> parser_t;

    double x; // Variable de la función
    tablaSimbolos_t tablaSimbolos;
    tablaSimbolos.add_variable("x", x); // Se agrega 'x' a la tabla de símbolos

    expresion_t expr;
    expr.register_symbol_table(tablaSimbolos); // Se registra la tabla de símbolos

    parser_t parser;
    if (!parser.compile(expresion, expr)) {
        cerr << "Error: No se pudo compilar la expresion." << endl;
        return nan("");
    }

    // Se intenta evaluar la función directamente en el punto dado
    x = punto;
    double evaluacionDirecta = expr.value();

    // Si la evaluación directa es válida, se devuelve ese valor
    if (!isnan(evaluacionDirecta) && !isinf(evaluacionDirecta)) {
        return evaluacionDirecta;
    }

    // Si la evaluación directa falla, se intenta acercar desde ambos lados
    x = punto - tolerancia;
    double izquierda = expr.value();

    x = punto + tolerancia;
    double derecha = expr.value();

    // Si los valores son aproximadamente iguales, se devuelve el promedio
    if (abs(izquierda - derecha) < tolerancia) {
        return (izquierda + derecha) / 2;
    } else {
        return nan(""); // Indeterminado o no existe
    }
}