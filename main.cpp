#include <iostream>
#include <vector>
#include <string>
#include <Eigen/Dense>
#include "nd_ray_tracer.h"
#include "plotting.h"

struct Test {
    int dim;
    std::string label;
    Eigen::VectorXd x_0;
    Eigen::VectorXd x_f;
    std::vector<Eigen::VectorXi> obstacles;
};

void run_test(const Test& test) {
    std::cout << "\n============================================================\n";
    std::cout << "Testing " << test.dim << "D: " << test.label << "\n";
    std::cout << "Start: " << test.x_0.transpose() << "\n";
    std::cout << "Goal: " << test.x_f.transpose() << "\n";
    std::cout << "============================================================\n";

    NDRayTracer tracer;
    auto [path, front_cells, intersections, y_history, hit, goal_reached] = tracer.traverse(test.x_0, test.x_f, test.obstacles);

    std::cout << "\nTraversal Results for " << test.label << ":\n";
    std::cout << "  Obstacle hit: " << (hit ? "true" : "false") << "\n";
    std::cout << "  Goal reached: " << (goal_reached ? "true" : "false") << "\n";

    std::string title = std::to_string(test.dim) + "D Test - " + test.label;
    if (test.dim == 2) {
        plot_2d_trace(title, test.x_0, test.x_f, path, front_cells, intersections, y_history, test.obstacles);
    } else if (test.dim == 3) {
        plot_3d_trace(title, test.x_0, test.x_f, path, front_cells, intersections, y_history, test.obstacles);
        plot_2d_projection(title + " (XY)", test.x_0, test.x_f, path, front_cells, intersections, y_history, test.obstacles, 0, 1);
        plot_2d_projection(title + " (YZ)", test.x_0, test.x_f, path, front_cells, intersections, y_history, test.obstacles, 1, 2);
        plot_2d_projection(title + " (XZ)", test.x_0, test.x_f, path, front_cells, intersections, y_history, test.obstacles, 0, 2);
    }
}

