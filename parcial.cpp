#include <iostream>
#include <string>
using namespace std;

struct Elemento {
    string codigo;
    string nombre;
    float longitud;
    float cargas[3];
    float capacidadMaxima;
    float factorUtilizacion;
    string estadoSeguridad;
};

void registrarElemento(Elemento &elemento);
float calcularFactor(Elemento *elemento);

int main () {

    Elemento elementos[10];
    int cantidad;

    do {
        cout << "Cuantos elementos desea registrar (1-10): ";
        cin >> cantidad;

        if (cantidad < 1 || cantidad > 10) {
            cout << "Cantidad invalida. Intente nuevamente." << endl;
        }

    } while (cantidad < 1 || cantidad > 10);
    
    cout << "Cantidad registrada correctamente: " << cantidad << endl;
    for (int i = 0; i < cantidad; i++) {
    cout << "\n--- Registro del elemento " << i + 1 << " ---" << endl;
    registrarElemento(elementos[i]);
}

cout << "\nRegistro completado correctamente." << endl;
Elemento *puntero = elementos;

    cout << "\n--- FACTORES DE UTILIZACION ---" << endl;

    for (int i = 0; i < cantidad; i++) {
        float factor = calcularFactor(puntero);

        cout << "Elemento: " << puntero->nombre << endl;
        cout << "Factor de utilizacion: " << factor << endl;

        puntero++;
    }
    return 0;
}

void registrarElemento(Elemento &elemento) {
cout << "Codigo: ";
    cin >> elemento.codigo;

    cin.ignore();

    cout << "Nombre: ";
    getline(cin, elemento.nombre);

    cout << "Longitud: ";
    cin >> elemento.longitud;

    for (int i = 0; i < 3; i++) {
        cout << "Carga " << i + 1 << ": ";
        cin >> elemento.cargas[i];
    }

    cout << "Capacidad maxima: ";
    cin >> elemento.capacidadMaxima;

    elemento.factorUtilizacion = 0;
    elemento.estadoSeguridad = "SIN CALCULAR";
}

float calcularFactor(Elemento *elemento) {
    float sumaCargas = 0;

    for (int i = 0; i < 3; i++) {
        sumaCargas += elemento->cargas[i];
    }

    float cargaPromedio = sumaCargas / 3.0;

    elemento->factorUtilizacion =
        cargaPromedio / elemento->capacidadMaxima;

    return elemento->factorUtilizacion;
}




