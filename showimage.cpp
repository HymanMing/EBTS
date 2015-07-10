#include <QtGui>
#include <QMouseEvent>
//#include <QDebug>
//#include <QString>
//#include <QWheelEvent>
//#include <QKeyEvent>
//#include <QResizeEvent>
#include "showimage.h"

ShowImage::ShowImage(QWidget *parent)
    :QWidget(parent),wscale(1.0),hscale(1.0)
{
    init_path(QDir("C:/"),0);
//    setBackgroundRole(QPalette::Window);
//    setBackgroundRole(QPalette::WindowText);//��ɫ����
//    setBackgroundRole(QPalette::Foreground);//��ɫ����
//    setBackgroundRole(QPalette::Base);//��ɫ����
    setBackgroundRole(QPalette::Background);//ϵͳ����

    setAutoFillBackground(true);//�Զ���䱳��
    FirstTimeShowFlag = true;
}

QSize ShowImage::minimumSizeHint() const
{
    return QSize(100, 100);
}

QSize ShowImage::sizeHint() const
{
    return QSize(640, 480);
}

void ShowImage::init_path(QDir newdir, QString file)
{
    filepath = QDir(newdir);
    //filepath = "D:\testsrc\day0812\build-AnImageBrowser-����-Debug";
    QStringList filters;
    filters<<"*.jpg";
    filepath.setNameFilters(filters);//�ļ����͹���

    //���ù�����
    filepath.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
    filepath.setSorting(QDir::Size | QDir::Reversed);//��������˳��:����С����������
    list = filepath.entryList();//����һ���б�Ŀ¼�е������ļ���Ŀ¼������

    if (!list.empty())
    {
        emit get2beg(false);
        emit get2end(false);
    }
    else//�б�Ϊ�գ���ʼ��ʾ
    {
        emit get2beg(true);
        emit get2end(true);
    }
    //file = "D:\testsrc\day0812\build-AnImageBrowser-����-Debug\0a4cd7.jpg";
    pixmap = QPixmap(file);
    QStringList::const_iterator itmp = list.begin();
    for (; itmp != list.end(); ++itmp)
        if (filepath.absoluteFilePath((*itmp)) == file)
        {//absoluteFilePath����,����Ŀ¼�е��ļ��ľ���·����
            iterator = itmp;
            break;
        }
    FirstTimeShowFlag = true;
    update();//�ػ�ͼ��
}

void ShowImage::show_next()
{
    ++iterator;
    if(iterator+1 > list.end())
        iterator = list.begin();
    pixmap = QPixmap(filepath.absoluteFilePath((*iterator)));
    wscale = 1.0;
    hscale = 1.0;
    emit turn2default(100);
    FirstTimeShowFlag = true;
    update();//�ػ�ͼ��
}

void ShowImage::show_prev()
{
    if(iterator == list.begin())
        iterator = list.end();
    --iterator;
    pixmap = QPixmap(filepath.absoluteFilePath((*iterator)));
    wscale = 1.0;
    hscale = 1.0;
    emit turn2default(100);
    FirstTimeShowFlag = true;
    update();//�ػ�ͼ��
}

//ͼƬ����
void ShowImage::arise_scale(int rate)
{
    wscale = static_cast<double>(rate)/100.0;
    hscale = wscale;
    update();//�ػ�ͼ��
}


//����QPainter��ͼ
void ShowImage::paintEvent(QPaintEvent * /*event*/)
{
    double pixwidth = static_cast<double>(pixmap.width());
    double pixheight = static_cast<double>(pixmap.height());
    double showwidth = static_cast<double>(width());
    double showheight = static_cast<double>(height());

    double Wscalerate = pixwidth / showwidth;
    double Hscalerate = pixheight / showheight;
    double compare = (Wscalerate > Hscalerate ? Wscalerate : Hscalerate);

    //����ƽ�����QRect ( int x, int y, int width, int height )
    QRect rect(showwidth/2.0 - pixwidth/compare/2.0,
               showheight/2.0 - pixheight/compare/2.0,
               pixwidth/compare,
               pixheight/compare);
    QRect midrect(
          (showwidth/2.0-pixwidth/2.0),
          (showheight/2.0-pixheight/2.0),
          pixwidth,
          pixheight);
    QPainter painter(this);

    painter.save();

    if(true == FirstTimeShowFlag)
    {//������ʾ������ϵͳԭ����ͼƬ���ĵ�
        painter.translate(showwidth/2.0, (showheight/2.0));
        //ת������ϵͳ��ͨ��������ƫ�ƣ���������ƫ������ӵ�
        painter.scale(wscale, hscale);
        painter.translate(-(showwidth/2), -(showheight/2.0));
    }
    else
    {//���ץȡ�ƶ�������ϵͳԭ�������λ��
        painter.translate(x,y);
        painter.scale(wscale, hscale);
        painter.translate(-x,-y);
    }

//    //��
//    QRectF target(10.0, 20.0, 80.0, 60.0);
//    QRectF source(0.0, 0.0, 70.0, 40.0);
//    QPixmap pixmap(":myPixmap.png");
//    QPainter(this);
//    painter.drawPixmap(target, image, source);

    if (compare < 1.0)
        painter.drawPixmap(midrect, pixmap);
    else
        painter.drawPixmap(rect, pixmap);
    painter.restore();
    //�ָ���ǰ�Ļ���״̬����ջ�е���һ������״̬��
}

void ShowImage::mouseMoveEvent(QMouseEvent *event)
{
    x = event->x();
    y = event->y();
    FirstTimeShowFlag = false;
    update();//�ػ�ͼ��
}

//void ShowImage::wheelEvent(QWheelEvent *event)
//{
//    QString str;
//    switch(event->orientation())//���ع��ַ���:ˮƽ��ֱ
//    {
//    case Qt::Horizontal:
//        str = "Horizontal Whell Move";
//        break;
//    case Qt::Vertical:
//        str = "Vertical Whell Move";
//        break;
//    default:
//        break;
//    }
//    str += "\n";
//    str += "    ";
//    if(event->delta()>0)//���ع�������
//        str += "go ahead";
//    else
//        str += "go back";
//    qDebug()<<str;
//}
