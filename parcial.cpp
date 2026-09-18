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

// Prototipos
void registrarElemento(Elemento &elemento);
float calcularFactor(Elemento *elemento);
void determinarSeguridad(Elemento &elemento);

Elemento* obtenerElementoCritico(
    Elemento elementos[],
    int cantidad
);

int main() {
    Elemento elementos[10];
    int cantidad;

    // Validación de la cantidad
    do {
        cout << "Cuantos elementos desea registrar (1-10): ";
        cin >> cantidad;

        if (cantidad < 1 || cantidad > 10) {
            cout << "Cantidad invalida. Intente nuevamente." << endl;
        }

    } while (cantidad < 1 || cantidad > 10);

    // Registro de los elementos
    for (int i = 0; i < cantidad; i++) {
        cout << "\n--- REGISTRO DEL ELEMENTO "
             << i + 1 << " ---" << endl;

        registrarElemento(elementos[i]);
    }

    // Cálculo mediante recorrido con punteros
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

    // Obtener un puntero al elemento más comprometido
    Elemento *elementoCritico =
        obtenerElementoCritico(elementos, cantidad);

    // Mostrar toda la información del elemento crítico
    cout << "\n========================================" << endl;
    cout << "ELEMENTO MAS COMPROMETIDO" << endl;
    cout << "========================================" << endl;

    cout << "Codigo: " << elementoCritico->codigo << endl;
    cout << "Nombre: " << elementoCritico->nombre << endl;
    cout << "Longitud: " << elementoCritico->longitud << endl;

    for (int i = 0; i < 3; i++) {
        cout << "Carga " << i + 1 << ": "
             << elementoCritico->cargas[i] << " N" << endl;
    }

    cout << "Capacidad maxima: "
         << elementoCritico->capacidadMaxima << " N" << endl;

    cout << "Factor de utilizacion: "
         << elementoCritico->factorUtilizacion << endl;

    cout << "Estado de seguridad: "
         << elementoCritico->estadoSeguridad << endl;

    return 0;
}

// Registrar un elemento
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

// Calcular el factor mediante un puntero
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

// Determinar el estado de seguridad
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

// Encontrar el elemento con el factor más alto
Elemento* obtenerElementoCritico(
    Elemento elementos[],
    int cantidad
) {
    Elemento *critico = &elementos[0];
    Elemento *actual = &elementos[1];

    for (int i = 1; i < cantidad; i++) {
        if (actual->factorUtilizacion >
            critico->factorUtilizacion) {

            critico = actual;
        }

        actual++;
    }

    return critico;
}