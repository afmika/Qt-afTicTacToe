#include "mainwindow.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <QDebug>
#include <QGraphicsTextItem>

#include "TicTacToe.h"

MainWindow::MainWindow(QWidget* parent) : QWidget(parent)
{
    game_infos = new QLabel("Click \"New Game\" to start");
    QFont font;
    font.setFamily("consolas");
    font.setPixelSize(18);
    game_infos->setFont(font);
    
    QVBoxLayout* layout = new QVBoxLayout(this);
    QPushButton* new_game_btn = new QPushButton("New Game");
    view = new afCanvasView;
    QGraphicsScene* scene = new QGraphicsScene(view);
    view->setScene(scene);
    view->setFixedSize(280, 265);
    
    // events
    // custom event defined in afCanvasView
    connect(view, SIGNAL(customClickSignal(int, int)), SLOT(onViewClick(int, int)));
    connect(new_game_btn, SIGNAL(clicked()), SLOT(onNewGameClick()));
    
    // view
    QLabel* title = new QLabel("TicTacToe - afmika");
    title->setFont(font);
    
    layout->addWidget(title);
    layout->addWidget(view);
    layout->addWidget(new_game_btn);
    layout->addWidget(game_infos);
    setLayout(layout);
    
    // init
    resize(300, 360);
    setFixedSize(size());
    setWindowTitle(tr("afTicTacToe - afmika"));
    
    initGame();
}

void MainWindow::initGame() {
    board = TicTacToe::newGame();
    size_t wdim = static_cast<size_t>(view->width() - 10) / 3;
    size_t hdim = static_cast<size_t>(view->height() - 10) / 3;
    
    QGraphicsScene* scene = view->scene();
    scene->clear();
    drawLines(scene, wdim, hdim);
    game_infos->setText("Game started");
}

void MainWindow::drawLines(QGraphicsScene* scene, size_t wdim, size_t hdim) {
    int xd = static_cast<int>(wdim);
    int yd = static_cast<int>(hdim);
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            QRect rect(i * xd, j * yd, xd, yd);
            scene->addRect(rect);
        }
    }
}

void MainWindow::drawPlayers(QGraphicsScene* scene, size_t wdim, size_t hdim) {
    for (size_t y = 0; y < 3; y++) {
        for (size_t x = 0; x < 3; x++) {
            if ( board[y][x] != 0 ) {
                char player = TicTacToe::player_map[board[y][x]];
                QString value(player);
                QGraphicsTextItem* text = new QGraphicsTextItem;
                text->setPlainText(value);
                QFont font;
                font.setFamily("consolas");
                font.setPixelSize(64);
                text->setFont(font);
                text->setPos(wdim / 4 + x * wdim, hdim / 24 + y * hdim);
                scene->addItem(text);                
            }
        }
    }
}

void MainWindow::onViewClick(int x, int y) {
    QGraphicsScene* scene = view->scene();
    scene->clear();
    size_t wdim = static_cast<size_t>(view->width() - 10) / 3;
    size_t hdim = static_cast<size_t>(view->height() - 10) / 3;
    
    size_t bx = static_cast<size_t>(x) / wdim;
    size_t by = static_cast<size_t>(y) / hdim;
    if ( board[by][bx] == 0 && TicTacToe::gameEnd(board) == TicTacToe::_GAME_NOT_ENDED ) {
        board[by][bx] = -1;
        pair<int, int> pos = TicTacToe::play(board);
        board[pos.first][pos.second] = 1;  
        
        int game_state = TicTacToe::gameEnd(board);
        if ( game_state != TicTacToe::_GAME_NOT_ENDED ) {
            QString text;
            if ( game_state == 0 ) {
                text = "TIE";
            } else {
                char winner = TicTacToe::player_map[game_state];
                text = QString("%1 WON!").arg(winner);
            }
            game_infos->setText(text);
        }
    }
    
    drawLines(scene, wdim, hdim);
    drawPlayers(scene, wdim, hdim);
    
    qDebug() << x << y;
}

void MainWindow::onNewGameClick() {
    qDebug() << "new game";
    initGame();    
}
