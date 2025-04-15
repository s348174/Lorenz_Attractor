# Lorenz_Attractor - C++ & MATLAB project

C++ code implementation for a Lorenz attractor. The Lorenz attractor is a weel known dynamical chaotic system described by 3 first order ODEs. The code implements a 4 step Runge-Kutta method in order to solve numerically at each time step in a given interval the ODEs.

## System of equations

The Lorenz equations give the gradient of the trajectory at any given point in $\mathbb{R}^3$:

$$
\begin{cases} 
\dot{x} = \sigma y-x \\
\dot{y} = x (\rho - z) - y \\
\dot{z} = x y - \beta z. 
\end{cases}
$$

The calculation starts in an initial point $X_0 = (x_0,y_0,z_0)$. Each successive point is calculated by multiplying the gradient in point $X_i$ by the time step ad adding to the previous position in order to obtain the next point in the trajectory:

$$
X_{i+1} = X_{i} + \nabla X_i \cdot dt \ .
$$

The gradient is extimated with the following 4 stage Runge-Kutta method:

$$
 \begin{cases}
\begin{aligned}
K_1 &= f(t_n, X_n) \\
K_2 &= f\left(t_n + \frac{h}{2},\; X_n + \frac{h}{2}K_1\right) \\
K_3 &= f\left(t_n + \frac{h}{2},\; X_n + \frac{h}{2}K_2\right) \\
K_4 &= f(t_n + h,\; X_n + hK_3) \\
X_{n+1} &= X_n + \frac{h}{6}(K_1 + 2K_2 + 2K_3 + K_4).
\end{aligned}
\end{cases}
$$

In this case $f(t,X) = f(X) = \nabla X$ since the system of ODEs is only dependent to the position.

## Implementation details

Each coordinate of the starting point $X_0$ is sampled uniformly between $-0.1$ and $0.1$, while parameters $\sigma = 10$, $\rho = 28$, $\beta = 8/3$ are given.

The points of the trajectory are calculated in the c++ program and stored in a dinamically allocated `vector<Vector3d>`, where `vector` is the native dinamically allocated array of the standard template library, while `Vector3d` is a column vector of 3 doubles from the Eigen library. Then the programs exports the trajectory in an output csv file named `Lorenz_attractor_trajectory.csv`.

## Running the program

The main program is the `main.cpp` file. It requires 2 command line arguments, the first is `T_max` (the maximum time for calculating the trajectory) the second is `dt` (the integration step).

The file `plot_lorenz.m` in the main directory is a MATLAB script that can be used to make a 3d plot of the resulting .csv file.

The complete program (C++ + MATLAB) can be executed via the run_all.sh script in Linux and MAC (bash and g++ required) systems. It requiers 2 command line arguments, which are the `T_max` and `dt` of the c++ code: 

```bash
./run_all.sh <T_max> <dt>
```

The script will execute the c++ code, export the results in a `data/` folder (the script creates the folder in the working directory) and then it opens the MATLAB 3d render of the trajectory.
