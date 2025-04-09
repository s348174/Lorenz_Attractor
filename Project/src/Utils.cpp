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
    X.resize(N);
    X[0] = X0;
    // Ciclo for che implementa il metodo
    for (unsigned int i = 0; i < N-1; ++i) {
        Vector3d K1 = lorenz_gradient(X[i], r, s, b);
        Vector3d K2 = lorenz_gradient(X[i] + K1 * dt / 2, r, s, b);
        Vector3d K3 = lorenz_gradient(X[i] + K2 * dt / 2, r, s, b);
        Vector3d K4 = lorenz_gradient(X[i] + K3 * dt, r, s, b);
        X[i+1] = X[i] + dt * (K1 + 2*K2 + 2*K3 + K4) / 6;
    }
    return X;
}

bool print_result(const string& fileoutname, const vector<Vector3d>& X)
{
    ofstream fileout(fileoutname);
    if (fileout.fail()) {
        cerr << "Error while creating/opening " << fileoutname << endl;
        return false;
    }
    for (const Vector3d& X_t : X) {
        fileout << scientific << setprecision(8) << X_t(0) << "; "  << X_t(1) << "; " << X_t(2) << ";" << endl;
    }
    fileout.close();
    return true;
}
