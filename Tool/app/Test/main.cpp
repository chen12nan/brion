
#include<QApplication>
#include <QTableView>
#include <tablemodel.h>
#include "DisplayTableForm.h"
#include <ccontactdb.h>
#include <weatherrequest.h>
#include <clock.h>
#include <datetime.h>
#include <QWebView>
#include <QtWebKitWidgets>
#include <weatherwidget.h>

#include <stringutil.h>
#include <networkutil.h>
#include <utility.h>
#include <utildb.h>
#include <datetimeutil.h>
#include <indexview.h>
#include <editdatewidget.h>

int main(int argc, char* argv[])
{
    QApplication app(argc,argv);

    return app.exec();
}
