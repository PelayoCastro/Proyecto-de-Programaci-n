#ifndef ProyectosProgramacionHeader_h
#define ProyectosProgramacionHeader_h

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <stdexcept>
#include <cmath>
#include <algorithm>
#include <iomanip> 

using namespace std;

// Constantes
float COSTE_POR_KM = 0.2;
float SALARIO_EMPLEADO = 1500.0;
int NUM_CIUDADES = 20;

enum class Tipo { CONDUCTOR, REPARTIDOR };  

// CLASES
// La clase fecha es se utiliza para otras clases
class Fecha {
public:
    int day, month, year;
    Fecha(int d, int m, int y) : day(d), month(m), year(y) {}
};
// Struct para las coordenadas, se utilizan para un atributo de la clase Ciudad
struct Coordenadas {
    float x;
    float y;
};
// Clase ciudad, habrá 20 objetos de esta clase
class Ciudad {
private:
    Coordenadas coordenadas;
    bool esAlmacen;
    float distanciaAlmacen;

public:
    // Como el constructor necesita el dato de distanciaAlmacen que se deriva de las coordendas de 2 ciduades, es necesario inicializarlo y luego cambiarlo
    Ciudad(float x, float y, bool almacen) : coordenadas{x, y}, esAlmacen(almacen), distanciaAlmacen(0.0) {}
    // Getters
    Coordenadas getCoordenadas() const { return coordenadas; }
    bool getEsAlmacen() const { return esAlmacen; }
    float getDistanciaAlmacen() const { return distanciaAlmacen; }

    // Esta función actualiza el valor de distanciaAlmacen
    void calcularDistanciaAlmacen(const Coordenadas& almacenCoordenadas) {
        if (!esAlmacen) {
            float dx = coordenadas.x - almacenCoordenadas.x;
            float dy = coordenadas.y - almacenCoordenadas.y;
            distanciaAlmacen = sqrt(dx * dx + dy * dy);
        }
    }
};
// A continuación la clase abstracta persona, de la que heredarán las clases Cliente y Empleado
class Persona {
protected:
    string nombre;
    string apellido1;
    string apellido2;
    Fecha fechaNacimiento;
    long long int numeroTelefonico;  
    Ciudad ciudad;

public:
    // Constructor
    Persona(const string& n, const string& a1, const string& a2,
            const Fecha& fn, long long int tel, const Ciudad& c)  
        : nombre(n), apellido1(a1), apellido2(a2), 
          fechaNacimiento(fn), numeroTelefonico(tel), ciudad(c) {}

    // Destructor virtual
    virtual ~Persona() = default;

    // Método virtual para mostrar los datos de Persona
    virtual void mostrar() const = 0;

    // Getters
    string getNombre() const {
        return nombre;
    }

    string getApellido1() const {
        return apellido1;
    }

    string getApellido2() const {
        return apellido2;
    }

    Fecha getFechaNacimiento() const {
        return fechaNacimiento;
    }

    long long int getNumeroTelefonico() const {
        return numeroTelefonico;
    }

    Ciudad getCiudad() const {
        return ciudad;
    }
};
// Habrá 5 objetos de la clase producto
// Clase derivada cliente, que hereda de Persona
class Cliente : public Persona {
private:
    string clienteID;  // El único atributo único de Cliente. El resto son heredados

public:
    // Constructor
    Cliente(const string& id, const string& n, const string& a1, const string& a2, 
            const Fecha& fn, int tel, const Ciudad& c)
        : Persona(n, a1, a2, fn, tel, c), clienteID(id) {}

    // Mostramos la información de clientes
    void mostrar() const {
        cout << "Cliente ID: " << clienteID << endl;
        cout << "Nombre: " << nombre << " " << apellido1 << " " << apellido2 << endl;
    }

    // Getter
    string getID() const { 
        return clienteID; 
    }
};
// Clase derivada Empleado, que hereda de Persona
class Empleado : public Persona {
private:
    string empleadoID; 
    Fecha fechaIncorporacion;
    Tipo tipo;

public:
    Empleado(const string& id, const string& n, const string& a1, const string& a2,
             const Fecha& fn, int tel, const Ciudad& c, const Fecha& fi, Tipo t)
        : Persona(n, a1, a2, fn, tel, c), empleadoID(id),
          fechaIncorporacion(fi), tipo(t) {}

    void mostrar() const {
        cout << "Empleado ID: " << empleadoID << endl;
        cout << "Nombre: " << nombre << " " << apellido1 << " " << apellido2 << endl;
        cout << "Tipo: " << (tipo == Tipo::CONDUCTOR ? "Conductor" : "Repartidor") << endl;
    }

    string getID() const { return empleadoID; }
    Tipo getTipo() const { return tipo; }
};
// Clase Producto
class Producto {
private:
    string nombreProducto;
    int cantidadDisponible;
    float precio;

public:
    Producto(const string& nom, int cant, float prec) 
        : nombreProducto(nom), cantidadDisponible(cant), precio(prec) {}

