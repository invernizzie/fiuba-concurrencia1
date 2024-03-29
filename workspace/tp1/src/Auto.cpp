#include "include/Auto.h"

#include <cstdlib>
#include <unistd.h>
#include <time.h>

#include "include/logger.h"

Auto :: Auto() {
    srand (time(NULL) + getpid());
}

void Auto :: ejecutar() {
    buscarLugar();
    sleep(determinarEspera());
    liberarLugar();
    pagar();
    estacionamiento.salir(determinarSalida());
}

// Estrategia: comienza en posicion 0, mira una a una
// Si llega al final vuelve a empezar
void Auto :: buscarLugar() {
    stringstream ss;
    ss << "Auto " << getpid() << ": buscando lugar";
    Logger::write(DEBUG, ss.str());

    int cantidad = estacionamiento.getCapacidad();
    bool encontrado = false;
    posicion = 0;
    while (!encontrado) {
        try {
            estacionamiento.ocupar(posicion);

            stringstream ss;
            ss << "Auto " << getpid() << ": ocupo lugar " << posicion;
            Logger::write(DEBUG, ss.str());

            encontrado = true;
        } catch (exception& e) {
            stringstream ss;
            ss << "Auto " << getpid() << ": lugar " << posicion << " ocupado, sigo buscando";
            Logger::write(DEBUG, ss.str());

            posicion = (posicion + 1) % cantidad;
        }
    }
}

void Auto :: liberarLugar() {
    stringstream ss;
    ss << "Auto " << getpid() << ": libero lugar " << posicion;
    Logger::write(DEBUG, ss.str());

    estacionamiento.liberar(posicion);
}

unsigned Auto :: determinarEspera() {
    espera = rand() % (ESTADIA_MAXIMA - 1) + 1;
    return espera;
}

void Auto :: pagar() {
    // Esto seria el pago
    estacionamiento.registrarPago(espera * estacionamiento.getValorHora() );

    stringstream ss;
    ss << "Auto " << getpid() << ": se retira";
    Logger::write(DEBUG, ss.str());
}
