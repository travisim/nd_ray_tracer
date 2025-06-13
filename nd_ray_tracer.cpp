#include "nd_ray_tracer.h"
#include <iostream>
#include <cmath>
#include <limits>
#include <algorithm>

NDRayTracer::NDRayTracer() : l(0), t(0), n(0) {}

Eigen::VectorXi NDRayTracer::_floor_ceil_conditional(const Eigen::VectorXd& a, const Eigen::VectorXd& b) {
    Eigen::VectorXi result(a.size());
    for (int i = 0; i < a.size(); ++i) {
        if (b(i) <= 0) {
            result(i) = std::floor(a(i));
        } else {
            result(i) = std::ceil(a(i));
        }
    }
    return result;
}

int NDRayTracer::_sign(double x) {
    if (x > 0) return 1;
    if (x < 0) return -1;
    return 0;
}

void NDRayTracer::_determine_front_cells_recursive(int dim, Eigen::VectorXi& current_f) {
    if (dim == n) {
        F_list.push_back(current_f);
        return;
    }

    bool is_delta_x_zero = std::abs(delta_x(dim)) < 1e-10;
    bool is_x0_integer = std::abs(x_0(dim) - std::round(x_0(dim))) < 1e-10;

    if (is_delta_x_zero && is_x0_integer) {
        current_f(dim) = -1;
        _determine_front_cells_recursive(dim + 1, current_f);
        current_f(dim) = 0;
        _determine_front_cells_recursive(dim + 1, current_f);
    } else {
        if (delta_x_sign(dim) < 0) {
            current_f(dim) = -1;
        } else {
            current_f(dim) = 0;
        }
        _determine_front_cells_recursive(dim + 1, current_f);
    }
}

void NDRayTracer::_determine_front_cells() {
    F_list.clear();
    Eigen::VectorXi current_f(n);
    _determine_front_cells_recursive(0, current_f);
    F.resize(F_list.size(), n);
    for (size_t i = 0; i < F_list.size(); ++i) {
        F.row(i) = F_list[i];
    }
}

std::map<std::string, std::any> NDRayTracer::init(const Eigen::VectorXd& start, const Eigen::VectorXd& end) {
    x_0 = start;
    n = x_0.size();
    t = 0;

    delta_x = end - x_0;
    abs_delta_x = delta_x.cwiseAbs();
    norm_delta_x = delta_x.norm();
    delta_x_sign.resize(n);
    for (int i = 0; i < n; ++i) {
        delta_x_sign(i) = _sign(delta_x(i));
    }

    l = 0;
    k = Eigen::VectorXi::Zero(n);
    y = _floor_ceil_conditional(x_0, -delta_x);
    y_coords_history.clear();
    y_coords_history.push_back(y);

    _determine_front_cells();

    D.resize(n);
    for (int i = 0; i < n; ++i) {
        if (delta_x(i) < 0) {
            D(i) = (std::floor(x_0(i)) - x_0(i)) / delta_x(i);
        } else if (std::abs(delta_x(i)) < 1e-10) {
            D(i) = std::numeric_limits<double>::infinity();
        } else {
            D(i) = (std::ceil(x_0(i)) - x_0(i)) / delta_x(i);
        }
        if (std::abs(D(i)) < 1e-9 && std::abs(delta_x(i)) > 1e-9) {
            D(i) = 1.0 / std::abs(delta_x(i));
        }
    }
    D_0 = D;

    std::map<std::string, std::any> result;
    result["front_cells"] = front_cells();
    result["last_coordinates"] = coords();
    result["length_traversed"] = length();
    result["reached_goal"] = reached();
    return result;
}

Eigen::VectorXd NDRayTracer::coords() {
    if (norm_delta_x == 0) {
        return x_0;
    }
    return x_0 + (l / norm_delta_x) * delta_x;
}

std::vector<Eigen::VectorXi> NDRayTracer::front_cells() {
    std::vector<Eigen::VectorXi> cells;
    for (int i = 0; i < F.rows(); ++i) {
        cells.push_back(y + F.row(i).transpose());
    }
    return cells;
}

