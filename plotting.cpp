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
    // Obstacles
    if (!obstacles.empty()) {
        for (size_t i = 0; i < obstacles.size(); ++i) {
            const auto& obs = obstacles[i];
            script << "set object " << i + 1 << " rect from " << obs(0) << "," << obs(1) << " to " << obs(0) + 1 << "," << obs(1) + 1 << " fc rgb 'black' fs solid 0.5\n";
        }
    }

    // Front cells
    if (!all_front_cells.empty()) {
        int obj_idx = obstacles.size() + 1;
        for (const auto& step_cells : all_front_cells) {
            for (const auto& cell : step_cells) {
                script << "set object " << obj_idx++ << " rect from " << cell(0) << "," << cell(1) << " to " << cell(0) + 1 << "," << cell(1) + 1 << " fc rgb 'cyan' fs solid 0.3\n";
            }
        }
    }
    
    // Arrows from intersections to front cells
    if (!intersection_coords.empty() && !all_front_cells.empty()) {
        int arrow_idx = 1;
        for (size_t i = 0; i < intersection_coords.size(); ++i) {
            if (i < all_front_cells.size()) {
                const auto& intersection = intersection_coords[i];
                const auto& front_cells = all_front_cells[i];
                for (const auto& cell : front_cells) {
                    double start_x = intersection(0);
                    double start_y = intersection(1);
                    double end_x = cell(0) + 0.5;
                    double end_y = cell(1) + 0.5;
                    script << "set arrow " << arrow_idx++ << " from " << start_x << "," << start_y << " to " << end_x << "," << end_y << " head filled lw 2 lc 'red'\n";
                }
            }
        }
    }

    std::vector<std::string> plot_commands;
    plot_commands.push_back("'-' with lines title 'Path'");
    plot_commands.push_back("'-' with points pt 7 ps 2 lc 'red' title 'Intersections'");
    plot_commands.push_back("'-' with points pt 5 ps 1.5 lc 'green' title 'Start'");
    plot_commands.push_back("'-' with points pt 5 ps 1.5 lc 'blue' title 'Goal'");
    plot_commands.push_back("'-' with points pt 9 ps 1.5 lc 'purple' title 'Y Coords'");
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
    script << "set view 60, 30\n";


    // Arrows
    if (!intersection_coords.empty() && !all_front_cells.empty()) {
        int arrow_idx = 1;
        for (size_t i = 0; i < intersection_coords.size(); ++i) {
            if (i < all_front_cells.size()) {
                const auto& intersection = intersection_coords[i];
                const auto& front_cells = all_front_cells[i];
                for (const auto& cell : front_cells) {
                    double start_x = intersection(0);
                    double start_y = intersection(1);
                    double start_z = intersection(2);
                    double end_x = cell(0) + 0.5;
                    double end_y = cell(1) + 0.5;
                    double end_z = cell(2) + 0.5;
                    script << "set arrow " << arrow_idx++ << " from " << start_x << "," << start_y << "," << start_z << " to " << end_x << "," << end_y << "," << end_z << " head filled lw 2 lc 'red'\n";
                }
            }
        }
    }

    script << "set pm3d depthorder\n";
    std::vector<std::string> splot_commands;
    splot_commands.push_back("'-' with lines title 'Path'");
    splot_commands.push_back("'-' with points pt 7 ps 2 lc 'red' title 'Intersections'");
    splot_commands.push_back("'-' with points pt 5 ps 1.5 lc 'green' title 'Start'");
    splot_commands.push_back("'-' with points pt 5 ps 1.5 lc 'blue' title 'Goal'");
    splot_commands.push_back("'-' with points pt 9 ps 1.5 lc 'purple' title 'Y Coords'");

    if (!obstacles.empty()) {
        splot_commands.push_back("'-' with polygons fc rgb 'black' fs solid 0.5 notitle");
    }
    if (!all_front_cells.empty()) {
        for (const auto& step : all_front_cells) {
            for (size_t i = 0; i < step.size(); ++i) {
                splot_commands.push_back("'-' with polygons fc rgb 'cyan' fs solid 0.3 notitle");
            }
        }
    }
    
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

    auto write_cube_faces = [](std::ofstream& s, const Eigen::VectorXi& origin) {
        double x = origin(0);
        double y = origin(1);
        double z = origin(2);
        s << x << " " << y << " " << z << "\n";
        s << x + 1 << " " << y << " " << z << "\n";
        s << x + 1 << " " << y + 1 << " " << z << "\n";
        s << x << " " << y + 1 << " " << z << "\n\n";
        s << x << " " << y << " " << z + 1 << "\n";
        s << x + 1 << " " << y << " " << z + 1 << "\n";
        s << x + 1 << " " << y + 1 << " " << z + 1 << "\n";
        s << x << " " << y + 1 << " " << z + 1 << "\n\n";
        s << x << " " << y << " " << z << "\n";
        s << x << " " << y << " " << z + 1 << "\n";
        s << x << " " << y + 1 << " " << z + 1 << "\n";
        s << x << " " << y + 1 << " " << z << "\n\n";
        s << x + 1 << " " << y << " " << z << "\n";
        s << x + 1 << " " << y << " " << z + 1 << "\n";
        s << x + 1 << " " << y + 1 << " " << z + 1 << "\n";
        s << x + 1 << " " << y + 1 << " " << z << "\n\n";
    };

    if (!obstacles.empty()) {
        for (const auto& obs : obstacles) {
            write_cube_faces(script, obs);
        }
        script << "e\n";
    }

    if (!all_front_cells.empty()) {
        for (const auto& step_cells : all_front_cells) {
            for (const auto& cell : step_cells) {
                write_cube_faces(script, cell);
            }
        }
        script << "e\n";
    }

    script.close();
    run_gnuplot("plot_3d.gp");
}

