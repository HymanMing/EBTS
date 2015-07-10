#ifndef SHOWIMAGE_H
#define SHOWIMAGE_H

#include <QPixmap>
#include <QWidget>
#include <QStringList>
#include <QDir>

class ShowImage : public QWidget
{
    Q_OBJECT

public:
    ShowImage(QWidget *parent = 0);

    QSize minimumSizeHint() const;
    QSize sizeHint() const;

signals:
    void get2end(bool);
    void get2beg(bool);
    void turn2default(int);//���ű���

public slots:
    void init_path(QDir,QString);
    void show_next(void);//�鿴��һ��
    void show_prev(void);//�鿴��һ��
    void arise_scale(int);//ͼƬ����

protected:
    void paintEvent(QPaintEvent *event);//����QPainter��ͼ
//    void wheelEvent(QWheelEvent *event);//�������ƶ�
    void mouseMoveEvent(QMouseEvent *);

private:
    QStringList::const_iterator iterator;//����������
    QStringList list;
    QDir filepath;
    QPixmap pixmap;//����ͼ�豸��
    double wscale;
    double hscale;
    volatile int x;
    volatile int y;
    bool FirstTimeShowFlag;
};

#endif // SHOWIMAGE_H
