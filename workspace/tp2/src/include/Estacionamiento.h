#ifndef ESTACIONAMIENTO_H
#define ESTACIONAMIENTO_H

#include <vector>
#include <typeinfo>
#include <exception>
#include <sstream>

#include "logger.h"
#include "Mensajes.h"
#include "MemoriaCompartida.h"

using namespace std;

class EstacionamientoCompleto : public exception { };

class LugarOcupado : public exception { };

class Estacionamiento {

    public:
        Estacionamiento(int capacidad, int valorHora);
        virtual ~Estacionamiento();
        bool reservarLugar();
        unsigned asignarPosicionLibre();
        void liberarLugar();
        void cobrarYLiberarPosicion(unsigned nroLugar, unsigned duracionEstadia);
        EstadoEstacionamiento estadoActual();
        bool estaCerrado();
        void cerrarEntrada();
        void cerrarSalida();
        void cerrarAdministrador();

    private:
        int capacidad;
        int valorHora;
        int lugaresLibres;
        int facturacion;
        int entradasActivas;
        int salidasActivas;
        bool administradorActivo;
        vector<unsigned> posicionesLibres;
};

#endif // ESTACIONAMIENTO_H