void plot_2d_projection(
    const std::string& title,
    const Eigen::VectorXd& x_0,
    const Eigen::VectorXd& x_f,
    const std::vector<Eigen::VectorXd>& path,
    const std::vector<std::vector<Eigen::VectorXi>>& all_front_cells,
    const std::vector<Eigen::VectorXd>& intersection_coords,
    const std::vector<Eigen::VectorXi>& y_coords_history,
    const std::vector<Eigen::VectorXi>& obstacles,
    int dim1, int dim2)
{
    std::ofstream script("plot_2d_proj.gp");
    script << "set term pngcairo size 800,800\n";
    script << "set output '" << title << ".png'\n";
    script << "set title '" << title << "'\n";
    script << "set xlabel 'Dim " << dim1 << "'\n";
    script << "set ylabel 'Dim " << dim2 << "'\n";
    script << "set grid\n";
    script << "set size square\n";

    // Obstacles
    if (!obstacles.empty()) {
        for (size_t i = 0; i < obstacles.size(); ++i) {
            const auto& obs = obstacles[i];
            script << "set object " << i + 1 << " rect from " << obs(dim1) << "," << obs(dim2) << " to " << obs(dim1) + 1 << "," << obs(dim2) + 1 << " fc rgb 'black' fs solid 0.5\n";
        }
    }

    // Front cells
    if (!all_front_cells.empty()) {
        int obj_idx = obstacles.size() + 1;
        for (const auto& step_cells : all_front_cells) {
            for (const auto& cell : step_cells) {
                script << "set object " << obj_idx++ << " rect from " << cell(dim1) << "," << cell(dim2) << " to " << cell(dim1) + 1 << "," << cell(dim2) + 1 << " fc rgb 'cyan' fs solid 0.3\n";
            }
        }
    }
    
    std::vector<std::string> plot_commands;
    plot_commands.push_back("'-' with lines title 'Path'");
    plot_commands.push_back("'-' with points pt 7 ps 2 lc 'red' title 'Intersections'");
    plot_commands.push_back("'-' with points pt 5 ps 1.5 lc 'green' title 'Start'");
    plot_commands.push_back("'-' with points pt 5 ps 1.5 lc 'blue' title 'Goal'");
    plot_commands.push_back("'-' with points pt 9 ps 1.5 lc 'purple' title 'Y Coords'");

    script << "plot ";
    for (size_t i = 0; i < plot_commands.size(); ++i) {
        script << plot_commands[i] << (i == plot_commands.size() - 1 ? "" : ", ");
    }
    script << "\n";

    // Path data
    for (const auto& p : path) {
        script << p(dim1) << " " << p(dim2) << "\n";
    }
    script << "e\n";

    // Intersection data
    for (const auto& i : intersection_coords) {
        script << i(dim1) << " " << i(dim2) << "\n";
    }
    script << "e\n";

    // Start data
    script << x_0(dim1) << " " << x_0(dim2) << "\n";
    script << "e\n";

    // Goal data
    script << x_f(dim1) << " " << x_f(dim2) << "\n";
    script << "e\n";

    // Y Coords data
    for (const auto& y : y_coords_history) {
        script << y(dim1) << " " << y(dim2) << "\n";
    }
    script << "e\n";

    script.close();
    run_gnuplot("plot_2d_proj.gp");
}