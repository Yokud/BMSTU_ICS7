from UI import *

app = QtWidgets.QApplication([])
MainWindow = QtWidgets.QMainWindow()
ui = UI()
ui.setupUi(MainWindow)
MainWindow.show()
app.exec()
