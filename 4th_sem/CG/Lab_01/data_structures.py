from collections import namedtuple
from math import hypot, prod
from itertools import combinations


Point = namedtuple('Point', ['x', 'y'])
Bisect = namedtuple('Bisect', ['head', 'tail'])


class Triangle:
    def __init__(self, p_1, p_2, p_3):
        self.point_a = p_1
        self.point_b = p_2
        self.point_c = p_3

        self.bisect_ak = None
        self.bisect_bl = None
        self.bisect_cm = None
        self.triangle_centre = None

    @classmethod
    def is_triangle(cls, p_1, p_2, p_3):
        ab = hypot(p_1.x - p_2.x, p_1.y - p_2.y)
        bc = hypot(p_2.x - p_3.x, p_2.y - p_3.y)
        ac = hypot(p_3.x - p_1.x, p_3.y - p_1.y)

        return ab + bc > ac and bc + ac > ab and ab + ac > bc

    def get_lengths(self):
        return (hypot(self.point_a.x - self.point_b.x, self.point_a.y - self.point_b.y),
                hypot(self.point_b.x - self.point_c.x, self.point_b.y - self.point_c.y),
                hypot(self.point_c.x - self.point_a.x, self.point_c.y - self.point_a.y))

    def init_bisects(self):
        ab, bc, ac = self.get_lengths()

        self.bisect_ak = Bisect(self.point_a, Point((self.point_b.x + ab / ac * self.point_c.x) / (1 + ab / ac),
                                                    (self.point_b.y + ab / ac * self.point_c.y) / (1 + ab / ac)))

        self.bisect_bl = Bisect(self.point_b, Point((self.point_a.x + ab / bc * self.point_c.x) / (1 + ab / bc),
                                                    (self.point_a.y + ab / bc * self.point_c.y) / (1 + ab / bc)))

        self.bisect_cm = Bisect(self.point_c, Point((self.point_a.x + ac / bc * self.point_b.x) / (1 + ac / bc),
                                                    (self.point_a.y + ac / bc * self.point_b.y) / (1 + ac / bc)))

        self.triangle_centre = Point((ab * self.point_a.x + bc * self.point_b.x + ac * self.point_c.x) / (ab + bc + ac),
                                     (bc * self.point_a.y + ac * self.point_b.y + ab * self.point_c.y) / (ab + bc + ac))

    def is_point_in_triangle(self, point):
        ab = (self.point_a.x - point.x) * (self.point_b.y - self.point_a.y) - \
            (self.point_b.x - self.point_a.x) * (self.point_a.y - point.y)
        bc = (self.point_b.x - point.x) * (self.point_c.y - self.point_b.y) - \
            (self.point_c.x - self.point_b.x) * (self.point_b.y - point.y)
        ac = (self.point_c.x - point.x) * (self.point_a.y - self.point_c.y) - \
            (self.point_a.x - self.point_c.x) * (self.point_c.y - point.y)

        return ab >= 0 and bc >= 0 and ac >= 0 or ab <= 0 and bc <= 0 and ac <= 0

    def count_of_points_in_triangle(self, points):
        count = 0
        for point in points:
            if point not in (self.point_a, self.point_b, self.point_c):
                count += self.is_point_in_triangle(point)

        return count

    def get_diff(self, points):
        if self.bisect_ak is None or self.bisect_bl is None or self.bisect_cm is None or self.triangle_centre is None:
            self.init_bisects()
        sub_triangles = (Triangle(self.point_a, self.bisect_bl.tail, self.triangle_centre),
                         Triangle(self.point_c, self.bisect_bl.tail, self.triangle_centre),
                         Triangle(self.point_c, self.bisect_ak.tail, self.triangle_centre),
                         Triangle(self.point_b, self.bisect_ak.tail, self.triangle_centre),
                         Triangle(self.point_b, self.bisect_cm.tail, self.triangle_centre),
                         Triangle(self.point_a, self.bisect_cm.tail, self.triangle_centre))

        counts = [sub_triangle.count_of_points_in_triangle(points) for sub_triangle in sub_triangles]

        min_count, max_count = min(counts), max(counts)
        return max_count - min_count

    @classmethod
    def get_solution(cls, points):
        triangles = list()
        for comb in combinations(points, 3):
            if Triangle.is_triangle(comb[0], comb[1], comb[2]):
                triangles.append(Triangle(comb[0], comb[1], comb[2]))

        # Вырожденный случай: все точки расположены на одной прямой
        if not triangles:
            return list()

        min_diff = float('inf')
        res_triangle = None
        for triangle in triangles:
            temp_diff = triangle.get_diff(points)
            if temp_diff < min_diff:
                min_diff = temp_diff
                res_triangle = triangle

        return res_triangle.point_a, res_triangle.point_b, res_triangle.point_c
