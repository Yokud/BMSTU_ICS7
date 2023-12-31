# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'D:\Projects\CG\Lab_01\ui_prototype.ui'
#
# Created by: PyQt5 UI code generator 5.15.2
#
# WARNING: Any manual changes made to this file will be lost when pyuic5 is
# run again.  Do not edit this file unless you know what you are doing.


from PyQt5 import QtCore, QtGui, QtWidgets


class Ui_MainWindow(object):
    def setupUi(self, MainWindow):
        MainWindow.setObjectName("MainWindow")
        MainWindow.resize(415, 310)
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Fixed, QtWidgets.QSizePolicy.Fixed)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(MainWindow.sizePolicy().hasHeightForWidth())
        MainWindow.setSizePolicy(sizePolicy)
        MainWindow.setMinimumSize(QtCore.QSize(415, 310))
        MainWindow.setMaximumSize(QtCore.QSize(415, 310))
        MainWindow.setLayoutDirection(QtCore.Qt.LeftToRight)
        MainWindow.setAutoFillBackground(True)
        MainWindow.setStyleSheet("")
        MainWindow.setAnimated(False)
        self.centralwidget = QtWidgets.QWidget(MainWindow)
        self.centralwidget.setObjectName("centralwidget")
        self.referenceButton = QtWidgets.QPushButton(self.centralwidget)
        self.referenceButton.setGeometry(QtCore.QRect(310, 280, 51, 23))
        self.referenceButton.setStyleSheet("background-color: gray;\n"
"color: white;\n"
"border-style: outset;\n"
"border-width: 1px;\n"
"border-color: black;")
        self.referenceButton.setObjectName("referenceButton")
        self.deleteButton = QtWidgets.QPushButton(self.centralwidget)
        self.deleteButton.setGeometry(QtCore.QRect(260, 70, 141, 23))
        self.deleteButton.setStyleSheet("background-color: red;\n"
"color: white;\n"
"border-style: outset;\n"
"border-width: 1px;\n"
"border-color: black;")
        self.deleteButton.setObjectName("deleteButton")
        self.addButton = QtWidgets.QPushButton(self.centralwidget)
        self.addButton.setGeometry(QtCore.QRect(260, 10, 141, 23))
        font = QtGui.QFont()
        font.setFamily("MS Shell Dlg 2")
        font.setStyleStrategy(QtGui.QFont.PreferDefault)
        self.addButton.setFont(font)
        self.addButton.setStyleSheet("background-color: grey;\n"
"color: white;\n"
"border-style: outset;\n"
"border-width: 1px;\n"
"border-color: black;")
        self.addButton.setAutoDefault(False)
        self.addButton.setDefault(False)
        self.addButton.setFlat(False)
        self.addButton.setObjectName("addButton")
        self.textBrowser = QtWidgets.QTextBrowser(self.centralwidget)
        self.textBrowser.setGeometry(QtCore.QRect(260, 160, 141, 111))
        font = QtGui.QFont()
        font.setBold(False)
        font.setItalic(False)
        font.setUnderline(False)
        font.setWeight(50)
        font.setStrikeOut(False)
        font.setKerning(True)
        self.textBrowser.setFont(font)
        self.textBrowser.setContextMenuPolicy(QtCore.Qt.DefaultContextMenu)
        self.textBrowser.setStyleSheet("border-style: outset;\n"
"border-width: 1px;\n"
"border-color: black;")
        self.textBrowser.setObjectName("textBrowser")
        self.changeButton = QtWidgets.QPushButton(self.centralwidget)
        self.changeButton.setGeometry(QtCore.QRect(260, 40, 141, 23))
        font = QtGui.QFont()
        font.setPointSize(7)
        self.changeButton.setFont(font)
        self.changeButton.setStyleSheet("background-color: grey;\n"
"color: white;\n"
"border-style: outset;\n"
"border-width: 1px;\n"
"border-color: black;")
        self.changeButton.setObjectName("changeButton")
        self.label = QtWidgets.QLabel(self.centralwidget)
        self.label.setGeometry(QtCore.QRect(260, 140, 141, 20))
        self.label.setStyleSheet("border-style: outset;\n"
"border-width: 1px;\n"
"border-color: black;\n"
"background-color: grey;")
        self.label.setObjectName("label")
        self.tableOfPoints = QtWidgets.QTableWidget(self.centralwidget)
        self.tableOfPoints.setGeometry(QtCore.QRect(10, 10, 241, 291))
        self.tableOfPoints.setStyleSheet("border-style: outset;\n"
"border-width: 1px;\n"
"border-color: black;")
        self.tableOfPoints.setHorizontalScrollBarPolicy(QtCore.Qt.ScrollBarAlwaysOff)
        self.tableOfPoints.setObjectName("tableOfPoints")
        self.tableOfPoints.setColumnCount(2)
        self.tableOfPoints.setRowCount(0)
        item = QtWidgets.QTableWidgetItem()
        self.tableOfPoints.setHorizontalHeaderItem(0, item)
        item = QtWidgets.QTableWidgetItem()
        self.tableOfPoints.setHorizontalHeaderItem(1, item)
        self.drawButton = QtWidgets.QPushButton(self.centralwidget)
        self.drawButton.setGeometry(QtCore.QRect(280, 100, 101, 31))
        self.drawButton.setStyleSheet("background-color: blue;\n"
"color: white;\n"
"border-style: outset;\n"
"border-width: 2px;\n"
"border-color: black;")
        self.drawButton.setObjectName("drawButton")
        MainWindow.setCentralWidget(self.centralwidget)
        self.actionkkkk = QtWidgets.QAction(MainWindow)
        self.actionkkkk.setObjectName("actionkkkk")

        self.retranslateUi(MainWindow)
        QtCore.QMetaObject.connectSlotsByName(MainWindow)

    def retranslateUi(self, MainWindow):
        _translate = QtCore.QCoreApplication.translate
        MainWindow.setWindowTitle(_translate("MainWindow", "Поиск треугольника"))
        self.referenceButton.setText(_translate("MainWindow", "Справка"))
        self.deleteButton.setText(_translate("MainWindow", "Удалить точку по номеру"))
        self.addButton.setText(_translate("MainWindow", "Добавить точку"))
        self.changeButton.setText(_translate("MainWindow", "Изменить координаты точки"))
        self.label.setText(_translate("MainWindow", "Результат"))
        item = self.tableOfPoints.horizontalHeaderItem(0)
        item.setText(_translate("MainWindow", "Координата x"))
        item = self.tableOfPoints.horizontalHeaderItem(1)
        item.setText(_translate("MainWindow", "Координата y"))
        self.drawButton.setText(_translate("MainWindow", "Рисовать"))
        self.actionkkkk.setText(_translate("MainWindow", "kkkk"))


if __name__ == "__main__":
    import sys
    app = QtWidgets.QApplication(sys.argv)
    MainWindow = QtWidgets.QMainWindow()
    ui = Ui_MainWindow()
    ui.setupUi(MainWindow)
    MainWindow.show()
    sys.exit(app.exec_())
