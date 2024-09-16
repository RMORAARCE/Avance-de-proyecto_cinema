#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
 
using namespace std;

struct Pelicula {
    string nombre;
    int ano;
    int duracion;
    string pais;
    string resena;
};

struct Sala {
    int numero;
    int cantidadButacas;
    double precio;
};

struct Horario {
    string fecha;
    string horaInicial;
    string horaFinal;
};

struct Reserva {
    int consecutivo;
    Pelicula pelicula;
    Sala sala;
    Horario horario;
    vector<vector<char>> butacas;
};

struct Venta {
    int consecutivo;
    string cedula;
    string tarjeta;
};

vector<Pelicula> peliculas;
vector<Sala> salas;
vector<Horario> horarios;
vector<Reserva> reservas;
vector<Venta> ventas;
int consecutivo = 1;

void mostrarMenu();
void agregarPelicula();
void agregarSala();
void agregarHorario();
void realizarReserva();
void realizarVenta();
void mostrarPeliculas();
void mostrarSalas();
void mostrarHorarios();
void mostrarReservas();
void mostrarVentas();
void mostrarButacas(const vector<vector<char>> &butacas);
bool esCedulaValida(const string &cedula);
bool esTarjetaValida(const string &tarjeta);

int main() {
    int opcion;
    do {
        mostrarMenu();
        cin >> opcion;
        switch(opcion) {
            case 1: agregarPelicula(); break;
            case 2: agregarSala(); break;
            case 3: agregarHorario(); break;
            case 4: realizarReserva(); break;
            case 5: realizarVenta(); break;
            case 6: mostrarPeliculas(); break;
            case 7: mostrarSalas(); break;
            case 8: mostrarHorarios(); break;
            case 9: mostrarReservas(); break;
            case 10: mostrarVentas(); break;
            case 0: cout << "Saliendo del sistema..." << endl; break;
            default: cout << "Opcion no valida" << endl; break;
        }
    } while (opcion != 0);
    return 0;
}

void mostrarMenu() {
    cout << "\n--- MENU ---\n";
    cout << "1. Agregar Pelicula\n";
    cout << "2. Agregar Sala\n";
    cout << "3. Agregar Horario\n";
    cout << "4. Realizar Reserva\n";
    cout << "5. Realizar Venta\n";
    cout << "6. Mostrar Peliculas\n";
    cout << "7. Mostrar Salas\n";
    cout << "8. Mostrar Horarios\n";
    cout << "9. Mostrar Reservas\n";
    cout << "10. Mostrar Ventas\n";
    cout << "0. Salir\n";
    cout << "Seleccione una opcion: ";
}

void agregarPelicula() {
    Pelicula p;
    cout << "Ingrese nombre de la pelicula: ";
    cin.ignore();
    getline(cin, p.nombre);
    cout << "Ingrese ano: ";
    cin >> p.ano;
    cout << "Ingrese duracion (min): ";
    cin >> p.duracion;
    cout << "Ingrese pais: ";
    cin.ignore();
    getline(cin, p.pais);
    cout << "Ingrese resena: ";
    getline(cin, p.resena);
    peliculas.push_back(p);
    cout << "Pelicula agregada exitosamente." << endl;
}

void agregarSala() {
    Sala s;
    cout << "Ingrese numero de la sala: ";
    cin >> s.numero;
    cout << "Ingrese cantidad de butacas: ";
    cin >> s.cantidadButacas;
    cout << "Ingrese precio: ";
    cin >> s.precio;
    salas.push_back(s);
    cout << "Sala agregada exitosamente." << endl;
}

void agregarHorario() {
    Horario h;
    cout << "Ingrese fecha (DD/MM/AAAA): ";
    cin >> h.fecha;
    cout << "Ingrese hora inicial (HH:MM): ";
    cin >> h.horaInicial;
    cout << "Ingrese hora final (HH:MM): ";
    cin >> h.horaFinal;
    horarios.push_back(h);
    cout << "Horario agregado exitosamente." << endl;
}

