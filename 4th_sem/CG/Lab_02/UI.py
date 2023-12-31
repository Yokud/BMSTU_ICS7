from PyQt5.QtWidgets import QMessageBox, QMainWindow
from copy import deepcopy
from UI_prototype import *
from drawing import *


def is_float(str_num):
    if str_num.find('-') == 0 or str_num.find('-') == -1:
        str_num = str_num.replace('-', '', 1)
        str_num = str_num.replace('.', '', 1)
        return str_num.isdigit()
    else:
        return False


def is_int(str_num):
    if str_num.find('-') == 0 or str_num.find('-') == -1:
        str_num = str_num.replace('-', '', 1)
        return str_num.isdigit()
    else:
        return False


class UI(Ui_MainWindow, QMainWindow):
    def __init__(self, MainWindow):
        super().__init__()
        super().setupUi(MainWindow)
        super().retranslateUi(MainWindow)

        self.scene = QtWidgets.QGraphicsScene(MainWindow)
        self.graphicsView.setScene(self.scene)

        self.painting = Drawing(Point(300, 250))
        self.painting.draw(self.scene)
        self.draw_coords.setText("({:5g}; {:5g})".format(self.painting.centre.x, self.painting.centre.y))
        self.states = list()

        self.moveButton.clicked.connect(self.move_painting)
        self.scaleButton.clicked.connect(self.scale_painting)
        self.rotateButton.clicked.connect(self.rotate_painting)
        self.askButton.clicked.connect(self.info)
        self.reestablishButton.clicked.connect(self.reestablish_painting)
        self.returnButton.clicked.connect(self.return_painting)

    def move_painting(self):
        if is_int(self.dx_line.text()) and is_int(self.dy_line.text()):
            dx, dy = int(self.dx_line.text()), int(self.dy_line.text())
            self.states.append(deepcopy(self.painting))
            self.painting.moving(dx, dy)
            self.scene.clear()
            self.painting.draw(self.scene)
            self.draw_coords.setText("({:5g}; {:5g})".format(self.painting.centre.x, self.painting.centre.y))
        else:
            QMessageBox.critical(self, "Ошибка ввода", "Введены некорректные значения для перемещения!")

    def scale_painting(self):
        if is_float(self.centre_x_line.text()) and is_float(self.centre_y_line.text()) and \
                is_float(self.kx_line.text()) and is_float(self.ky_line.text()):
            kx, ky = float(self.kx_line.text()), float(self.ky_line.text())
            center = Point(float(self.centre_x_line.text()), float(self.centre_y_line.text()))
            self.states.append(deepcopy(self.painting))
            self.painting.scale(kx, ky, center)
            self.scene.clear()
            self.painting.draw(self.scene)
            self.draw_coords.setText("({:5g}; {:5g})".format(self.painting.centre.x, self.painting.centre.y))
        else:
            if not self.centre_x_line.text() or self.centre_x_line.text().isspace() \
                    or not self.centre_y_line.text() or self.centre_y_line.text().isspace():
                QMessageBox.critical(self, "Ошибка ввода", "Не введена точка масштабирования!")
            else:
                QMessageBox.critical(self, "Ошибка ввода", "Введены некорректные коэффициенты масштабирования!")

    def rotate_painting(self):
        if is_float(self.centre_x_line.text()) and is_float(self.centre_y_line.text()) and is_float(self.phi_line.text()):
            deg = float(self.phi_line.text())
            center = Point(float(self.centre_x_line.text()), float(self.centre_y_line.text()))
            self.states.append(deepcopy(self.painting))
            self.painting.rotate(deg, center)
            self.scene.clear()
            self.painting.draw(self.scene)
            self.draw_coords.setText("({:5g}; {:5g})".format(self.painting.centre.x, self.painting.centre.y))
        else:
            if not self.centre_x_line.text() or self.centre_x_line.text().isspace() \
                    or not self.centre_y_line.text() or self.centre_y_line.text().isspace():
                QMessageBox.critical(self, "Ошибка ввода", "Не введена точка поворота!")
            else:
                QMessageBox.critical(self, "Ошибка ввода", "Введен некорректный угол поворота!")

    def info(self):
        str_info = "Данная программа позволяет преобразовывать исходное изображение: перемещать, масштабировать и " \
                   "поворачивать. Также есть возможность возвращать предыдущее и исходное состояние рисунка." \
                   "\n\tСистема координат экранная, сами координаты представляют собой пиксели на " \
                   "полотне, где изображён рисунок, т. е. являются целыми числами. Коэффициенты масштабирования " \
                   "принимают любые действительные значения. Угол задаётся в градусах действительным числом."
        QMessageBox.information(self, "Информация о программе", str_info)

    def reestablish_painting(self):
        self.scene.clear()
        self.states.clear()
        self.painting = Drawing(Point(300, 250))
        self.painting.draw(self.scene)
        self.draw_coords.setText("({:5g}; {:5g})".format(self.painting.centre.x, self.painting.centre.y))

    def return_painting(self):
        self.scene.clear()
        self.painting = self.states.pop() if len(self.states) else Drawing(Point(300, 250))
        self.painting.draw(self.scene)
        self.draw_coords.setText("({:5g}; {:5g})".format(self.painting.centre.x, self.painting.centre.y))


if __name__ == "__main__":
    import sys
    app = QtWidgets.QApplication(sys.argv)
    MainWindow = QtWidgets.QMainWindow()
    ui = UI(MainWindow)
    MainWindow.show()
    sys.exit(app.exec_())
