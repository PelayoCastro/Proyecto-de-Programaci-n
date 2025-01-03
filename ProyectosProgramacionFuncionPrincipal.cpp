#include "ProyectosProgramacionHeader.h"


int main() {
    try {
        // Leer todos los datos
        vector<Ciudad> ciudades = leerCiudades("ProyectoProgramacion_Ciudades.txt");
        vector<Empleado> empleados = leerEmpleados("ProyectoProgramacion_Empleados.txt", ciudades);
        vector<Cliente> clientes = leerClientes("ProyectoProgramacion_Clientes.txt", ciudades);
        vector<Producto> productos = leerProductos("ProyectoProgramacion_Productos.txt");

        // Mostrar información de ciudades
        cout << "\n=== INFORMACIÓN DE CIUDADES ===" << endl;
        cout << endl;
        for (int i = 0; i < ciudades.size(); ++i) {
            Ciudad& ciudad = ciudades[i];
            cout << "Ciudad " << i << ":" << endl;
            cout << "Coordenadas: (" << ciudad.getCoordenadas().x << ", " 
                 << ciudad.getCoordenadas().y << ")" << endl;
            cout << "Tipo: " << (ciudad.getEsAlmacen() ? "Almacén" : "Ciudad ") << endl;
            if (!ciudad.getEsAlmacen()) {
                cout << "Distancia al almacén: " << ciudad.getDistanciaAlmacen() << " km" << endl;
            }
            cout << endl;
        }

        
        cout << "\n=== INFORMACIÓN DE EMPLEADOS ===" << endl;
        cout << endl;
        for (Empleado& empleado : empleados) {
            cout << "ID: " << empleado.getID() << endl;
            cout << "Nombre completo: " << empleado.getNombre() << " " 
                 << empleado.getApellido1() << " " << empleado.getApellido2() << endl;
            cout << "Tipo: " << (empleado.getTipo() == Tipo::CONDUCTOR ? "Conductor" : "Repartidor") << endl;
            cout << "Ciudad asignada: (" << empleado.getCiudad().getCoordenadas().x << ", " 
                 << empleado.getCiudad().getCoordenadas().y << ")" << endl;
            cout << endl;
        }

        
        cout << "\n=== INFORMACIÓN DE CLIENTES ===" << endl;
        cout << endl;
        for (Cliente& cliente : clientes) {
            cout << "ID: " << cliente.getID() << endl;
            cout << "Nombre completo: " << cliente.getNombre() << " " 
                 << cliente.getApellido1() << " " << cliente.getApellido2() << endl;
            cout << "Ciudad: (" << cliente.getCiudad().getCoordenadas().x << ", " 
                 << cliente.getCiudad().getCoordenadas().y << ")" << endl;
            if (!cliente.getCiudad().getEsAlmacen()) {
                cout << "Distancia al almacén: " << cliente.getCiudad().getDistanciaAlmacen() 
                     << " km" << endl;
            }
            cout << endl;
        }

        
        cout << "\n=== INFORMACIÓN DE PRODUCTOS ===" << endl;
        cout << endl;
        for (Producto& producto : productos) {
            cout << "Nombre: " << producto.getNombre() << endl;
            cout << "Cantidad disponible: " << producto.getCantidad() << endl;
            cout << "Precio: " << producto.getPrecio() << "€" << endl;
            cout << endl;
        }

        
        cout << "\n=== ESTADÍSTICAS GENERALES ===" << endl;
        cout << endl;
        cout << "Total de ciudades: " << ciudades.size() << endl;
        cout << "Total de empleados: " << empleados.size() << endl;
        cout << "Total de clientes: " << clientes.size() << endl;
        cout << "Total de productos: " << productos.size() << endl;

        // Contamos los empleados de cada tipo que hay
        int numConductores = contarConductores(empleados);
        cout << "\nDistribución de empleados:" << endl;
        cout << "Conductores: " << numConductores << endl;
        cout << "Repartidores: " << empleados.size() - numConductores << endl;

        // Calcular el valor total del inventario
        double valorTotalDelInventario = 0.0;
        for (Producto& producto : productos) {
            valorTotalDelInventario += producto.getPrecio() * producto.getCantidad();
        }
        cout << "\nValor total del inventario: " << valorTotalDelInventario << "€" << endl;

    } catch (exception& e) {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }

    return 0;
}
