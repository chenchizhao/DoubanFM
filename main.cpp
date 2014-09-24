#include <QApplication>
#include "doubanfm.h"

int main( int argc ,char *argv[] )
{
    QApplication app( argc, argv );

    DoubanFM doubanfm;
    doubanfm.show();

    return app.exec();
}