double NDRayTracer::length() {
    return l;
}

bool NDRayTracer::reached() {
    return D.minCoeff() >= 1.0;
}

std::map<std::string, std::any> NDRayTracer::next() {
    double min_D_value = D.minCoeff();
    std::vector<int> i_star_indices;
    for (int i = 0; i < n; ++i) {
        if (D(i) == min_D_value) {
            i_star_indices.push_back(i);
        }
    }

    for (int i_star : i_star_indices) {
        k(i_star)++;
    }

    l = min_D_value * norm_delta_x;

    for (int i_star : i_star_indices) {
        if (std::abs(delta_x(i_star)) > 1e-10) {
            D(i_star) = D_0(i_star) + (k(i_star) / std::abs(delta_x(i_star)));
        } else {
            D(i_star) = std::numeric_limits<double>::infinity();
        }
    }

    for (int i_star : i_star_indices) {
        y(i_star) += delta_x_sign(i_star);
    }

    t++;
    _determine_front_cells();

    std::map<std::string, std::any> result;
    result["front_cells"] = front_cells();
    result["last_coordinates"] = coords();
    result["length_traversed"] = length();
    result["reached_goal"] = reached();
    return result;
}

bool NDRayTracer::isHitObstacle(const Eigen::VectorXd& current_actual_coords, const std::vector<Eigen::VectorXi>& obstacles) {
    if (obstacles.empty()) {
        return false;
    }
    Eigen::VectorXi current_floored_coords(n);
    for(int i=0; i<n; ++i) {
        current_floored_coords(i) = std::floor(current_actual_coords(i) + 1e-8);
    }

    for (const auto& obs_coord : obstacles) {
        if (current_floored_coords.isApprox(obs_coord)) {
            return true;
        }
    }
    return false;
}

std::tuple<std::vector<Eigen::VectorXd>, std::vector<std::vector<Eigen::VectorXi>>, std::vector<Eigen::VectorXd>, std::vector<Eigen::VectorXi>, bool, bool> NDRayTracer::traverse(const Eigen::VectorXd& start, const Eigen::VectorXd& end, const std::vector<Eigen::VectorXi>& obstacles) {
    init(start, end);
    std::vector<Eigen::VectorXd> path;
    path.push_back(x_0);
    std::vector<std::vector<Eigen::VectorXi>> all_front_cells;
    all_front_cells.push_back(front_cells());
    std::vector<Eigen::VectorXd> intersection_coords;
    intersection_coords.push_back(x_0);

    bool obstacle_hit = false;
    bool goal_reached = false;

    if (isHitObstacle(x_0, obstacles)) {
        obstacle_hit = true;
        return std::make_tuple(path, all_front_cells, intersection_coords, y_coords_history, obstacle_hit, goal_reached);
    }

    if (x_0.isApprox(end)) {
        goal_reached = true;
        return std::make_tuple(path, all_front_cells, intersection_coords, y_coords_history, obstacle_hit, goal_reached);
    }

    while (!reached()) {
        auto step_info = next();
        Eigen::VectorXd new_coords = std::any_cast<Eigen::VectorXd>(step_info["last_coordinates"]);
        auto new_front_cells = std::any_cast<std::vector<Eigen::VectorXi>>(step_info["front_cells"]);

        path.push_back(new_coords);
        intersection_coords.push_back(new_coords);
        y_coords_history.push_back(y);
        all_front_cells.push_back(new_front_cells);

        if (isHitObstacle(new_coords, obstacles)) {
            obstacle_hit = true;
            break;
        }
    }

    if (!obstacle_hit) {
        path.push_back(end);
        goal_reached = true;
        if (isHitObstacle(end, obstacles)) {
            obstacle_hit = true;
        }
    }

    return std::make_tuple(path, all_front_cells, intersection_coords, y_coords_history, obstacle_hit, goal_reached);
}