from PyQt5.QtWidgets import QMessageBox, QTableWidgetItem, QMainWindow, QInputDialog
from UI_prototype import *
from draw_funcs import *


class UI(Ui_MainWindow, QMainWindow):
    def __init__(self):
        super().__init__()

        self.Points = list()

    def setupUi(self, MainWindow):
        super().setupUi(MainWindow)
        super().retranslateUi(MainWindow)

        self.referenceButton.clicked.connect(self.reference)
        self.addButton.clicked.connect(self.add_point)
        self.deleteButton.clicked.connect(self.delete_point)
        self.drawButton.clicked.connect(self.draw)
        self.changeButton.clicked.connect(self.change_point)

    def reference(self):
        text = "Программа принимает на вход множество точек на плоскости. В этом множестве есть возможность удалять " \
               "точки и изменять их координаты. Точки задаются в декартовой системе координат.\n\n" \
               "Результатом программы является треугольник " \
               "с вершинами в этих точках, у которого разность максимального и минимального количеств точек, попавших" \
               "в каждый из 6-ти треугольников, образованных пересечением биссектрис, минимальна. Также в результат " \
               "включается его графическая интерпретация."
        QMessageBox.about(self, "Условие лабораторной работы", text)

    def add_point(self):
        coords, okPressed = QInputDialog.getText(self, "Добавление точки", "Введите координаты точки\n(x, y) через "
                                                                           "пробел:")
        if okPressed:
            coords = coords.split()
            if len(coords) == 2 and is_float(coords[0]) and is_float(coords[1]):
                self.Points.append(Point(float(coords[0]), float(coords[1])))
                numRows = self.tableOfPoints.rowCount()
                self.tableOfPoints.insertRow(numRows)
                self.tableOfPoints.setItem(numRows, 0, QTableWidgetItem("{:.6g}".format(self.Points[-1].x)))
                self.tableOfPoints.setItem(numRows, 1, QTableWidgetItem("{:.6g}".format(self.Points[-1].y)))
            else:
                QMessageBox.critical(self, "Ошибка ввода точки", "Координаты введены в неверном формате или сами "
                                                                 "координаты заданы неверно!")

    def delete_point(self):
        if not len(self.Points):
            QMessageBox.warning(self, "Ошибка удаления точки", "Список пуст!")
            return

        number, okPressed = QInputDialog.getInt(self, "Удаление точки", "Введите номер точки", value=1, min=1,
                                                max=len(self.Points))

        if okPressed:
            self.Points.pop(number - 1)
            self.tableOfPoints.removeRow(number - 1)

    def change_point(self):
        if not len(self.Points):
            QMessageBox.warning(self, "Ошибка изменения точки", "Список пуст!")
            return

        number, okPressed = QInputDialog.getInt(self, "Изменение точки", "Введите номер точки", value=1, min=1,
                                                max=len(self.Points))
        if okPressed:
            coords, okPressed = QInputDialog.getText(self, "Изменение точки", "Введите координаты точки\n(x, y) через "
                                                                              "пробел:")
            if okPressed:
                coords = coords.split()
                if len(coords) == 2 and is_float(coords[0]) and is_float(coords[1]):
                    self.Points[number - 1] = Point(float(coords[0]), float(coords[1]))
                    self.tableOfPoints.removeRow(number - 1)
                    self.tableOfPoints.insertRow(number - 1)
                    self.tableOfPoints.setItem(number - 1, 0,
                                               QTableWidgetItem("{:.6g}".format(self.Points[number - 1].x)))
                    self.tableOfPoints.setItem(number - 1, 1,
                                               QTableWidgetItem("{:.6g}".format(self.Points[number - 1].y)))
                else:
                    QMessageBox.critical(self, "Ошибка ввода точки", "Координаты введены в неверном формате или сами "
                                                                     "координаты заданы неверно!")

    def draw(self):
        if len(self.Points) > 2:
            solution = Triangle.get_solution(self.Points)
            if not solution and type(solution) is list:
                QMessageBox.critical(self, "Ошибка поиска решения", "Решение не было найдено, т. к. все точки "
                                                                    "расположены на одной прямой!")
            elif not solution and solution is None:
                QMessageBox.critical(self, "Ошибка поиска решения", "Решение не было найдено, т. к. нет такого треуголь"
                                                                    "ника, который бы соответствовал условиям задачи.")
            else:
                self.textBrowser.setText("Треугольник, построенный на точках:\n- {:d}({:.6g}; {:.6g})\n"
                                         "- {:d}({:.6g}; {:.6g})\n"
                                         "- {:d}({:.6g}; {:.6g})\n"
                                         "Разность макс. и мин. количеств точек, попавших в каждый из "
                                         "6-ти треугольников, образованных пересечением биссектрис: {:d}".format(
                                            self.Points.index(solution[0]) + 1, solution[0].x, solution[0].y,
                                            self.Points.index(solution[1]) + 1, solution[1].x, solution[1].y,
                                            self.Points.index(solution[2]) + 1, solution[2].x, solution[2].y,
                                            Triangle(solution[0], solution[1], solution[2]).get_diff(self.Points)))
                draw_solution(solution, self.Points)
        else:
            QMessageBox.critical(self, "Ошибка поиска решения", "Список точек пуст или их меньше трёх!")


def is_float(str_num):
    if str_num.find('-') == 0 or str_num.find('-') == -1:
        str_num = str_num.replace('-', '', 1)
        str_num = str_num.replace('.', '', 1)
        return str_num.isdigit()
    else:
        return False
