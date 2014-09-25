#include <QApplication>
#include <unistd.h>
#include "doubanfm.h"

int main( int argc ,char *argv[] )
{
    QApplication app( argc, argv );
    app.setApplicationName("DoubanFM");

    DoubanFM doubanfm;
    //doubanfm.show();
    //
    close(STDOUT_FILENO);
    close(STDERR_FILENO);

    return app.exec();
}
