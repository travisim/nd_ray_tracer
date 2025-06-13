#ifndef ND_RAY_TRACER_H
#define ND_RAY_TRACER_H

#include <vector>
#include <Eigen/Dense>
#include <string>
#include <map>
#include <any>

class NDRayTracer {
public:
    NDRayTracer();

    std::map<std::string, std::any> init(const Eigen::VectorXd& x_0, const Eigen::VectorXd& x_f);
    std::map<std::string, std::any> next();
    std::tuple<std::vector<Eigen::VectorXd>, std::vector<std::vector<Eigen::VectorXi>>, std::vector<Eigen::VectorXd>, std::vector<Eigen::VectorXi>, bool, bool> traverse(const Eigen::VectorXd& x_0, const Eigen::VectorXd& x_f, const std::vector<Eigen::VectorXi>& obstacles);
    
    Eigen::VectorXd coords();
    std::vector<Eigen::VectorXi> front_cells();
    double length();
    bool reached();

private:
    Eigen::VectorXd x_0;
    Eigen::VectorXd delta_x;
    Eigen::VectorXd abs_delta_x;
    double norm_delta_x;
    Eigen::VectorXi delta_x_sign;
    Eigen::VectorXi k;
    Eigen::VectorXd D;
    Eigen::VectorXd D_0;
    Eigen::VectorXi y;
    Eigen::MatrixXi F;
    double l;
    int t;
    int n;
    std::vector<Eigen::VectorXi> y_coords_history;
    std::vector<Eigen::VectorXi> F_list;

    Eigen::VectorXi _floor_ceil_conditional(const Eigen::VectorXd& a, const Eigen::VectorXd& b);
    int _sign(double x);
    void _determine_front_cells();
    void _determine_front_cells_recursive(int dim, Eigen::VectorXi& current_f);
    bool isHitObstacle(const Eigen::VectorXd& current_actual_coords, const std::vector<Eigen::VectorXi>& obstacles);
};

#endif // ND_RAY_TRACER_H