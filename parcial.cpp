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

    return 0;
}



