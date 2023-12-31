from collections import namedtuple
from numpy import sin, cos, arange, pi, deg2rad


class Point:
    def __init__(self, x, y):
        self.x = x
        self.y = y


class Line:
    def __init__(self, head, tail):
        self.head = head
        self.tail = tail


class Drawing:
    def __init__(self, position):
        self.tail = [Line(Point(80 + position.x, -21 + position.y), Point(117 + position.x, -52 + position.y)),
                     Line(Point(117 + position.x, -52 + position.y), Point(177 + position.x, -52 + position.y)),
                     Line(Point(177 + position.x, -52 + position.y), Point(127 + position.x, -12 + position.y)),
                     Line(Point(127 + position.x, -12 + position.y), Point(167 + position.x, 18 + position.y)),
                     Line(Point(167 + position.x, 18 + position.y), Point(87 + position.x, 18 + position.y)),
                     ]
        self.upper_fin = [Line(Point(-50 + position.x, 30 + position.y), Point(-30 + position.x, 55 + position.y)),
                          Line(Point(-30 + position.x, 55 + position.y), Point(70 + position.x, 55 + position.y)),
                          Line(Point(70 + position.x, 55 + position.y), Point(50 + position.x, 30 + position.y)),
                          ]
        self.lower_fin = [Line(Point(-35 + position.x, -33 + position.y), Point(-25 + position.x, -57 + position.y)),
                          Line(Point(-25 + position.x, -57 + position.y), Point(35 + position.x, -57 + position.y)),
                          Line(Point(35 + position.x, -57 + position.y), Point(25 + position.x, -34 + position.y)),
                          ]
        self.mouth = Line(Point(-93 + position.x, 6 + position.y), Point(-75 + position.x, 6 + position.y))
        self.eye = [Point(round(3 * cos(t)) + position.x - 85, round(3 * sin(t)) + position.y - 12) for t in
                    arange(0, 2 * pi, 0.01)]
        self.face = [Point(round(20 * cos(t)) + position.x - 79, round(20 * sin(t)) + position.y) for t in
                     arange(pi / 2, -pi / 2, -0.01)]
        self.body = [Point(round(100 * cos(t)) + position.x, round(35 * sin(t)) + position.y) for t in
                     arange(0, 2 * pi, 0.01)]
        self.centre = self.get_centre()

    def draw(self, scene):
        # Drawing body
        for i in range(len(self.body) - 1):
            scene.addLine(self.body[i].x, self.body[i].y, self.body[i + 1].x, self.body[i + 1].y)
        scene.addLine(self.body[-1].x, self.body[-1].y, self.body[0].x, self.body[0].y)

        # Drawing tail
        for line in self.tail:
            scene.addLine(line.head.x, line.head.y, line.tail.x, line.tail.y)

        # Drawing mouth
        scene.addLine(self.mouth.head.x, self.mouth.head.y, self.mouth.tail.x, self.mouth.tail.y)

        # Drawing eye
        for i in range(len(self.eye) - 1):
            scene.addLine(self.eye[i].x, self.eye[i].y, self.eye[i + 1].x, self.eye[i + 1].y)
        scene.addLine(self.eye[-1].x, self.eye[-1].y, self.eye[0].x, self.eye[0].y)

        # Drawing face
        for i in range(len(self.face) - 1):
            scene.addLine(self.face[i].x, self.face[i].y, self.face[i + 1].x, self.face[i + 1].y)

        # Drawing upper fin
        for line in self.upper_fin:
            scene.addLine(line.head.x, line.head.y, line.tail.x, line.tail.y)

        # Drawing lower fin
        for line in self.lower_fin:
            scene.addLine(line.head.x, line.head.y, line.tail.x, line.tail.y)

    def get_centre(self):
        x_list = [p.x for p in self.body] + \
                 [line.head.x for line in self.tail] + [line.tail.x for line in self.tail] + \
                 [line.head.x for line in self.upper_fin] + [line.tail.x for line in self.upper_fin] + \
                 [line.head.x for line in self.lower_fin] + [line.tail.x for line in self.lower_fin]
        y_list = [p.y for p in self.body] + \
                 [line.head.y for line in self.tail] + [line.tail.y for line in self.tail] + \
                 [line.head.y for line in self.upper_fin] + [line.tail.y for line in self.upper_fin] + \
                 [line.head.y for line in self.lower_fin] + [line.tail.y for line in self.lower_fin]

        return Point(int((max(x_list) + min(x_list)) / 2), int(((max(y_list) + min(y_list)) / 2)))

    def moving(self, dx, dy):
        self.centre.x += dx
        self.centre.y += dy

        def move_points(part):
            nonlocal dx, dy
            for i in range(len(part)):
                part[i].x += dx
                part[i].y += dy

        def move_lines(part):
            nonlocal dx, dy
            for i in range(len(part)):
                part[i].head.x += dx
                part[i].head.y += dy
                part[i].tail.x += dx
                part[i].tail.y += dy

        move_points(self.body)
        move_points(self.eye)
        move_points(self.face)

        move_lines([self.mouth])
        move_lines(self.tail)
        move_lines(self.upper_fin)
        move_lines(self.lower_fin)

    def scale(self, kx, ky, scale_centre):
        self.centre.x = self.centre.x * kx + scale_centre.x * (1 - kx)
        self.centre.y = self.centre.y * ky + scale_centre.y * (1 - ky)

        def scale_points(part):
            nonlocal kx, ky, scale_centre
            for i in range(len(part)):
                part[i].x = part[i].x * kx + scale_centre.x * (1 - kx)
                part[i].y = part[i].y * ky + scale_centre.y * (1 - ky)

        def scale_lines(part):
            nonlocal kx, ky, scale_centre
            for i in range(len(part)):
                part[i].head.x = part[i].head.x * kx + scale_centre.x * (1 - kx)
                part[i].head.y = part[i].head.y * ky + scale_centre.y * (1 - ky)
                part[i].tail.x = part[i].tail.x * kx + scale_centre.x * (1 - kx)
                part[i].tail.y = part[i].tail.y * ky + scale_centre.y * (1 - ky)

        scale_points(self.body)
        scale_points(self.eye)
        scale_points(self.face)

        scale_lines([self.mouth])
        scale_lines(self.tail)
        scale_lines(self.upper_fin)
        scale_lines(self.lower_fin)

    def rotate(self, deg, rotate_centre):
        phi = deg2rad(deg)

        self.centre.x = (rotate_centre.x + (self.centre.x - rotate_centre.x) * cos(phi) +
                         (self.centre.y - rotate_centre.y) * sin(phi))
        self.centre.y = (rotate_centre.y - (self.centre.x - rotate_centre.x) * sin(phi) +
                         (self.centre.y - rotate_centre.y) * cos(phi))

        def rotate_points(part):
            nonlocal phi, rotate_centre
            for i in range(len(part)):
                new_x = (rotate_centre.x + (part[i].x - rotate_centre.x) * cos(phi) +
                         (part[i].y - rotate_centre.y) * sin(phi))
                new_y = (rotate_centre.y - (part[i].x - rotate_centre.x) * sin(phi) + (part[i].y - rotate_centre.y)
                         * cos(phi))
                part[i].x = new_x
                part[i].y = new_y

        def rotate_lines(part):
            nonlocal phi, rotate_centre
            for i in range(len(part)):
                new_x_head = (rotate_centre.x + (part[i].head.x - rotate_centre.x) * cos(phi) +
                              (part[i].head.y - rotate_centre.y) * sin(phi))
                new_y_head = (rotate_centre.y - (part[i].head.x - rotate_centre.x) * sin(phi) +
                              (part[i].head.y - rotate_centre.y) * cos(phi))
                new_x_tail = (rotate_centre.x + (part[i].tail.x - rotate_centre.x) * cos(phi) +
                              (part[i].tail.y - rotate_centre.y) * sin(phi))
                new_y_tail = (rotate_centre.y - (part[i].tail.x - rotate_centre.x) * sin(phi) +
                              (part[i].tail.y - rotate_centre.y) * cos(phi))
                part[i].head.x = new_x_head
                part[i].head.y = new_y_head
                part[i].tail.x = new_x_tail
                part[i].tail.y = new_y_tail

        rotate_points(self.body)
        rotate_points(self.eye)
        rotate_points(self.face)

        rotate_lines([self.mouth])
        rotate_lines(self.tail)
        rotate_lines(self.upper_fin)
        rotate_lines(self.lower_fin)
