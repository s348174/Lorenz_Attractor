# Lorenz_Attractor
C++ code for a Lorenz attractor. The Lorenz attractor is a dinamical system of 3 first order ODEs, so the code implements a 4 step Runge-Kutta method in order to solve numerically at each time step in a given interval the ODEs which give the gradient:

$$\begin{cases} \dot{x} = \sigma y-x \newline \dot{y} = x (\rho - z) - y \newline \dot{z} = x y - \beta z. \end{cases}$$

The gradient is then multiplied by the time step ad added to previous posisision in order to obtain the next point in the trajectory:

$$ X_{i+1} = X_{i} + \nabla X_i \cdot dt \ .$$

The points of the trajectory are stored in a dinamically allocated `vector<Vector3d>`, where `vector` is the native dinamically allocated array of the standard template library, while `Vector3d` is a column vector of 3 doubles from the Eigen library. 

The main.cpp file requires 2 command line arguments, the first beeing T_max, or the maximum time for calculating the trajectory, the second beeing dt, or the integration step. 
Each coordinate of the starting point X0 is chosen uniformly at random between -0.1 and 0.1, while $\sigma = 10$, $\rho = 28$, $\beta = 8/3$ are given.
The trajectory is memorized in a vectr<Vector3d>> using Eigen library. Then the programs prints the trajectory in an output .csv file.

The file plot_lorenz.m in the main directory is a MATLAB script that can be used to make a 3d plot of the resulting .csv file.
