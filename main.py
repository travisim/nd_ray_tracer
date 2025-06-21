import numpy as np
from nd_ray_tracer import NDRayTracer
from plotting import plot_2d_trace_with_proper_front_cells, plot_3d_trace_with_proper_front_cells

def analyze_front_cells(tracer, x_0, x_f):
    """
    Helper function to analyze and explain front cell calculation
    """
    print(f"\n=== Front Cell Analysis ===")
    print(f"Start: {x_0}, Goal: {x_f}")
    print(f"Delta_x: {tracer.delta_x}")
    print(f"Delta_x_sign: {tracer.delta_x_sign}")
    print(f"y (corner coords): {tracer.y}")
    print(f"F matrix (relative coords): \n{tracer.F}")
    
    front_cells = tracer.front_cells()
    print(f"Front cells coordinates:")
    for i, fc in enumerate(front_cells):
        print(f"  Cell {i}: {fc}")
    
    # Check which direction the ray is traveling
    print(f"\nRay direction analysis:")
    for i in range(len(tracer.delta_x)):
        direction = "positive" if tracer.delta_x[i] > 0 else "negative" if tracer.delta_x[i] < 0 else "zero"
        print(f"  Dimension {i}: {direction} (Δx={tracer.delta_x[i]:.3f})")

if __name__ == "__main__":
    # Comprehensive Test Suite
    tests = [
        # 2D Test Cases
        # {"dim": 2, "label": "Start Integer, Goal Float", "x_0": np.array([1, 1]), "x_f": np.array([4.5, 4.5]), "obstacles": [], "loose_dimension": 1},
        # {"dim": 2, "label": "Start Float, Goal Integer", "x_0": np.array([1.5, 1.5]), "x_f": np.array([4, 4]), "obstacles": [], "loose_dimension": 1},
        # {"dim": 2, "label": "Both Float", "x_0": np.array([1.5, 1.5]), "x_f": np.array([4.5, 4.5]), "obstacles": [], "loose_dimension": 1},
        # {"dim": 2, "label": "Both Float (different values)", "x_0": np.array([1.2, 1.8]), "x_f": np.array([5.7, 6.3]), "obstacles": [], "loose_dimension": 1},
        # {"dim": 2, "label": "Both Integer", "x_0": np.array([1, 1]), "x_f": np.array([4, 4]), "obstacles": [], "loose_dimension": 1},
        # {"dim": 2, "label": "Vertical", "x_0": np.array([2, 1]), "x_f": np.array([2, 5]), "obstacles": [], "loose_dimension": 1},
        # {"dim": 2, "label": "Horizontal", "x_0": np.array([1, 2]), "x_f": np.array([5, 2]), "obstacles": [], "loose_dimension": 1},
        # {"dim": 2, "label": "Diagonal", "x_0": np.array([1, 1]), "x_f": np.array([5, 5]), "obstacles": [], "loose_dimension": 1},
        # {"dim": 2, "label": "45-degree", "x_0": np.array([1, 1]), "x_f": np.array([5, 5]), "obstacles": [], "loose_dimension": 1},
        # {"dim": 2, "label": "End at Goal which is Obstacle", "x_0": np.array([1, 1]), "x_f": np.array([3, 3]), "obstacles": [np.array([3, 3])], "loose_dimension": 1},
        # {"dim": 2, "label": "Start and Goal is Same", "x_0": np.array([2, 2]), "x_f": np.array([2, 2]), "obstacles": [], "loose_dimension": 1},
        # {"dim": 2, "label": "Start and Goal is Same but at Obstacle", "x_0": np.array([2, 2]), "x_f": np.array([2, 2]), "obstacles": [np.array([2, 2])], "loose_dimension": 1},
        # {"dim": 2, "label": "Start at Obstacle", "x_0": np.array([1, 1]), "x_f": np.array([5, 5]), "obstacles": [np.array([1, 1])], "loose_dimension": 1},
        # {"dim": 2, "label": "Start at Obstacle", "x_0": np.array([0, 0]), "x_f": np.array([4, 4]), "obstacles": [np.array([0, 1]),np.array([1, 0])], "loose_dimension": 1},

        # # 2D Cardinal Directions
        # {"dim": 2, "label": "North", "x_0": np.array([2.5, 1.5]), "x_f": np.array([2.5, 5.5]), "obstacles": [], "loose_dimension": 1},
        # {"dim": 2, "label": "South", "x_0": np.array([2.5, 5.5]), "x_f": np.array([2.5, 1.5]), "obstacles": [], "loose_dimension": 1},
        # {"dim": 2, "label": "East", "x_0": np.array([1.5, 2.5]), "x_f": np.array([5.5, 2.5]), "obstacles": [], "loose_dimension": 1},
        # {"dim": 2, "label": "West", "x_0": np.array([5.5, 2.5]), "x_f": np.array([1.5, 2.5]), "obstacles": [], "loose_dimension": 1},
        # # 2D Quadrants
        # {"dim": 2, "label": "Quadrant 1 (NE)", "x_0": np.array([1.5, 1.5]), "x_f": np.array([5.5, 5.5]), "obstacles": [], "loose_dimension": 1},
        # {"dim": 2, "label": "Quadrant 2 (NW)", "x_0": np.array([5.5, 1.5]), "x_f": np.array([1.5, 5.5]), "obstacles": [], "loose_dimension": 1},
        # {"dim": 2, "label": "Quadrant 3 (SW)", "x_0": np.array([5.5, 5.5]), "x_f": np.array([1.5, 1.5]), "obstacles": [], "loose_dimension": 1},
        # {"dim": 2, "label": "Quadrant 4 (SE)", "x_0": np.array([1.5, 5.5]), "x_f": np.array([5.5, 1.5]), "obstacles": [], "loose_dimension": 1},

        # # 3D Test Cases
        # {"dim": 3, "label": "Start Integer, Goal Float", "x_0": np.array([1, 1, 1]), "x_f": np.array([4.5, 4.5, 4.5]), "obstacles": [], "loose_dimension": 1},
        # {"dim": 3, "label": "Start Float, Goal Integer", "x_0": np.array([1.5, 1.5, 1.5]), "x_f": np.array([4, 4, 4]), "obstacles": [], "loose_dimension": 1},
        # {"dim": 3, "label": "Both Float", "x_0": np.array([1.5, 1.5, 1.5]), "x_f": np.array([4.5, 4.5, 4.5]), "obstacles": [], "loose_dimension": 1},
        # {"dim": 3, "label": "Both Float (different values)", "x_0": np.array([1.2, 1.8, 1.1]), "x_f": np.array([5.7, 6.3, 5.9]), "obstacles": [], "loose_dimension": 1},
        # {"dim": 3, "label": "Both Integer", "x_0": np.array([1, 1, 1]), "x_f": np.array([4, 4, 4]), "obstacles": [], "loose_dimension": 1},
        # {"dim": 3, "label": "Vertical", "x_0": np.array([2, 2, 1]), "x_f": np.array([2, 2, 5]), "obstacles": [], "loose_dimension": 1},
        # {"dim": 3, "label": "Horizontal (along x-axis)", "x_0": np.array([1, 2, 2]), "x_f": np.array([5, 2, 2]), "obstacles": [], "loose_dimension": 1},
        # {"dim": 3, "label": "Diagonal", "x_0": np.array([1, 1, 1]), "x_f": np.array([5, 5, 5]), "obstacles": [], "loose_dimension": 2},
        # {"dim": 3, "label": "45-degree (in xy-plane)", "x_0": np.array([1, 1, 1]), "x_f": np.array([5, 5, 1]), "obstacles": [], "loose_dimension": 1},
        # {"dim": 3, "label": "End at Goal which is Obstacle", "x_0": np.array([1, 1, 1]), "x_f": np.array([3, 3, 3]), "obstacles": [np.array([3, 3, 3])], "loose_dimension": 1},
        # {"dim": 3, "label": "Start and Goal is Same", "x_0": np.array([2, 2, 2]), "x_f": np.array([2, 2, 2]), "obstacles": [], "loose_dimension": 1},
        # {"dim": 3, "label": "Start and Goal is Same but at Obstacle", "x_0": np.array([2, 2, 2]), "x_f": np.array([2, 2, 2]), "obstacles": [np.array([2, 2, 2])], "loose_dimension": 1},
        # {"dim": 3, "label": "Start at Obstacle", "x_0": np.array([1, 1, 1]), "x_f": np.array([5, 5, 5]), "obstacles": [np.array([1, 1, 1])], "loose_dimension": 1},
        # # 3D Cardinal Directions
        # {"dim": 3, "label": "Up", "x_0": np.array([2.5, 2.5, 1.5]), "x_f": np.array([2.5, 2.5, 5.5]), "obstacles": [], "loose_dimension": 1},
        # {"dim": 3, "label": "Down", "x_0": np.array([2.5, 2.5, 5.5]), "x_f": np.array([2.5, 2.5, 1.5]), "obstacles": [], "loose_dimension": 1},
        # # 3D Octants
        # {"dim": 3, "label": "Octant 1 (+,+,+)", "x_0": np.array([1.5, 1.5, 1.5]), "x_f": np.array([5.5, 5.5, 5.5]), "obstacles": [], "loose_dimension": 1},
        # {"dim": 3, "label": "Octant 2 (-,+,+)", "x_0": np.array([5.5, 1.5, 1.5]), "x_f": np.array([1.5, 5.5, 5.5]), "obstacles": [], "loose_dimension": 1},
        # {"dim": 3, "label": "Octant 3 (-,-,+)", "x_0": np.array([5.5, 5.5, 1.5]), "x_f": np.array([1.5, 1.5, 5.5]), "obstacles": [], "loose_dimension": 1},
        # {"dim": 3, "label": "Octant 4 (+,-,+)", "x_0": np.array([1.5, 5.5, 1.5]), "x_f": np.array([5.5, 1.5, 5.5]), "obstacles": [], "loose_dimension": 1},
        # {"dim": 3, "label": "Octant 5 (+,+,-)", "x_0": np.array([1.5, 1.5, 5.5]), "x_f": np.array([5.5, 5.5, 1.5]), "obstacles": [], "loose_dimension": 1},
        # {"dim": 3, "label": "Octant 6 (-,+,-)", "x_0": np.array([5.5, 1.5, 5.5]), "x_f": np.array([1.5, 5.5, 1.5]), "obstacles": [], "loose_dimension": 1},
        # {"dim": 3, "label": "Octant 7 (-,-,-)", "x_0": np.array([5.5, 5.5, 5.5]), "x_f": np.array([1.5, 1.5, 1.5]), "obstacles": [], "loose_dimension": 1},
        # {"dim": 3, "label": "Octant 8 (+,-,-)", "x_0": np.array([1.5, 5.5, 5.5]), "x_f": np.array([5.5, 1.5, 1.5]), "obstacles": [], "loose_dimension": 1},
        
        # 3D Obstacle Test Case
  
        #   {"dim": 3, "label": "Surrounded Obstacle", "x_0": np.array([0, 0, 0]), "x_f": np.array([4, 4, 4]), "obstacles": [
        #     np.array([2, 1, 2]), np.array([1, 2, 2]), np.array([2, 2, 1]),
           
        # ], "loose_dimension": 1},
        #  {"dim": 3, "label": "Surrounded Obstacle", "x_0": np.array([0, 0, 0]), "x_f": np.array([4, 4, 4]), "obstacles": [
        #     np.array([2, 1, 2]), np.array([1, 2, 2]),
           
        # ], "loose_dimension": 1},
        #  {"dim": 3, "label": "Surrounded Obstacle", "x_0": np.array([0, 0, 0]), "x_f": np.array([4, 4, 4]), "obstacles": [
        #     np.array([2, 1, 2]), np.array([1, 2, 2]), np.array([2, 2, 1]),
           
        # ], "loose_dimension": 2},

        # {"dim": 3, "label": "Surrounded Obstacle", "x_0": np.array([0, 0, 0]), "x_f": np.array([4, 4, 4]), "obstacles": [
        #      np.array([1, 1, 2]), np.array([1, 2, 1]), np.array([2, 1, 1]), np.array([2, 1, 2]), np.array([1, 2, 2]), np.array([2, 2, 1]),
           
        # ], "loose_dimension": 2},
      
# {"dim": 3, "label": "1D Change (X-axis)", "x_0": np.array([0, 0, 0]), "x_f": np.array([0, 4, 4]), "obstacles": [np.array([-1, 1, 2]),np.array([0, 1, 2]),np.array([-1, 2, 1]),np.array([0, 2, 1])], "loose_dimension": 1},

        {"dim": 3, "label": "Ray along Y-axis with obstacles", "x_0": np.array([2, 0, 3]), "x_f": np.array([2, 5, 3]), "obstacles": [np.array([1, 1, 3]), np.array([1, 2, 3]), np.array([1, 3, 3]), np.array([1, 4, 3]), np.array([2, 1, 2]), np.array([2, 2, 2]), np.array([2, 3, 2]), np.array([2, 4, 2]), np.array([2, 2, 3]),np.array([1, 3, 2])], "loose_dimension": 2},
# {"dim": 3, "label": "1D Change (X-axis)", "x_0": np.array([0, 0, 0]), "x_f": np.array([0, 6, 6]), "obstacles": [np.array([-1, 0, 0]),np.array([-1, 1, 1]),np.array([-1, 2, 2])], "loose_dimension": 2},

# {"dim": 3, "label": "1D Change (X-axis)", "x_0": np.array([0, 0, 0]), "x_f": np.array([0, 4, 4]), "obstacles": [np.array([-1, 1, 2]),np.array([0, 1, 2]),np.array([-1, 2, 1]),np.array([0, 2, 1])], "loose_dimension": 2},



# {"dim": 3, "label": "1D Change (X-axis)", "x_0": np.array([0.5, 0.5, 0.5]), "x_f": np.array([0.5, 4.5, 4.5]), "obstacles": [np.array([0, 1, 2]),np.array([0, 2, 1])], "loose_dimension": 1},
# {"dim": 3, "label": "1D Change (X-axis)", "x_0": np.array([0.5, 0.5, 0.5]), "x_f": np.array([0.5, 4.5, 4.5]), "obstacles": [np.array([0, 1, 2]),np.array([0, 2, 1])], "loose_dimension": 2},

# {"dim": 3, "label": "1D Change (Y-axis)", "x_0": np.array([0.5, 0.5, 0.5]), "x_f": np.array([0.5, 0.5, 4.5]), "obstacles": [np.array([1, 0, 2]),np.array([2, 0, 1])], "loose_dimension": 1},
# {"dim": 3, "label": "1D Change (Y-axis)", "x_0": np.array([0.5, 0.5, 0.5]), "x_f": np.array([0.5, 0.5, 4.5]), "obstacles": [np.array([1, 0, 2]),np.array([2, 0, 1])], "loose_dimension": 2},




# {"dim": 3, "label": "1D Change (Y-axis)", "x_0": np.array([2.5, 0.5, 2.5]), "x_f": np.array([2.5, 4.5, 2.5]), "obstacles": [np.array([2, 2, 2])], "loose_dimension": 1},
# {"dim": 3, "label": "1D Change (Z-axis)", "x_0": np.array([2.5, 2.5, 0.5]), "x_f": np.array([2.5, 2.5, 4.5]), "obstacles": [np.array([2, 2, 2])], "loose_dimension": 1},
# {"dim": 3, "label": "2D Change (XY-plane)", "x_0": np.array([0.5, 0.5, 2.5]), "x_f": np.array([4.5, 4.5, 2.5]), "obstacles": [np.array([2, 2, 2])], "loose_dimension": 1},
# {"dim": 3, "label": "2D Change (XZ-plane)", "x_0": np.array([0.5, 2.5, 0.5]), "x_f": np.array([4.5, 2.5, 4.5]), "obstacles": [np.array([2, 2, 2])], "loose_dimension": 1},
# {"dim": 3, "label": "2D Change (YZ-plane)", "x_0": np.array([2.5, 0.5, 0.5]), "x_f": np.array([2.5, 4.5, 4.5]), "obstacles": [np.array([2, 2, 2])], "loose_dimension": 1},
# {"dim": 3, "label": "Goal in Obstacle", "x_0": np.array([0.5, 0.5, 0.5]), "x_f": np.array([2.5, 2.5, 2.5]), "obstacles": [np.array([2, 2, 2])], "loose_dimension": 1},
]


