#ifndef CIRGRAPHICSVIEW_H
#define CIRGRAPHICSVIEW_H

#include <QObject>
#include <QGraphicsView>

class CirGraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit CirGraphicsView(QWidget *parent = nullptr);

signals:

};

#endif // CIRGRAPHICSVIEW_H
