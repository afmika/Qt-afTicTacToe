#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QLabel>
#include "afCanvasView.h"
#include <vector>
using namespace std;

class MainWindow : public QWidget
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget* parent = nullptr);
    
    void initGame();
    void drawLines(QGraphicsScene* scene, size_t wdim, size_t hdim);
    void drawPlayers(QGraphicsScene* scene, size_t wdim, size_t hdim);
public slots:
    void onViewClick(int x, int y);
    void onNewGameClick();
private:
    afCanvasView* view = nullptr;  
    QLabel* game_infos = nullptr;
    vector<vector<int>> board;
};

#endif // MAINWINDOW_H
