#include "Utils.hpp"
#include <iostream>
#include <Eigen/Eigen>
#include <vector>
#include <sstream>
#include <fstream>
#include <iomanip>

using namespace std;
using namespace Eigen;

Vector3d lorenz_gradient(Vector3d X, double& r, double& s, double& b)
{
    double x = X(0);
    double y = X(1);
    double z = X(2);
    Vector3d gradient(s * (y - x),              // dx/dt
                      x * (r - z) - y,          // dy/dt
                      x * y - b * z);           // dz/dt
    return gradient;
}

vector<Vector3d> runge_kutta_4(Vector3d X0, const double& T_max, const double& dt, double& r, double& s, double& b)
{
    unsigned int N = round(T_max/dt); // Numero di iterazioni della simulazione
    vector<Vector3d> X; // Vettore in cui viene memorizzata la traiettoria
    X.reserve(N);
    X.push_back(X0);
    unsigned int i = 0;
    unsigned int t = 0;
    // Ciclo for che implementa il metodo
    while (t <= T_max && i <= N) {
        Vector3d K1 = lorenz_gradient(X[i], r, s, b);
        Vector3d K2 = lorenz_gradient(X[i] + K1 * dt / 2, r, s, b);
        Vector3d K3 = lorenz_gradient(X[i] + K2 * dt / 2, r, s, b);
        Vector3d K4 = lorenz_gradient(X[i] + K3 * dt, r, s, b);
        Vector3d X_next = X[i] + dt * (K1 + 2*K2 + 2*K3 + K4) / 6;
        X.push_back((X_next));
        i++;
        t += dt;
    }
    return X;
}

// bool print_result(const string& fileoutname, const vector<Vector3d>& X)
// {
//     ofstream fileout(fileoutname);
//     if (fileout.fail()) {
//         cerr << "Error while creating/opening " << fileoutname << endl;
//         return false;
//     }
//     for (const Vector3d& X_t : X) {
//         fileout << scientific << setprecision(8) << X_t(0) << "; "  << X_t(1) << "; " << X_t(2) << ";" << endl;
//     }
//     fileout.close();
//     return true;
// }

bool print_trajectory_to_csv(const vector<Vector3d>& trajectory, const string& filename)
{
    ofstream file_csv(filename);
    if (!file_csv.is_open()) {
        cerr << "Error while crating/opening " << filename << endl;
        return false;
    }

    // Intestazione
    file_csv << "x,y,z\n";

    for (const auto& point : trajectory) {
        file_csv << scientific << setprecision(8) << point(0) << "," << point(1) << "," << point(2) << "\n";
    }

    file_csv.close();

    return true;
}