int main() {
    std::vector<Test> tests = {
        // 2D Test Cases
        {2, "Start Integer, Goal Float", (Eigen::Vector2d() << 1, 1).finished(), (Eigen::Vector2d() << 4.5, 4.5).finished(), {}},
        {2, "Start Float, Goal Integer", (Eigen::Vector2d() << 1.5, 1.5).finished(), (Eigen::Vector2d() << 4, 4).finished(), {}},
        {2, "Both Float", (Eigen::Vector2d() << 1.5, 1.5).finished(), (Eigen::Vector2d() << 4.5, 4.5).finished(), {}},
        {2, "Both Float (different values)", (Eigen::Vector2d() << 1.2, 1.8).finished(), (Eigen::Vector2d() << 5.7, 6.3).finished(), {}},
        {2, "Both Integer", (Eigen::Vector2d() << 1, 1).finished(), (Eigen::Vector2d() << 4, 4).finished(), {}},
        {2, "Vertical", (Eigen::Vector2d() << 2, 1).finished(), (Eigen::Vector2d() << 2, 5).finished(), {}},
        {2, "Horizontal", (Eigen::Vector2d() << 1, 2).finished(), (Eigen::Vector2d() << 5, 2).finished(), {}},
        {2, "Diagonal", (Eigen::Vector2d() << 1, 1).finished(), (Eigen::Vector2d() << 5, 5).finished(), {}},
        {2, "45-degree", (Eigen::Vector2d() << 1, 1).finished(), (Eigen::Vector2d() << 5, 5).finished(), {}},
        {2, "End at Goal which is Obstacle", (Eigen::Vector2d() << 1, 1).finished(), (Eigen::Vector2d() << 3, 3).finished(), {(Eigen::Vector2i() << 3, 3).finished()}},
        {2, "Start and Goal is Same", (Eigen::Vector2d() << 2, 2).finished(), (Eigen::Vector2d() << 2, 2).finished(), {}},
        {2, "Start and Goal is Same but at Obstacle", (Eigen::Vector2d() << 2, 2).finished(), (Eigen::Vector2d() << 2, 2).finished(), {(Eigen::Vector2i() << 2, 2).finished()}},
        {2, "Start at Obstacle", (Eigen::Vector2d() << 1, 1).finished(), (Eigen::Vector2d() << 5, 5).finished(), {(Eigen::Vector2i() << 1, 1).finished()}},
        // 2D Cardinal Directions
        {2, "North", (Eigen::Vector2d() << 2.5, 1.5).finished(), (Eigen::Vector2d() << 2.5, 5.5).finished(), {}},
        {2, "South", (Eigen::Vector2d() << 2.5, 5.5).finished(), (Eigen::Vector2d() << 2.5, 1.5).finished(), {}},
        {2, "East", (Eigen::Vector2d() << 1.5, 2.5).finished(), (Eigen::Vector2d() << 5.5, 2.5).finished(), {}},
        {2, "West", (Eigen::Vector2d() << 5.5, 2.5).finished(), (Eigen::Vector2d() << 1.5, 2.5).finished(), {}},
        // 2D Quadrants
        {2, "Quadrant 1 (NE)", (Eigen::Vector2d() << 1.5, 1.5).finished(), (Eigen::Vector2d() << 5.5, 5.5).finished(), {}},
        {2, "Quadrant 2 (NW)", (Eigen::Vector2d() << 5.5, 1.5).finished(), (Eigen::Vector2d() << 1.5, 5.5).finished(), {}},
        {2, "Quadrant 3 (SW)", (Eigen::Vector2d() << 5.5, 5.5).finished(), (Eigen::Vector2d() << 1.5, 1.5).finished(), {}},
        {2, "Quadrant 4 (SE)", (Eigen::Vector2d() << 1.5, 5.5).finished(), (Eigen::Vector2d() << 5.5, 1.5).finished(), {}},

        // 3D Test Cases
        {3, "Start Integer, Goal Float", (Eigen::Vector3d() << 1, 1, 1).finished(), (Eigen::Vector3d() << 4.5, 4.5, 4.5).finished(), {}},
        {3, "Start Float, Goal Integer", (Eigen::Vector3d() << 1.5, 1.5, 1.5).finished(), (Eigen::Vector3d() << 4, 4, 4).finished(), {}},
        {3, "Both Float", (Eigen::Vector3d() << 1.5, 1.5, 1.5).finished(), (Eigen::Vector3d() << 4.5, 4.5, 4.5).finished(), {}},
        {3, "Both Float (different values)", (Eigen::Vector3d() << 1.2, 1.8, 1.1).finished(), (Eigen::Vector3d() << 5.7, 6.3, 5.9).finished(), {}},
        {3, "Both Integer", (Eigen::Vector3d() << 1, 1, 1).finished(), (Eigen::Vector3d() << 4, 4, 4).finished(), {}},
        {3, "Vertical", (Eigen::Vector3d() << 2, 2, 1).finished(), (Eigen::Vector3d() << 2, 2, 5).finished(), {}},
        {3, "Horizontal (along x-axis)", (Eigen::Vector3d() << 1, 2, 2).finished(), (Eigen::Vector3d() << 5, 2, 2).finished(), {}},
        {3, "Diagonal", (Eigen::Vector3d() << 1, 1, 1).finished(), (Eigen::Vector3d() << 5, 5, 5).finished(), {}},
        {3, "45-degree (in xy-plane)", (Eigen::Vector3d() << 1, 1, 1).finished(), (Eigen::Vector3d() << 5, 5, 1).finished(), {}},
        {3, "End at Goal which is Obstacle", (Eigen::Vector3d() << 1, 1, 1).finished(), (Eigen::Vector3d() << 3, 3, 3).finished(), {(Eigen::Vector3i() << 3, 3, 3).finished()}},
        {3, "Start and Goal is Same", (Eigen::Vector3d() << 2, 2, 2).finished(), (Eigen::Vector3d() << 2, 2, 2).finished(), {}},
        {3, "Start and Goal is Same but at Obstacle", (Eigen::Vector3d() << 2, 2, 2).finished(), (Eigen::Vector3d() << 2, 2, 2).finished(), {(Eigen::Vector3i() << 2, 2, 2).finished()}},
        {3, "Start at Obstacle", (Eigen::Vector3d() << 1, 1, 1).finished(), (Eigen::Vector3d() << 5, 5, 5).finished(), {(Eigen::Vector3i() << 1, 1, 1).finished()}},
        // 3D Cardinal Directions
        {3, "Up", (Eigen::Vector3d() << 2.5, 2.5, 1.5).finished(), (Eigen::Vector3d() << 2.5, 2.5, 5.5).finished(), {}},
        {3, "Down", (Eigen::Vector3d() << 2.5, 2.5, 5.5).finished(), (Eigen::Vector3d() << 2.5, 2.5, 1.5).finished(), {}},
        // 3D Octants
        {3, "Octant 1 (+,+,+)", (Eigen::Vector3d() << 1.5, 1.5, 1.5).finished(), (Eigen::Vector3d() << 5.5, 5.5, 5.5).finished(), {}},
        {3, "Octant 2 (-,+,+)", (Eigen::Vector3d() << 5.5, 1.5, 1.5).finished(), (Eigen::Vector3d() << 1.5, 5.5, 5.5).finished(), {}},
        {3, "Octant 3 (-,-,+)", (Eigen::Vector3d() << 5.5, 5.5, 1.5).finished(), (Eigen::Vector3d() << 1.5, 1.5, 5.5).finished(), {}},
        {3, "Octant 4 (+,-,+)", (Eigen::Vector3d() << 1.5, 5.5, 1.5).finished(), (Eigen::Vector3d() << 5.5, 1.5, 5.5).finished(), {}},
        {3, "Octant 5 (+,+,-)", (Eigen::Vector3d() << 1.5, 1.5, 5.5).finished(), (Eigen::Vector3d() << 5.5, 5.5, 1.5).finished(), {}},
        {3, "Octant 6 (-,+,-)", (Eigen::Vector3d() << 5.5, 1.5, 5.5).finished(), (Eigen::Vector3d() << 1.5, 5.5, 1.5).finished(), {}},
        {3, "Octant 7 (-,-,-)", (Eigen::Vector3d() << 5.5, 5.5, 5.5).finished(), (Eigen::Vector3d() << 1.5, 1.5, 1.5).finished(), {}},
        {3, "Octant 8 (+,-,-)", (Eigen::Vector3d() << 1.5, 5.5, 5.5).finished(), (Eigen::Vector3d() << 5.5, 1.5, 1.5).finished(), {}},
    };

    for (const auto& test : tests) {
        run_test(test);
    }

    return 0;
}