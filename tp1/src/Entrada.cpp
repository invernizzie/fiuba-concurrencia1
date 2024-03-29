#include "include/Entrada.h"

#include <cstdlib>
#include <unistd.h>
#include <time.h>
#include <exception>
#include <string>
#include <stdlib.h>

#include "include/constantes.h"
#include "include/Auto.h"
#include "logger.h"

Entrada :: Entrada(string nombre, int tiempoSimulacion) :
            tiempoSimulacion(tiempoSimulacion),
            nombre(nombre) {}

void Entrada :: ejecutar() {
    inicializar();
    recibirAutos();
}

void Entrada :: inicializar() {
    // Obtener tiempo de inicio de memoria compartida
    MemoriaCompartida<time_t> inicio;
    inicio.crear((char*)ARCHIVO_AUXILIAR, C_SHM_TIEMPO_INICIO);
    instanteFinal = inicio.leer() + this->tiempoSimulacion;

    srand (time(NULL) + getpid());
}

void Entrada :: recibirAutos() {
    while (instanteFinal > time(NULL)) {
        int autos = autosPorHora();
        stringstream ss;
        ss << "Entrada " << nombre << ": esta hora recibire " << autos << " autos";
        Logger::write(DEBUG, ss.str());
        for (; autos > 0; autos--) {
            try {
                estacionamiento.ocuparLugar();
                // Si hay lugar, se forkea un Auto

                Auto* _auto = new Auto();
                pid_t pIdAuto = _auto->iniciar();

                stringstream ss;
                ss << "Entrada " << nombre << ": dejo ingresar auto " << pIdAuto;
                Logger::write(DEBUG, ss.str());

            } catch (exception e) {
                // Si no, el auto se retira
                stringstream ss;
                ss << "Entrada " << nombre << ": no hay lugares libres, se retira un auto";
                Logger::write(DEBUG, ss.str());
            }
        }
        sleep(1);
    }
    stringstream ss;
    ss << "Entrada " << nombre << " finaliza la simulacion";
    Logger::write(DEBUG, ss.str());
}

unsigned Entrada :: autosPorHora() {
    return rand() % AUTOS_POR_HORA;
}
