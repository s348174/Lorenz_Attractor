# pragma once

#include <iostream>
#include <Eigen/Eigen>
#include <vector>

using namespace std;
using namespace Eigen;

Vector3d lorenz_gradient(Vector3d X, double& r, double& s, double& b); // Funzione che calcola il gradiente in un punto
vector<Vector3d> runge_kutta_4(Vector3d X0, const double& T_max, const double& dt, double& r, double& s, double& b); // Funzione che implementa il metodo di Runge Kutta a 4 stadi
bool print_result(const string& fileoutname, const vector<Vector3d>& X); // Funzione che stampa l'output in un file
