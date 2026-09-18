#include <iostream>
#include <iomanip>
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

Elemento* obtenerElementoCritico(
    Elemento elementos[],
    int cantidad
);

void aumentarCargas(
    Elemento &elemento,
    float porcentaje
);

int main() {
    Elemento elementos[10];
    int cantidad;

    cout << fixed << setprecision(2);

    
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

    Elemento *puntero = elementos;

    cout << "\n--- FACTORES Y ESTADOS ---" << endl;

    for (int i = 0; i < cantidad; i++) {
        calcularFactor(puntero);
        determinarSeguridad(*puntero);

        cout << "\nElemento: " << puntero->nombre << endl;
        cout << "Factor de utilizacion: "
             << puntero->factorUtilizacion << endl;
        cout << "Estado: "
             << puntero->estadoSeguridad << endl;

        puntero++;
    }

   
    Elemento *elementoCritico =
        obtenerElementoCritico(elementos, cantidad);

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

    float porcentaje;

    do {
        cout << "\nPorcentaje de incremento para el elemento critico: ";
        cin >> porcentaje;

        if (porcentaje < 0) {
            cout << "El porcentaje no puede ser negativo." << endl;
        }

    } while (porcentaje < 0);

    aumentarCargas(*elementoCritico, porcentaje);

    calcularFactor(elementoCritico);
    determinarSeguridad(*elementoCritico);

    cout << "\n========================================" << endl;
    cout << "RESULTADO DESPUES DEL INCREMENTO" << endl;
    cout << "========================================" << endl;

    cout << "Codigo: " << elementoCritico->codigo << endl;
    cout << "Nombre: " << elementoCritico->nombre << endl;

    for (int i = 0; i < 3; i++) {
        cout << "Nueva carga " << i + 1 << ": "
             << elementoCritico->cargas[i] << " N" << endl;
    }

    cout << "Capacidad maxima: "
         << elementoCritico->capacidadMaxima << " N" << endl;

    cout << "Nuevo factor de utilizacion: "
         << elementoCritico->factorUtilizacion << endl;

    cout << "Nuevo estado de seguridad: "
         << elementoCritico->estadoSeguridad << endl;

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


Elemento* obtenerElementoCritico(
    Elemento elementos[],
    int cantidad
) {
    Elemento *critico = elementos;

    for (
        Elemento *actual = elementos + 1;
        actual < elementos + cantidad;
        actual++
    ) {
        if (actual->factorUtilizacion >
            critico->factorUtilizacion) {

            critico = actual;
        }
    }

    return critico;
}


void aumentarCargas(
    Elemento &elemento,
    float porcentaje
) {
    float multiplicador = 1.0f + porcentaje / 100.0f;

    for (int i = 0; i < 3; i++) {
        elemento.cargas[i] =
            elemento.cargas[i] * multiplicador;
    }
}