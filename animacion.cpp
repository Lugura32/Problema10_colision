#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <iomanip>
#include "../funcion/Grafica.h"

using namespace std;

void generarAnimacion() {
    cout << "Generando animacion GIF..." << endl;
    
    // LIMPIAR ARCHIVOS ANTERIORES
    remove("animacion.gif");
    system("rmdir /s /q frames 2>nul");
    
    // Leer datos del archivo de simulación
    ifstream datafile("simulacion.txt");
    if (!datafile.is_open()) {
        cerr << "Error: No se pudo abrir simulacion.txt" << endl;
        return;
    }
    
    // Saltar la línea de encabezado
    string header;
    getline(datafile, header);
    
    // Leer datos
    vector<double> tiempos, posiciones, velocidades, energias;
    double t, x, v, e;
    
    while (datafile >> t >> x >> v >> e) {
        tiempos.push_back(t);
        posiciones.push_back(x);
        velocidades.push_back(v);
        energias.push_back(e);
    }
    datafile.close();
    
    if (tiempos.empty()) {
        cerr << "Error: No hay datos en simulacion.txt" << endl;
        return;
    }
    
    // Crear directorio para frames temporales
    system("mkdir frames 2>nul");
    
    // Generar frames individuales
    int total_frames = tiempos.size();
    int frame_step = max(1, total_frames / 30);
    
    cout << "Generando " << (total_frames / frame_step) << " frames..." << endl;
    
    int frame_count = 0;
    for (int i = 0; i < total_frames; i += frame_step) {
        stringstream frame_filename;
        frame_filename << "frames/frame_" << setw(5) << setfill('0') << frame_count << ".png";
        
        stringstream script;
        script << "set terminal png size 1200,800 enhanced font 'Arial,12'" << endl;
        script << "set output '" << frame_filename.str() << "'" << endl;
        script << "set multiplot layout 2,1 title 'Simulacion de Particula en Caja - Tiempo: " 
               << fixed << setprecision(3) << tiempos[i] << " s'" << endl;
        
        // Gráfica superior: Posición
        script << "set title 'Posicion vs Tiempo'" << endl;
        script << "set xlabel 'Tiempo (s)'" << endl;
        script << "set ylabel 'Posicion (m)'" << endl;
        script << "set xrange [0:" << tiempos.back() << "]" << endl;
        script << "set yrange [0:*]" << endl;
        script << "set grid" << endl;
        script << "plot 'simulacion.txt' every ::1 using 1:2 with lines lw 2 lc rgb 'blue' title 'Trayectoria', \\" << endl;
        script << "     '-' using 1:2 with points pt 7 ps 3 lc rgb 'red' title 'Posicion Actual'" << endl;
        script << tiempos[i] << " " << posiciones[i] << endl;
        script << "e" << endl;
        
        // Gráfica inferior: Velocidad
        script << "set title 'Velocidad vs Tiempo'" << endl;
        script << "set xlabel 'Tiempo (s)'" << endl;
        script << "set ylabel 'Velocidad (m/s)'" << endl;
        script << "set xrange [0:" << tiempos.back() << "]" << endl;
        script << "set yrange [*:*]" << endl;
        script << "set grid" << endl;
        script << "plot 'simulacion.txt' every ::1 using 1:3 with lines lw 2 lc rgb 'green' title 'Velocidad', \\" << endl;
        script << "     '-' using 1:2 with points pt 7 ps 3 lc rgb 'red' title 'Velocidad Actual'" << endl;
        script << tiempos[i] << " " << velocidades[i] << endl;
        script << "e" << endl;
        
        script << "unset multiplot" << endl;
        
        // Guardar script temporal
        ofstream scriptfile("temp_anim.gnu");
        if (scriptfile.is_open()) {
            scriptfile << script.str();
            scriptfile.close();
            system("gnuplot temp_anim.gnu >nul 2>&1");
        }
        
        frame_count++;
    }
    
    remove("temp_anim.gnu");
    
    // Crear GIF animado
    cout << "Creando GIF animado..." << endl;
    
    // Intentar con diferentes rutas posibles de ImageMagick
    const char* magick_paths[] = {
        "magick.exe",
        "\"C:\\Program Files\\ImageMagick-7.1.2-Q16-HDRI\\magick.exe\"",
        "\"C:\\Program Files\\ImageMagick-7.1.2\\magick.exe\"",
        "\"C:\\Program Files\\ImageMagick-7.1.1\\magick.exe\""
    };
    
    int result = -1;
    for (const char* magick_path : magick_paths) {
        string command = string(magick_path) + " -delay 30 frames/frame_*.png animacion.gif";
        cout << "Intentando con: " << magick_path << endl;
        result = system(command.c_str());
        if (result == 0) {
            cout << "¡GIF creado exitosamente!" << endl;
            break;
        }
    }
    
    // LIMPIAR FRAMES TEMPORALES
    system("rmdir /s /q frames 2>nul");
    
    if (result != 0) {
        cout << "No se pudo crear el GIF automaticamente." << endl;
        cout << "Puedes crear el GIF manualmente ejecutando:" << endl;
        cout << "magick.exe -delay 30 frames/frame_*.png animacion.gif" << endl;
    } else {
        cout << "Animacion guardada como: animacion.gif" << endl;
    }
}