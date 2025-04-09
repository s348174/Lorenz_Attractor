# Lorenz_Attractor
C++ code for a Lorenz attractor. It immplements a 4 step Runge-Kutta method in order to solve at each time the Lorenz differential equation which gives the gradient:

$$\begin{cases} \dot{x} = \sigma y-x; \\ \dot{y} = x (\rho - z) - y; \\ \dot{z} = x y - \beta z \end{cases}$$

The main file requires 2 command line arguments, the first beeing T_max, or the maximum time for calculating the trajectory, the second being dt, or the integration step. Each coordinate of the strating point X0 is chosen uniformly at random between -0.1 and 0.1. $\sigma$, $\rho$, $\beta$ are given.
The trajectory is memorized in a vectr<Vector3d>> using Eigen library. Then the programs prints the trajectory in an output txt file.