void realizarReserva() {
    if (peliculas.empty() || salas.empty() || horarios.empty()) {
        cout << "Debe agregar peliculas, salas y horarios antes de realizar una reserva." << endl;
        return;
    }

    Reserva r;
    int opcion;

    cout << "Seleccione una pelicula:\n";
    for (size_t i = 0; i < peliculas.size(); i++) {
        cout << i + 1 << ". " << peliculas[i].nombre << endl;
    }
    cin >> opcion;
    r.pelicula = peliculas[opcion - 1];

    cout << "Seleccione una sala:\n";
    for (size_t i = 0; i < salas.size(); i++) {
        cout << i + 1 << ". Sala " << salas[i].numero << " - " << salas[i].cantidadButacas << " butacas - " << salas[i].precio << " colones\n";
    }
    cin >> opcion;
    r.sala = salas[opcion - 1];

    cout << "Seleccione un horario:\n";
    for (size_t i = 0; i < horarios.size(); i++) {
        cout << i + 1 << ". " << horarios[i].fecha << " de " << horarios[i].horaInicial << " a " << horarios[i].horaFinal << endl;
    }
    cin >> opcion;
    r.horario = horarios[opcion - 1];

    r.butacas.resize(r.sala.cantidadButacas / 10, vector<char>(10, 'D'));

    mostrarButacas(r.butacas);

    int fila, columna;
    cout << "Ingrese la fila y columna de la butaca a reservar (fila columna): ";
    cin >> fila >> columna;

    if (r.butacas[fila][columna] == 'D') {
        r.butacas[fila][columna] = 'R';
        r.consecutivo = consecutivo++;
        reservas.push_back(r);
        cout << "Reserva realizada exitosamente. Su consecutivo es: " << r.consecutivo << endl;
    } else {
        cout << "Butaca no disponible." << endl;
    }
}

void realizarVenta() {
    if (reservas.empty()) {
        cout << "No hay reservas disponibles para realizar ventas." << endl;
        return;
    }

    int numConsecutivo;
    cout << "Ingrese el numero de consecutivo de la reserva: ";
    cin >> numConsecutivo;

    for (size_t i = 0; i < reservas.size(); i++) {
        if (reservas[i].consecutivo == numConsecutivo) {
            Venta v;
            v.consecutivo = numConsecutivo;

            string cedula, tarjeta;
            do {
                cout << "Ingrese cedula del cliente: ";
                cin >> cedula;
            } while (!esCedulaValida(cedula));
            v.cedula = cedula;

            do {
                cout << "Ingrese numero de tarjeta: ";
                cin >> tarjeta;
            } while (!esTarjetaValida(tarjeta));
            v.tarjeta = tarjeta;

            ventas.push_back(v);
            cout << "Venta realizada exitosamente." << endl;

            for (size_t f = 0; f < reservas[i].butacas.size(); f++) {
                for (size_t c = 0; c < reservas[i].butacas[f].size(); c++) {
                    if (reservas[i].butacas[f][c] == 'R') {
                        reservas[i].butacas[f][c] = 'V';
                    }
                }
            }
            return;
        }
    }
    cout << "Consecutivo no encontrado." << endl;
}

void mostrarPeliculas() {
    cout << "\n--- Peliculas ---\n";
    for (const auto& p : peliculas) {
        cout << "Nombre: " << p.nombre << "\nAno: " << p.ano << "\nDuracion: " << p.duracion << " min\nPais: " << p.pais << "\nResena: " << p.resena << "\n\n";
    }
}

void mostrarSalas() {
    cout << "\n--- Salas ---\n";
    for (const auto& s : salas) {
        cout << "Numero: " << s.numero << "\nCantidad de butacas: " << s.cantidadButacas << "\nPrecio: " << s.precio << " colones\n\n";
    }
}

void mostrarHorarios() {
    cout << "\n--- Horarios ---\n";
    for (const auto& h : horarios) {
        cout << "Fecha: " << h.fecha << "\nHora inicial: " << h.horaInicial << "\nHora final: " << h.horaFinal << "\n\n";
    }
}

void mostrarReservas() {
    cout << "\n--- Reservas ---\n";
    for (const auto& r : reservas) {
        cout << "Consecutivo: " << r.consecutivo << "\nPelicula: " << r.pelicula.nombre << "\nSala: " << r.sala.numero << "\nHorario: " << r.horario.fecha << " de " << r.horario.horaInicial << " a " << r.horario.horaFinal << "\n\n";
        mostrarButacas(r.butacas);
    }
}

void mostrarVentas() {
    cout << "\n--- Ventas ---\n";
    for (const auto& v : ventas) {
        cout << "Consecutivo: " << v.consecutivo << "\nCedula: " << v.cedula << "\nTarjeta: " << v.tarjeta << "\n\n";
    }
}

void mostrarButacas(const vector<vector<char>> &butacas) {
    cout << "Butacas:\n";
    for (const auto& fila : butacas) {
        for (const auto& butaca : fila) {
            cout << butaca << " ";
        }
        cout << endl;
    }
}

bool esCedulaValida(const string &cedula) {
    if (cedula.length() != 9) {
        cout << "Cedula invalida. Debe tener 9 digitos.\n";
        return false;
    }
    for (char c : cedula) {
        if (!isdigit(c)) {
            cout << "Cedula invalida. Debe contener solo numeros.\n";
            return false;
        }
    }
    return true;
}

bool esTarjetaValida(const string &tarjeta) {
    if (tarjeta.length() != 16) {
        cout << "Tarjeta invalida. Debe tener 16 digitos.\n";
        return false;
    }
    for (char c : tarjeta) {
        if (!isdigit(c)) {
            cout << "Tarjeta invalida. Debe contener solo numeros.\n";
            return false;
        }
    }
    return true;
}
