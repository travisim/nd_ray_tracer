#include "plotting.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <Eigen/Dense>

void run_gnuplot(const std::string& script_path) {
    // Check if gnuplot is in the PATH
    if (system("command -v gnuplot > /dev/null 2>&1") != 0) {
        std::cerr << "Warning: gnuplot not found. Skipping plot generation." << std::endl;
        return;
    }

    std::string command = "gnuplot " + script_path;
    int result = system(command.c_str());
    if (result != 0) {
        std::cerr << "Error executing gnuplot script." << std::endl;
    }
}

void plot_2d_trace(
    const std::string& title,
    const Eigen::VectorXd& x_0,
    const Eigen::VectorXd& x_f,
    const std::vector<Eigen::VectorXd>& path,
    const std::vector<std::vector<Eigen::VectorXi>>& all_front_cells,
    const std::vector<Eigen::VectorXd>& intersection_coords,
    const std::vector<Eigen::VectorXi>& y_coords_history,
    const std::vector<Eigen::VectorXi>& obstacles)
{
    std::ofstream script("plot_2d.gp");
    script << "set term pngcairo size 800,800\n";
    script << "set output '" << title << ".png'\n";
    script << "set title '" << title << "'\n";
    script << "set xlabel 'X'\n";
    script << "set ylabel 'Y'\n";
    script << "set grid\n";
    script << "set size square\n";
    std::vector<std::string> plot_commands;
    plot_commands.push_back("'-' with lines title 'Path'");
    plot_commands.push_back("'-' with points pt 7 ps 2 lc 'red' title 'Intersections'");
    plot_commands.push_back("'-' with points pt 5 ps 1.5 lc 'green' title 'Start'");
    plot_commands.push_back("'-' with points pt 5 ps 1.5 lc 'blue' title 'Goal'");
    plot_commands.push_back("'-' with points pt 9 ps 1.5 lc 'purple' title 'Y Coords'");

    if (!all_front_cells.empty()) {
        for (size_t i = 0; i < all_front_cells.size(); ++i) {
            plot_commands.push_back("'-' with boxes fill solid 0.2 title 'Front Cells " + std::to_string(i) + "'");
        }
    }
    if (!obstacles.empty()) {
        for (size_t i = 0; i < obstacles.size(); ++i) {
            plot_commands.push_back("'-' with boxes fill solid 1.0 border lc 'black' title 'Obstacle " + std::to_string(i) + "'");
        }
    }

    script << "plot ";
    for (size_t i = 0; i < plot_commands.size(); ++i) {
        script << plot_commands[i] << (i == plot_commands.size() - 1 ? "" : ", ");
    }
    script << "\n";

    // Path data
    for (const auto& p : path) {
        script << p(0) << " " << p(1) << "\n";
    }
    script << "e\n";

    // Intersection data
    for (const auto& i : intersection_coords) {
        script << i(0) << " " << i(1) << "\n";
    }
    script << "e\n";

    // Start data
    script << x_0(0) << " " << x_0(1) << "\n";
    script << "e\n";

    // Goal data
    script << x_f(0) << " " << x_f(1) << "\n";
    script << "e\n";

    // Y Coords data
    for (const auto& y : y_coords_history) {
        script << y(0) << " " << y(1) << "\n";
    }
    script << "e\n";

    // Front cells data
    for (const auto& step_cells : all_front_cells) {
        if (!step_cells.empty()) {
            for (const auto& cell : step_cells) {
                script << cell(0) << " " << cell(1) << " 1 1\n";
            }
        }
        script << "e\n";
    }

    // Obstacles data
    if (!obstacles.empty()) {
        for (const auto& obs : obstacles) {
            script << obs(0) << " " << obs(1) << " 1 1\n";
        }
        script << "e\n";
    }

    script.close();
    run_gnuplot("plot_2d.gp");
}

void plot_3d_trace(
    const std::string& title,
    const Eigen::VectorXd& x_0,
    const Eigen::VectorXd& x_f,
    const std::vector<Eigen::VectorXd>& path,
    const std::vector<std::vector<Eigen::VectorXi>>& all_front_cells,
    const std::vector<Eigen::VectorXd>& intersection_coords,
    const std::vector<Eigen::VectorXi>& y_coords_history,
    const std::vector<Eigen::VectorXi>& obstacles)
{
    std::ofstream script("plot_3d.gp");
    script << "set term pngcairo size 800,800\n";
    script << "set output '" << title << ".png'\n";
    script << "set title '" << title << "'\n";
    script << "set xlabel 'X'\n";
    script << "set ylabel 'Y'\n";
    script << "set zlabel 'Z'\n";
    script << "set grid\n";
    std::vector<std::string> splot_commands;
    splot_commands.push_back("'-' with lines title 'Path'");
    splot_commands.push_back("'-' with points pt 7 ps 2 lc 'red' title 'Intersections'");
    splot_commands.push_back("'-' with points pt 5 ps 1.5 lc 'green' title 'Start'");
    splot_commands.push_back("'-' with points pt 5 ps 1.5 lc 'blue' title 'Goal'");
    splot_commands.push_back("'-' with points pt 9 ps 1.5 lc 'purple' title 'Y Coords'");
    
    script << "splot ";
    for (size_t i = 0; i < splot_commands.size(); ++i) {
        script << splot_commands[i] << (i == splot_commands.size() - 1 ? "" : ", ");
    }
    script << "\n";
    
    // Path data
    for (const auto& p : path) {
        script << p(0) << " " << p(1) << " " << p(2) << "\n";
    }
    script << "e\n";

    // Intersection data
    for (const auto& i : intersection_coords) {
        script << i(0) << " " << i(1) << " " << i(2) << "\n";
    }
    script << "e\n";

    // Start data
    script << x_0(0) << " " << x_0(1) << " " << x_0(2) << "\n";
    script << "e\n";

    // Goal data
    script << x_f(0) << " " << x_f(1) << " " << x_f(2) << "\n";
    script << "e\n";

    // Y Coords data
    for (const auto& y : y_coords_history) {
        script << y(0) << " " << y(1) << " " << y(2) << "\n";
    }
    script << "e\n";

    script.close();
    run_gnuplot("plot_3d.gp");
}