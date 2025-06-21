import numpy as np
import itertools
from typing import List, Tuple, Optional, Dict, Any

def round2(x):
    """
    Rounds a float, int, or numpy array to 2 decimal places.
    """
    if isinstance(x, (float, int)):
        return round(x, 2)
    elif isinstance(x, np.ndarray):
        return np.round(x, 2)
    elif isinstance(x, list):
        return [round2(i) for i in x]
    else:
        return x

class NDRayTracer:
    """
    N-Dimensional Ray Tracer with corrected front cell implementation
    Each method and variable corresponds to sections in raytracer.pdf
    """
    
    def __init__(self):
        self.x_0 = None          # 1. Starting coordinates 
        self.delta_x = None      # 2. Δx, Difference between goal and start coordinates, 
        self.abs_delta_x = None  # 3. |Δx|, absolute value of Δx  
        self.norm_delta_x = None # 4. ||Δx||,  total length of ray, 
        self.delta_x_sign = None # 5. Vector of Sign, direction ray is cast, δx signum
        self.k = None            # 6. Vector of number of times ray crossed grid hyperplane aka counters of |Δx| in different dimensions
        self.D = None            # 7. Vector of distance of current point to the start for each hyperplace cross
        self.D_0 = None          # 8. Initial D values
        self.y = None            # 9. Current corner coordinates from which front cells derived
        self.F = None            # 10.Vector of relative coordinates of front cells
        self.l = 0               # 11. Total Length of ray
        self.t = 0               # Current step
        self.n = 0               # Number of dimensions
        self.y_coords_history = []  # History of y coordinates for each step

    def init(self, x_0: np.ndarray, x_f: np.ndarray):
        """
        Initialization function as described in PDF section "The steps for init(x_s, x_f)"
        """
        self.x_0 = np.array(x_0, dtype=float)
        x_f = np.array(x_f, dtype=float)
        self.n = len(x_0)
        self.t = 0
        
        # Step 1: Δx = x_f - x_s
        self.delta_x = x_f - self.x_0

        # Step 2: Calculate |Δx|
        self.abs_delta_x = np.abs(self.delta_x)
        
        # Step 3: Calculate δx (sign vector)
        self.delta_x_sign = np.array([self._sign(dx) for dx in self.delta_x])
        
        # Step 4: l^(0) = 0
        self.l = 0
        
        # Step 5: k^(0) = 0 vector
        self.k = np.zeros(self.n, dtype=int)
        
        # Step 6: Calculate D_i^(0) based on PDF formula
        self.norm_delta_x = np.linalg.norm(self.delta_x)  # ||Δx||
        # Step 7: y^(0) = [x_0 | -Δx] (conditional floor/ceiling)
        self.y = self._floor_ceil_conditional(self.x_0, -self.delta_x).astype(int)
        self.y_coords_history.append(self.y.copy())  # Initialize history with the first y value
        # Step 8: Determine F - front cells matrix
        self._determine_front_cells()
           # Calculate return values at the end

        all_front_cells = [self.front_cells()]

        self.D = np.zeros(self.n)
        self.D_0 = np.zeros(self.n)
        self.frontCellsInit = []
        self.init_coords = []
        for i in range(self.n):
            if self.delta_x[i] < 0:
                # (⌊x_{s,i}⌋ - x_{s,i}) / Δx_i when Δx_i < 0
                self.D[i] = (np.floor(self.x_0[i]) - self.x_0[i]) / self.delta_x[i]
            elif abs(self.delta_x[i]) < 1e-10:
                # ∞ when Δx_i = 0
                self.D[i] = float('inf')
            else: # self.delta_x[i] > 0
                # (⌈x_{s,i}⌉ - x_{s,i}) / Δx_i when Δx_i > 0
                self.D[i] = (np.ceil(self.x_0[i]) - self.x_0[i]) / self.delta_x[i]

            # If starting on a grid line, D[i] will be 0 or very close to it.
            # The next intersection should be one full grid cell away.
            if abs(self.D[i]) < 1e-9 and abs(self.delta_x[i]) > 1e-9:
                self.D[i] = 1.0 / abs(self.delta_x[i])
        self.D_0 = self.D.copy()
        
        all_front_cells.extend(self.frontCellsInit)
        current_front_cells = all_front_cells
        current_coords =  self.init_coords
        current_length = self.length()
        goal_reached = self.reached()

        return {
            "front_cells": current_front_cells,
            "last_coordinates": current_coords,
            "length_traversed": current_length,
            "reached_goal": goal_reached
        }
        
    def _floor_ceil_conditional(self, a: np.ndarray, b: np.ndarray) -> np.ndarray:
        """
        PDF operator 3: c = [a | b] - elementwise ceiling or flooring
        depending on element in b at same position
        """
        result = np.zeros_like(a)
        for i in range(len(a)):
            if b[i] <= 0:
                result[i] = np.floor(a[i])
            else:
                result[i] = np.ceil(a[i])
        return result
    
    def _sign(self, x: float) -> int:
        """
        Sign function as defined in PDF variable 5
        """
        if x > 0:
            return 1
        elif x == 0:
            return 0
        else:
            return -1
    


    def _determine_front_cells(self):
        """
        Determines front cells using a recursive approach.
        """
        self.F_list = []
        self._determine_front_cells_recursive(0, np.zeros(self.n, dtype=int))
        self.F = np.array(self.F_list)

    def _determine_front_cells_recursive(self, dim, current_f):
        if dim == self.n:
            self.F_list.append(current_f.copy())
            return

        is_delta_x_zero = abs(self.delta_x[dim]) < 1e-10
        is_x0_integer = abs(self.x_0[dim] - round(self.x_0[dim])) < 1e-10

        if is_delta_x_zero and is_x0_integer:
            # Branch for h = -1
            current_f[dim] = -1
            self._determine_front_cells_recursive(dim + 1, current_f)
            
            # Branch for h = 1 (which maps to f = 0)
            current_f[dim] = 0
            self._determine_front_cells_recursive(dim + 1, current_f)
        else:
            if self.delta_x_sign[dim] < 0:
                current_f[dim] = -1
            else:
                current_f[dim] = 0
            self._determine_front_cells_recursive(dim + 1, current_f)

    def coords(self) -> np.ndarray:
        """
        PDF Dynamic function 1: Returns current intercept coordinates
        x^(t) = x_0 + (l^(t) / ||Δx||) * Δx
        """
        if self.norm_delta_x == 0:
            return self.x_0.copy()
        return self.x_0 + (self.l / self.norm_delta_x) * self.delta_x
    
    def front_cells(self) -> List[np.ndarray]:
        """
        PDF Dynamic function 2: Returns coordinates of front cells
        These are the cells that the ray will enter next from current position
        """
        cells = []
        for f_j in self.F:
            cell_coord = self.y + f_j
            cells.append(cell_coord)
        return cells
    
    def length(self) -> float:
        """
        PDF Dynamic function 3: Returns current length travelled
        """
        return self.l
    
    def reached(self) -> bool:
        """
        PDF Dynamic function 4: Returns true if ray reached goal
        True if min D_i^(t) >= 1
        """
        return np.min(self.D) >= 1.0
    


    def _calculate_search_space(self, all_front_cells: List[np.ndarray]) -> List[Tuple[int, ...]]:
        """
        Calculates a bounding box search space based on all front cells provided.
        """
        if not all_front_cells:
            return []

        all_cells = np.vstack(all_front_cells)
        min_coords = np.min(all_cells, axis=0).astype(int)
        max_coords = np.max(all_cells, axis=0).astype(int)
        
        # Create a grid of all integer coordinates within the bounding box
        ranges = [range(min_c, max_c + 1) for min_c, max_c in zip(min_coords, max_coords)]
        
        return list(itertools.product(*ranges))

    def _generate_loose_dimensions_offsets(self, source_cell: np.ndarray, target_cell: np.ndarray, loose_dimension: int) -> List[np.ndarray]:
        """
        Generates offsets from a source cell towards a target cell.
        It creates offsets for all dimensional changes from 1 up to loose_dimension.
        """

             #loose dimension cannot be zero and must be less than or equal the number of dimensions
        if loose_dimension <= 0 or loose_dimension > self.n:
            raise ValueError("loose_dimension must be between 1 and the number of dimensions (inclusive)")
        
        diff = np.array(target_cell) - np.array(source_cell)
        change_dims = [i for i, d in enumerate(diff) if d != 0]
        
        all_offsets = []
        
        for i in range(1, loose_dimension + 1):
            if len(change_dims) < i:
                break  # Cannot form combinations of size i

            for dims_to_change in itertools.combinations(change_dims, i):
                offset = np.zeros(self.n, dtype=int)
                for dim in dims_to_change:
                    offset[dim] = diff[dim]
                all_offsets.append(offset)
                
        return all_offsets

    def _dfs_path_exists(self, start_cell: tuple, end_cells: set, search_space: set, obstacle_set: set, loose_dimension: int) -> bool:
        """
        Performs a Depth-First Search to find a path from a start cell to any of the end cells.
        Neighbors are generated using _generate_loose_dimensions_offsets, guiding the search towards the end cells.
        """
        if start_cell in obstacle_set:
            return False
            
        stack = [start_cell]
        visited = {start_cell}

        while stack:
            current_cell = stack.pop()

            if current_cell in end_cells:
                return True  # Path found

            # Generate neighbors by trying to move towards each end cell
            for end_cell in end_cells:
                if current_cell == end_cell:
                    continue

                offsets = self._generate_loose_dimensions_offsets(np.array(current_cell), np.array(end_cell), loose_dimension)
                for offset in offsets:
                    neighbor = tuple(np.array(current_cell) + offset)

                    if neighbor in search_space and neighbor not in visited:
                        visited.add(neighbor)
                        stack.append(neighbor)
        
        return False

    def isHitObstacle(self, prev_coords: np.ndarray, prev_front_cells: List[np.ndarray], current_coords: np.ndarray, current_front_cells: List[np.ndarray], obstacles: Optional[List[np.ndarray]], loose_dimension: int = 0) -> bool:
        if not obstacles:
            return False
        #if prev and current coordinates are the same, no obstacle hit
        if np.array_equal(prev_coords, current_coords):
            return False

        obstacle_set = {tuple(obs) for obs in obstacles}
        current_cell_coords = tuple(np.floor(current_coords + 1e-8).astype(int))

        print("isObs", current_cell_coords)
   

        # The search space is the set of all valid cells (non-obstacles) in the bounding box
        all_f_cells = prev_front_cells + current_front_cells
        search_space = {cell for cell in self._calculate_search_space(all_f_cells) if cell not in obstacle_set}

        _prev_front_cells = {tuple(c) for c in prev_front_cells}
        _current_front_cells = {tuple(c) for c in current_front_cells}

        # For each non-obstacle starting front cell, try to find a path to any of the target front cells
        for start_cell in _prev_front_cells:
            # If a path is found from this start cell, it means the obstacle is not blocking the way
            if self._dfs_path_exists(start_cell, _current_front_cells, search_space, obstacle_set, loose_dimension):
                return False  # A valid path was found, so no obstacle hit

        # If no path was found from any of the previous front cells, then it's an obstacle hit
        return True
    
    def next(self) -> Dict[str, Any]:
        """
        Advances the ray to the next grid intersection and updates its state.
        """
        min_D_value = np.min(self.D)
        i_star_indices = np.where(self.D == min_D_value)[0]
        
        for i_star in i_star_indices:
            self.k[i_star] += 1
        
        self.l = min_D_value * self.norm_delta_x
    
        for i_star in i_star_indices:
            if abs(self.delta_x[i_star]) > 1e-10:
                self.D[i_star] = self.D_0[i_star] + (self.k[i_star] / abs(self.delta_x[i_star]))
            else:
                self.D[i_star] = float('inf')

        for i_star in i_star_indices:
            self.y[i_star] += self.delta_x_sign[i_star]

        self.t += 1
        self._determine_front_cells()

        return {
            "front_cells": self.front_cells(),
            "last_coordinates": self.coords(),
            "length_traversed": self.length(),
            "reached_goal": self.reached()
        }

    def traverse(self, x_0: np.ndarray, x_f: np.ndarray, obstacles: Optional[List[np.ndarray]] = None, loose_dimension: int = 0) -> Tuple[List[np.ndarray], List[List[np.ndarray]], List[np.ndarray], List[np.ndarray], bool, bool]:
        """
        Complete traversal with corrected front cell tracking.
        Returns: (path_coordinates, front_cells_at_each_step, intersection_coordinates, y_coords_history, obstacle_hit, goal_reached)
        """
        step_info = self.init(x_0, x_f)
        path = [self.x_0.copy()]
        all_front_cells = [self.front_cells()]
        
        if np.all(np.abs(self.x_0 - np.round(self.x_0)) < 1e-10):
            intersection_coords = [self.x_0.copy()]
        else:
            all_front_cells = step_info['front_cells']
            intersection_coords = [self.x_0.copy()]
            if 'last_coordinates' in step_info and step_info['last_coordinates']:
                path.extend(step_info['last_coordinates'])
                intersection_coords.extend(step_info['last_coordinates'])

        isGoalReached = False
        obstacle_hit = False

        if self.isHitObstacle(self.x_0, all_front_cells[-1], self.x_0, all_front_cells[-1], obstacles, loose_dimension=loose_dimension):
            obstacle_hit = True
            return path, all_front_cells, intersection_coords, self.y_coords_history, obstacle_hit, isGoalReached

        if np.array_equal(self.x_0, x_f):
            isGoalReached = True
            return path, all_front_cells, intersection_coords, self.y_coords_history, obstacle_hit, isGoalReached
        
        while not self.reached():
            step_info = self.next()
            new_coords = step_info["last_coordinates"].copy()
            new_front_cells = step_info["front_cells"]
            
            path.append(new_coords)
            intersection_coords.append(new_coords)
            self.y_coords_history.append(self.y.copy())
            
            if self.isHitObstacle(path[-2], all_front_cells[-1], new_coords, new_front_cells, obstacles, loose_dimension=loose_dimension):
                obstacle_hit = True
                # all_front_cells.append(new_front_cells)
                break
            
            all_front_cells.append(new_front_cells)
        
        if not obstacle_hit:
            if not path or not np.array_equal(path[-1], x_f):
                path.append(x_f.copy())
            isGoalReached = True
            # if self.isHitObstacle(path[-2], all_front_cells[-1], x_f, all_front_cells[-1], obstacles, loose_dimension=loose_dimension):
            #     obstacle_hit = True

        return path, all_front_cells, intersection_coords, self.y_coords_history, obstacle_hit, isGoalReached