#ifndef PLOTTING_H
#define PLOTTING_H

#include <vector>
#include <string>
#include <Eigen/Dense>

void plot_2d_trace(
    const std::string& title,
    const Eigen::VectorXd& x_0,
    const Eigen::VectorXd& x_f,
    const std::vector<Eigen::VectorXd>& path,
    const std::vector<std::vector<Eigen::VectorXi>>& all_front_cells,
    const std::vector<Eigen::VectorXd>& intersection_coords,
    const std::vector<Eigen::VectorXi>& y_coords_history,
    const std::vector<Eigen::VectorXi>& obstacles
);

void plot_3d_trace(
    const std::string& title,
    const Eigen::VectorXd& x_0,
    const Eigen::VectorXd& x_f,
    const std::vector<Eigen::VectorXd>& path,
    const std::vector<std::vector<Eigen::VectorXi>>& all_front_cells,
    const std::vector<Eigen::VectorXd>& intersection_coords,
    const std::vector<Eigen::VectorXi>& y_coords_history,
    const std::vector<Eigen::VectorXi>& obstacles
);

#endif // PLOTTING_H