    // Getters y setters
    string getNombre() const { return nombreProducto; }
    int getCantidad() const { return cantidadDisponible; }
    float getPrecio() const { return precio; }
    
    void setCantidad(int nuevaCantidad) {
        if (nuevaCantidad < 0) throw runtime_error("Cantidad disponible no puede ser negativa.");
        cantidadDisponible = nuevaCantidad;
    }
};

// MÉTODOS
// La siguiente función lee la información del fichero de Ciudades
vector<Ciudad> leerCiudades(const string& nombreFichero) {
    // Creamos un vector de ciudades
    vector<Ciudad> ciudades;
    // Abrimos el flujo de salida de información del fichero
    ifstream archivo(nombreFichero);
    // Lanzamos un mesaje de error descriptivo en caso de que haya habido una excepción
    if (!archivo) {
        throw runtime_error("No se pudo abrir el archivo: " + nombreFichero);
    }
    // Declaramos las variables que vamos a necesitar para construir el objeto
    float x, y; // Coordenadas de cada ciudad
    int esAlmacenInt; // En el archivo de texto utilizamos un 1 para indicar que es un almacén y 0 para indicar lo contrario
    // Leyemos la info de las ciudades
    for (int indice = 0; indice < 20; ++indice) {
        if (!(archivo >> x >> y >> esAlmacenInt)) {
            throw runtime_error("Error leyendo ciudad en índice " + to_string(indice));
        }
        // Creamos una variable esAlmacen inicializada en falso, si el el valor de esAlamacenInt es 1 lo cambiamos a verdadero
        bool esAlmacen = false;
        if (esAlmacenInt == 1) { esAlmacen == true;}
        // Creamos el objeto Ciudad con las variables float x, y así como la variable booleana esAlmacen que depende de esAlmacenInt
        Ciudad nuevaCiduad(x, y, esAlmacen);
        ciudades.push_back(nuevaCiduad);
    }
    // Calculad la distancia desde cada ciudad al almacén. Esto lo hacemos una vez tenemos todos los objetos de la clase Ciudad añadidos al vector
    // Necesitamos tener las coordenadas del almacén para hacer este cálculo. Para ello en un bucle for determinamos el índice del almacén y luego 
    // extraemos las coordendas con getCoordendas
    Coordenadas almacenCoordenadas;
    for (const Ciudad& ciudad : ciudades)
    {
        if (ciudad.getEsAlmacen())
        {
            Coordenadas almacenCoordenadas = ciudad.getCoordenadas();
        }
    }
    for (Ciudad& ciudad : ciudades) {
        ciudad.calcularDistanciaAlmacen(almacenCoordenadas);
    }
    return ciudades;
}
// La siguiente función lee la información del fichero de Productos
vector<Producto> leerProductos(const string& nombreFichero) {
    // Como hay varios productos, utilizamos un vector
    vector<Producto> productos;
    // Abrimos el flujo al fichero
    ifstream archivo(nombreFichero);
    if (!archivo) { // Si no se pudo abrir mostramos un error indicando el fichero concreto que no se pudo abrir, porque hay varios
        throw runtime_error("No se pudo abrir el archivo de productos: " + nombreFichero);
    }
    // Creamos las variables que vamos a utilizar para dar valores a los atributos
    string nombreProducto;
    int cantidadDisponible;
    float precio;
    // Mientras siga fluyendo información del archivo continuamos añadiendo objetos, hasta llegar al final del fichero
    while (archivo >> nombreProducto >> cantidadDisponible >> precio) {
        try 
        { // Si la información del fichero se ha leído correctamente deberíamos primero crear el objeto y luego añadirlo al vector con push_back
            Producto nuevoProducto(nombreProducto, cantidadDisponible, precio);
            productos.push_back(nuevoProducto);
            
        } // Si nos encontramos un error leyendo el fichero lo indicamos
        catch (const runtime_error& e) {
            throw runtime_error("Error al procesar producto " + nombreProducto + ": " + e.what());
        }
    }
    // Una vez hemos terminado de añadir todos los objetos al vector devolvemos el vector de productos
    return productos;
}
// La siguiente función lee la información del fichero de Clientes
vector<Cliente> leerClientes(const string& nombreFichero, const vector<Ciudad>& ciudades) {
    // Como hay varios objetos utilizamos vectores
    vector<Cliente> clientes;
    // Abrimos el flujo de salida del fichero
    ifstream archivo(nombreFichero);
    cout << "Intentando leer clientes de fichero de clientes: " << nombreFichero << endl;

    if (!archivo) { // Si no hemos podido acceder al fichero indicamos el error 
        cerr << "Error al intentar abrir fichero de clientes: " << nombreFichero << endl;
        return clientes;
    }

    // Creamos la variable line que vamos a utilizar para leer la información del fichero línea a línea
    string line;
    // Creamos la variable indiceLinea que utilizaremos como el índice de las líneas
    int indiceLinea = 0;

    while (getline(archivo, line)) {
        indiceLinea++;

        istringstream iss(line);
        // Declaración de las variables que darán valor a los atributos
        string id, nombre, apellido1, apellido2;
        int yearNacimiento, monthNacimiento, dayNacimiento;
        long long int numeroTelefonico;
        int indiceCiudad;
        
        // A partir de los datos del archivo de texto damos valor a las variables
        if (!(iss >> id >> nombre >> apellido1 >> apellido2
              >> yearNacimiento >> monthNacimiento >> dayNacimiento
              >> numeroTelefonico >> indiceCiudad)) { 
            cerr << "Error al leer línea " << indiceLinea << endl;
            continue; // Con continue podemos continuar ejecutando el resto del código
        }
        // Con las variables ya con valores creamos los objetos
        try {
            // Creamos el objeto Fecha, que será un atributo de la clase Cliente
            Fecha fn(dayNacimiento, monthNacimiento, yearNacimiento);
            // Creamos un objeto Cliente con los valores que tenemos en cada iteración del bucle
            Cliente cliente(id, nombre, apellido1, apellido2, fn, numeroTelefonico, ciudades[indiceCiudad]);
            // Después de crear el objeto lo añadimos al vector con push_back
            clientes.push_back(cliente);
            cout << "Cliente añadido exitosamente: " << id << endl;
        } catch (const runtime_error& e) {
            cerr << "Error procesando al cliente" << id << ": " << e.what() << endl;
            continue; // Con continue podemos continuar ejecutando el resto del código
        }
    }

    cout << "Terminado de leer clientes. Total clientes: " << clientes.size() << endl;
    return clientes;
}
// Función auxiliar para la función que lee los datos de Empleados
int contarConductores(const vector<Empleado>& empleados) 
{
    int numConductores = 0;
    for (const Empleado& empleado : empleados) 
    { 
        if (empleado.getTipo() == Tipo::CONDUCTOR) 
        {
            numConductores++;
        }
    }
    return numConductores;
}
// La siguiente función lee la información del fichero de Empleados
vector<Empleado> leerEmpleados(const string& nombreFichero, const vector<Ciudad>& ciudades) {
    vector<Empleado> empleados;
    ifstream archivo(nombreFichero);
    cout << "Intentando leer empleados de fichero: " << nombreFichero << endl;

    if (!archivo) {
        cerr << "Error al intentar abrir fichero de empleados: " << nombreFichero << endl;
        return empleados;
    }

    string linea;
    // Índice de la línea que estamos leyendo
    int indiceLinea = 0;
    // Cambiar la forma de leer del archivo
    while (getline(archivo, linea)) {

        istringstream iss(linea);
        // Creamos las variables locales que vamos a utilizar para dar valores a los atributos de la clase Empleado
        string id, nombre, apellido1, apellido2, tipoStr;
        int yearNacimiento, monthNacimiento, dayNacimiento;
        long long int numeroTelefonico;
        int indiceCiudad, yearIncorporacion, monthIncorporacion, dayIncorporacion; // Campos para fecha de incorporación

        // Leer todos los campos, incluyendo fecha de incorporación y tipo
        if (!(iss >> id >> nombre >> apellido1 >> apellido2
              >> yearNacimiento >> monthNacimiento >> dayNacimiento
              >> numeroTelefonico >> indiceCiudad
              >> yearIncorporacion >> monthIncorporacion >> dayIncorporacion >> tipoStr)) {
            cerr << "Error al intentar leer línea " << indiceLinea << endl;
            continue;
        }

        try {
            Fecha fn(dayNacimiento, monthNacimiento, yearNacimiento);
            // Usar la fecha de incorporación leída del archivo
            Fecha fi(dayIncorporacion, monthIncorporacion, yearIncorporacion);

            // Como tenemos el tipo de empleado como string, tenemos que hacer la conversión
            Tipo tipo;
            if (tipoStr == "Conductor") {
                tipo = Tipo::CONDUCTOR;
            } else if (tipoStr == "Repartidor") {
                tipo = Tipo::REPARTIDOR;
            } else {
                cerr << "Tipo inválido para empleado con ID " << id << ": " << tipoStr << endl;
                continue;
            }

            // Creamos un objeto Empleado con los datos leídos
            Empleado nuevoEmpleado(id, nombre, apellido1, apellido2, fn, numeroTelefonico, ciudades[indiceCiudad], fi, tipo);
            // Añadimos el objeto al vector
            empleados.push_back(nuevoEmpleado);

            cout << "Empleado añadido exitosamente: " << id << endl;
        } catch (const runtime_error& e) {
            cerr << "Error procesando empleado " << id << ": " << e.what() << endl;
            continue;
        }
    }

    cout << "Terminado de leer empleados. Total empleados: " << empleados.size() << endl;
    return empleados;
}

#endif






