#include "include/logger.h"

#include <time.h>

using namespace std;

// Para imprimir correctamente el modo
std::ostream& operator<<( ostream& ofs, TipoLog modo )
{
   switch (modo)
   {
      case INFO: ofs << "INFO "; break;
      case DEBUG: ofs << "DEBUG"; break;
      case WARNING: ofs << "WARN "; break;
      case ERROR: ofs << "ERROR"; break;
      case FATAL: ofs << "FATAL"; break;
   }
   return ofs;
}

TipoLog Logger :: modo = MODO_LOG_DEFAULT;

Logger& Logger::getInstance() {
    static Logger* instance = new Logger();
    return *instance;
}

void Logger :: initialize(TipoLog mode, string logFile) {
    getInstance().lock = new LockFile((char*)logFile.c_str());
    getInstance().modo = mode;
    getInstance().openLogFile(logFile);
}

void Logger :: write(TipoLog modo, string mensaje) {
    getInstance().writeToLogFile(modo, mensaje);
}

void Logger::openLogFile(string logFile)
{
	fd.open( logFile.c_str(), ofstream::out);
}

void Logger::writeToLogFile(TipoLog modo, string mensaje) {
    if (modo >= this->modo) {
        lock->tomarLock();
        stringstream msj;
        //msj << "[" << fechaFormateada() << " : "  << modo << "] " << mensaje << endl;
        fd << "[" << fechaFormateada() << " : "  << modo << "] " << mensaje << endl;
        lock->liberarLock();
    }
}

string Logger::fechaFormateada() {
        time_t ahora = time(NULL);
        string fecha = ctime(&ahora);
        return fecha.substr(0, fecha.length() - 1);
}

Logger::~Logger(){
    delete lock;
    fd.close();
}

