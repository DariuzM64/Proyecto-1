#include<iostream>
#include<string>
#include<vector>
#include<map>

using namespace std;

struct Reservacion {
    string codigo;
    string nombre;
    string fecha;
    string destino;
    int puesto;
    double costo;
    bool cancelada;
};

vector<Reservacion> reservaciones;
map<string, vector<string>> autobuses = {{"Valencia", vector<string>(40, "")}, {"Caracas", vector<string>(40, "")}, {"Maracay", vector<string>(40, "")}, {"Anzoategui", vector<string>(40, "")}};
map<string, map<string, int>> reservacionesPorDia;

string generarCodigo() {
    return "RES" + to_string(reservaciones.size() + 1);
}

double calcularCosto(string destino) {
    if (destino == "Valencia") {
        return 10.0;
    } else if (destino == "Caracas") {
        return 15.0;
    } else if (destino == "Maracay") {
        return 12.0;
    } else if (destino == "Anzoategui") {
        return 20.0;
    } else {
        return 0.0;
    }
}

void bienvenida() {
    cout << "Bienvenido a la aplicacion de reservacion de boletos de Expresos Lara. Desarrollado por DARIO MENDOZA.\n";
}

void mostrarReservacion(Reservacion r) {
	cout << "///////////////////////////\n";
    cout << "///////////////////////////\n";
    cout << "Codigo: " << r.codigo << "\n";
    cout << "Nombre: " << r.nombre << "\n";
    cout << "Fecha: " << r.fecha << "\n";
    cout << "Destino: " << r.destino << "\n";
    cout << "Puesto: " << r.puesto << "\n";
}

void imprimirTicket(Reservacion r) {
    cout << "--------- TICKET ---------\n";
    mostrarReservacion(r);
    cout << "Costo: " << r.costo << "\n";
    cout << "--------------------------\n";
}

void buscarReservacion(string codigo) {
    for (Reservacion r : reservaciones) {
        if (r.codigo == codigo) {
            mostrarReservacion(r);
            return;
        }
    }
    cout << "No se encontro ninguna reservacion con el codigo proporcionado.\n";
}

void cancelarReservacion(string codigo) {
    for (Reservacion &r : reservaciones) {
        if (r.codigo == codigo) {
            r.cancelada = true;
            autobuses[r.destino][r.puesto - 1] = "";
            reservacionesPorDia[r.fecha][r.destino]--;
            cout << "Reservacion cancelada exitosamente.\n";
            return;
        }
    }
    cout << "No se encontro ninguna reservacion con el codigo proporcionado.\n";
}

void mostrarReservacionesCanceladas() {
    for (Reservacion r : reservaciones) {
        if (r.cancelada) {
            mostrarReservacion(r);
        }
    }
}

void mostrarMontoVentas() {
    double total = 0;
    for (Reservacion r : reservaciones) {
        if (!r.cancelada) {
            total += r.costo;
        }
    }
    cout << "El monto total de las ventas del dia es: " << total << "\n";
}

void mostrarReservacionesPorDestino(string destino) {
    for (Reservacion r : reservaciones) {
        if (r.destino == destino) {
            mostrarReservacion(r);
        }
    }
}

int asignarPuesto(string destino) {
    for (int i = 0; i < 40; i++) {
        if (autobuses[destino][i] == "") {
            return i + 1;
        }
    }
    return -1;
}

void agregarReservacion() {
    Reservacion r;
    cout << "Por favor, introduce el nombre del pasajero: ";
    cin >> r.nombre;
    cout << "Por favor, introduce la fecha de salida (formato DD/MM/AAAA): ";
    cin >> r.fecha;
    cout << "Por favor, introduce el destino (Valencia, Caracas, Maracay, Anzoategui): ";
    cin >> r.destino;
    if (reservacionesPorDia[r.fecha][r.destino] >= 40) {
        cout << "Lo siento, ya se han hecho todas las reservaciones posibles para el destino seleccionado en la fecha dada.\n";
        return;
    }
    r.codigo = generarCodigo();
    r.costo = calcularCosto(r.destino);
    r.puesto = asignarPuesto(r.destino);
    if (r.puesto == -1) {
        cout << "Lo siento, todos los puestos estan ocupados para el destino seleccionado.\n";
        return;
    }
    autobuses[r.destino][r.puesto - 1] = r.codigo;
    r.cancelada = false;
    reservaciones.push_back(r);
    reservacionesPorDia[r.fecha][r.destino]++;
    cout << "Reservacion agregada exitosamente.\n";
    imprimirTicket(r);
}

void menu() {
    int opcion;
    do {
    	cout <<"///////////////////////////\n";
        cout << "1. Agregar reservacion\n";
        cout << "2. Buscar reservacion\n";
        cout << "3. Cancelar reservacion\n";
        cout << "4. Mostrar reservaciones canceladas\n";
        cout << "5. Mostrar monto de ventas del dia\n";
        cout << "6. Mostrar reservaciones por destino\n";
        cout << "7. Salir\n";
        cout <<"///////////////////////////\n";
        cout << "Por favor, elige una opcion: ";
        cin >> opcion;
        switch (opcion) {
            case 1:
                agregarReservacion();
                break;
            case 2: {
                string codigo;
                cout << "Por favor, introduce el codigo de la reservacion: ";
                cin >> codigo;
                buscarReservacion(codigo);
                break;
            }
            case 3: {
                string codigo;
                cout << "Por favor, introduce el codigo de la reservacion a cancelar: ";
                cin >> codigo;
                cancelarReservacion(codigo);
                break;
            }
            case 4:
                mostrarReservacionesCanceladas();
                break;
            case 5:
                mostrarMontoVentas();
                break;
            case 6: {
                string destino;
                cout << "Por favor, introduce el destino: ";
                cin >> destino;
                mostrarReservacionesPorDestino(destino);
                break;
            }
            case 7:
                cout << "Gracias por usar nuestra aplicacion!\n";
                break;
            default:
                cout << "Opcion no valida. Por favor, elige una opcion del menu.\n";
        }
    } while (opcion != 7);
}

int main() {
    bienvenida();
    menu();
    return 0;
}

