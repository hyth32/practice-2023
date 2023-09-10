#include <QApplication>
#include <QMainWindow>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QFile>
#include <QTextStream>
#include <QStringList>

QT_CHARTS_USE_NAMESPACE

int main(int argc, char* argv[]) {
    QApplication a(argc, argv);

    // Создание серии для данных графика
    QLineSeries* series = new QLineSeries();

    // Чтение данных из файла .dat
    QFile file("graph.dat");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        while (!in.atEnd()) {
            QString line = in.readLine();
            QStringList values = line.split(" ");
            if (values.size() >= 2) {
                bool ok1, ok2;
                double x = values[0].toDouble(&ok1);
                double y = values[1].toDouble(&ok2);
                if (ok1 && ok2) {
                    series->append(x, y);
                }
            }
        }
        file.close();
    }
    else {
        qDebug() << "Error: Unable to open file graph.dat";
        return 1;
    }

    // Создание графика и добавление серии данных
    QChart* chart = new QChart();
    chart->addSeries(series);
    chart->createDefaultAxes();
    chart->setTitle("Graph");

    // Создание виджета для отображения графика
    QChartView* chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    // Создание главного окна и установка виджета с графиком в качестве центрального виджета
    QMainWindow window;
    window.setCentralWidget(chartView);
    window.resize(800, 600);
    window.show();

    return a.exec();
}
