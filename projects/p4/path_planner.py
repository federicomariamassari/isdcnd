import math


class PathPlanner:
    """Construct a PathPlanner Object"""

    def __init__(self, grid, start=None, goal=None):

        self.grid = grid
        self.start = start
        self.goal = goal
        self.closed_set = self.create_closed_set() if goal is not None and start is not None else None
        self.open_set = self.create_open_set() if goal is not None and start is not None else None
        self.came_from = self.create_came_from() if goal is not None and start is not None else None
        self.g_score = self.create_g_score() if goal is not None and start is not None else None
        self.f_score = self.create_f_score() if goal is not None and start is not None else None
        self.path = self.run_search() if self.grid and self.start is not None and self.goal is not None else None

    def reconstruct_path(self, current):
        """ Reconstructs path after search"""
        
        total_path = [current]

        while current in self.came_from.keys():
            current = self.came_from[current]
            total_path.append(current)
        
        return total_path

    def _reset(self):
        """Private method used to reset the closedSet, openSet, cameFrom, gScore, fScore, and path attributes"""

        self.closed_set = None
        self.open_set = None
        self.came_from = None
        self.g_score = None
        self.f_score = None
        self.path = self.run_search() if self.grid and self.start and self.goal else None

    def run_search(self):

        if self.grid is None:
            raise ValueError('Must create map before running search. Run: PathPlanner.set_map(start_node)')

        if self.goal is None:
            raise ValueError('Must create goal node before running search. Run: PathPlanner.set_goal(start_node)')

        if self.start is None:
            raise ValueError('Must create start node before running search. Run: PathPlanner.set_start(start_node)')

        self.closed_set = self.closed_set if self.closed_set is not None else self.create_closed_set()
        self.open_set = self.open_set if self.open_set is not None else self.create_open_set()
        self.came_from = self.came_from if self.came_from is not None else self.create_came_from()
        self.g_score = self.g_score if self.g_score is not None else self.create_g_score()
        self.f_score = self.f_score if self.f_score is not None else self.create_f_score()

        while not self.is_open_empty():
            current = self.get_current_node()

            if current == self.goal:
                self.path = [x for x in reversed(self.reconstruct_path(current))]
                return self.path

            else:
                self.open_set.remove(current)
                self.closed_set.add(current)

            for neighbor in self.get_neighbors(current):
                if neighbor in self.closed_set:
                    # Ignore the neighbor already evaluated
                    continue

                if neighbor not in self.open_set:
                    # Discover a new node
                    self.open_set.add(neighbor)

                # The distance from start to a neighbor
                if self.get_tentative_g_score(current, neighbor) >= self.get_g_score(neighbor):
                    # This is not a better path
                    continue

                # This path is the best until now. Record it!
                self.record_best_path_to(current, neighbor)

        print("No Path Found")
        self.path = None

        return False

    def create_closed_set(self):
        """ Creates and returns a data structure suitable to hold the set of nodes already evaluated"""
        return set()

    def create_open_set(self):
        """ Creates and returns a data structure suitable to hold the set of currently discovered nodes
        that are not evaluated yet. Initially, only the start node is known."""
        if self.start is not None:
            return {self.start}

        raise ValueError('Must create start node before creating an open set. Run: PathPlanner.set_start(start_node)')

    def create_came_from(self):
        """Creates and returns a data structure that shows which node can most efficiently be reached from another,
        for each node."""
        return {}

    def create_g_score(self):
        """Creates and returns a data structure that holds the cost of getting from the start node to that node,
        for each node. The cost of going from start to start is zero."""
        return {node: math.inf if node != self.start else 0. for node in self.grid.intersections.keys()}

    def create_f_score(self):
        """Creates and returns a data structure that holds the total cost of getting from the start node to the goal
        by passing by that node, for each node. That value is partly known, partly heuristic.
        For the first node, that value is completely heuristic."""
        return {node: math.inf if node != self.start else self.heuristic_cost_estimate(self.start)
                for node in self.grid.intersections.keys()}

    def set_map(self, grid):
        """Method used to set map attribute """
        self._reset()
        self.start = None
        self.goal = None
        self.grid = grid

    def set_start(self, start):
        """Method used to set start attribute """
        self._reset()
        self.start = start
        self.goal = None
        self.closed_set = None
        self.open_set = None
        self.came_from = None
        self.g_score = None
        self.path = None

    def set_goal(self, goal):
        """Method used to set goal attribute """
        self._reset()
        self.goal = goal

    def is_open_empty(self):
        """returns True if the open set is empty. False otherwise. """
        return len(self.open_set) == 0

    def get_current_node(self):
        """ Returns the node in the open set with the lowest value of f(node)."""
        # For a very interesting alternative implementation:
        # https://github.com/LukasLeonardKoening/Simple-Route-Planner/blob/master/planer.py#L144
        return min(self.open_set, key=lambda node: self.calculate_f_score(node))

    def get_neighbors(self, node):
        """Returns the neighbors of a node"""
        return self.grid.roads[node]

    def get_g_score(self, node):
        """Returns the g Score of a node"""
        return self.g_score[node]

    def distance(self, node_1, node_2):
        """ Computes the Euclidean L2 Distance"""
        x1, x2 = self.grid.intersections[node_1][0], self.grid.intersections[node_2][0]
        y1, y2 = self.grid.intersections[node_1][1], self.grid.intersections[node_2][1]

        # https://en.wikipedia.org/wiki/Euclidean_distance#Two_dimensions
        return math.sqrt(math.pow(x1 - x2, 2) + math.pow(y1 - y2, 2))

    def get_tentative_g_score(self, current, neighbor):
        """Returns the tentative g Score of a node"""
        return self.get_g_score(current) + self.distance(current, neighbor)

    def heuristic_cost_estimate(self, node):
        """ Returns the heuristic cost estimate of a node """
        return self.distance(node, self.goal)

    def calculate_f_score(self, node):
        """Calculate the f score of a node. """
        return self.get_g_score(node) + self.heuristic_cost_estimate(node)

    def record_best_path_to(self, current, neighbor):
        """Record the best path to a node """
        self.came_from[neighbor] = current
        self.g_score[neighbor] = self.get_tentative_g_score(current, neighbor)
        self.f_score[neighbor] = self.calculate_f_score(neighbor)
