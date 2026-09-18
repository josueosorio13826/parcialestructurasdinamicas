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
void determinarSeguridad(Elemento &elemento);

int main() {
    Elemento elementos[10];
    int cantidad;

    do {
        cout << "Cuantos elementos desea registrar (1-10): ";
        cin >> cantidad;

        if (cantidad < 1 || cantidad > 10) {
            cout << "Cantidad invalida. Intente nuevamente." << endl;
        }

    } while (cantidad < 1 || cantidad > 10);

   
    for (int i = 0; i < cantidad; i++) {
        cout << "\n--- REGISTRO DEL ELEMENTO "
             << i + 1 << " ---" << endl;

        registrarElemento(elementos[i]);
    }

    cout << "\nRegistro completado correctamente." << endl;

    
    Elemento *puntero = elementos;

    cout << "\n--- FACTORES Y ESTADOS DE SEGURIDAD ---" << endl;

    for (int i = 0; i < cantidad; i++) {
        float factor = calcularFactor(puntero);

        determinarSeguridad(*puntero);

        cout << "\nElemento: " << puntero->nombre << endl;
        cout << "Factor de utilizacion: " << factor << endl;
        cout << "Estado: " << puntero->estadoSeguridad << endl;

        puntero++;
    }

    return 0;
}

void registrarElemento(Elemento &elemento) {
    cout << "Codigo: ";
    cin >> elemento.codigo;

    cout << "Nombre: ";
    getline(cin >> ws, elemento.nombre);

    cout << "Longitud: ";
    cin >> elemento.longitud;

    for (int i = 0; i < 3; i++) {
        cout << "Carga " << i + 1 << ": ";
        cin >> elemento.cargas[i];
    }

    do {
        cout << "Capacidad maxima: ";
        cin >> elemento.capacidadMaxima;

        if (elemento.capacidadMaxima <= 0) {
            cout << "La capacidad debe ser mayor que cero." << endl;
        }

    } while (elemento.capacidadMaxima <= 0);

    elemento.factorUtilizacion = 0;
    elemento.estadoSeguridad = "SIN CALCULAR";
}

float calcularFactor(Elemento *elemento) {
    float sumaCargas = 0;

    for (int i = 0; i < 3; i++) {
        sumaCargas += elemento->cargas[i];
    }

    float cargaPromedio = sumaCargas / 3.0f;

    elemento->factorUtilizacion =
        cargaPromedio / elemento->capacidadMaxima;

    return elemento->factorUtilizacion;
}


void determinarSeguridad(Elemento &elemento) {
    if (elemento.factorUtilizacion <= 0.50f) {
        elemento.estadoSeguridad = "SEGURO";
    }
    else if (elemento.factorUtilizacion <= 0.80f) {
        elemento.estadoSeguridad = "PRECAUCION";
    }
    else if (elemento.factorUtilizacion <= 1.00f) {
        elemento.estadoSeguridad = "RIESGO";
    }
    else {
        elemento.estadoSeguridad = "SOBRECARGA";
    }
}