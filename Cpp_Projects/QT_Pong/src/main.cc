/*
 * File:   main.cc
 * Author: patty
 *
 * Created on February 20, 2010, 2:32 AM
 */

#include <QtGui/QApplication>
#include "QtPong.h"

int main(int argc, char *argv[]) {
    // initialize resources, if needed
    // Q_INIT_RESOURCE(resfile);

    QApplication app(argc, argv);

    QtPong game(app);
    game.run();
    
    return app.exec();
}
