#include "./src/Utils.hpp"
#include <iostream>
#include <Eigen/Eigen>
#include <cmath>
#include <vector>
#include <random>
#include <iomanip>
#include <sstream>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <filesystem>

using namespace std;
using namespace Eigen;

int main(int argc, char** argv)
{
    // Inizializzazione dei parametri di integrazione da riga di comando
    double T_max; // Tempo massimo di integrazione
    double dt; // Passo di integrazione
    if (argc != 3) {
        cerr << "Input missing" << endl;
        return 1;
    }
    else {
        istringstream str_Tmax(argv[1]);
        str_Tmax >> T_max;

        istringstream str_dt(argv[2]);
        str_dt >> dt;
    }
    // Inizializzazione dei parametri dell'equazione
    const double r = 10;
    const double s = 10;
    const double b = 8/3;
    // Inizializzazione dei parametri di integrazione
    // double T_max = 100; // Tempo massimo di integrazione
    // double dt = 0.001; // Passo di integrazione

    // Vector3d X0(0.01,-0.1,-0.1);
    // Generazione casuale del punto di partenza
    Vector3d X0;
    random_device dev;
    mt19937 rng(dev());
    uniform_real_distribution<double> dist(-0.1,0.1); // Campionamento da una uniforme U(-0.1,0.1)
    for (unsigned int i=0;i<3;++i) {
        X0(i) = dist(rng);
    }

    // Calcolo della traiettoria
    vector<Vector3d> X = runge_kutta_4(X0,T_max,dt,r,s,b);

    // for (size_t i = 0; i < X.size(); ++i) {
    //     cout << scientific << setprecision(8) << X[i].transpose() << endl;
    // }

    // Scrittura file di output
    // int N = round(T_max/dt);
    // string fileoutname = "Lorenz_attractor_trajectory_N=" + to_string(N) + "_X0=" + to_string(X0(0)) + ";" + to_string(X0(1)) + ";" + to_string(X0(2)) + ".txt";
    // if(print_result(fileoutname, X)) {
    //     cout << "File " << fileoutname << " written successfully" << endl;
    // }

    // Creazione cartella per l'export in csv
    string data_folder = "data";
    if (mkdir(data_folder.c_str(), 0777) == -1) {
        if (errno != EEXIST) {
            cerr << "Could not create directory " << data_folder << endl;
        }
    }

    // Scrittura file csv
    string filecsvname = (filesystem::current_path() / "data" / "Lorenz_attractor_trajectory.csv").string();
    // "../" + data_folder + "/Lorenz_attractor_trajectory.csv"
    if(print_trajectory_to_csv(X, filecsvname)) {
        cout << "File " << filecsvname << " written successfully" << endl;
    }

    // cout << "Current working directory: " << filesystem::current_path() << endl;
    return 0;
}