for test in tests:
        print(f"\n{'='*60}")
        print(f"Testing {test['dim']}D: {test['label']}")
        print(f"Start: {test['x_0']}, Goal: {test['x_f']}, Obstacles: {test['obstacles']}")
        print(f"{'='*60}")

        tracer = NDRayTracer()
        path, front_cells, intersections, y_history, hit, goal_reached = tracer.traverse(
            test['x_0'], test['x_f'], test['obstacles'], loose_dimension=test.get('loose_dimension', 0)
        )

        analyze_front_cells(tracer, test['x_0'], test['x_f'])

        print(f"\nTraversal Results for {test['label']}:")
        print(f"  Obstacle hit: {hit}")
        print(f"  Goal reached: {goal_reached}")

        if test['dim'] == 2:
            title = f"2D Test: {test['label']}\nStart: {np.round(test['x_0'], 2)}, Goal: {np.round(test['x_f'], 2)}, Loose: {test.get('loose_dimension', 0)}"
            plot_2d_trace_with_proper_front_cells(
                test['x_0'], test['x_f'],
                path, front_cells, intersections, y_history,
                test['obstacles'],
                title=title
            )
        elif test['dim'] == 3:
            title = f"3D Test: {test['label']}\nStart: {np.round(test['x_0'], 2)}, Goal: {np.round(test['x_f'], 2)}, Loose: {test.get('loose_dimension', 0)}"
            plot_3d_trace_with_proper_front_cells(
                test['x_0'], test['x_f'],
                path, front_cells, intersections, y_history,
                test['obstacles'],
                isGoalReached=goal_reached,
                title=title
            )