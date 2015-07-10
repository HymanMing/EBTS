#include <QtGui>
//#include <QDebug>
//#include <QWheelEvent>
#include "widget.h"
#include "showimage.h"

Widget::Widget()
{
    prevButton = new QPushButton(tr("&Previous"));
    nextButton = new QPushButton(tr("&Next"));
    indexButton = new QPushButton(tr("&Choose Path"));//ͼƬ·��ѡ��ť
    checkBox = new QCheckBox(tr("�õ�Ƭ����"));
    fileDialog = new QFileDialog(this,tr("Select the image"),tr("E:/images"),
                                 tr("Images (*.jpg *.png *.bmp *.gif)"));
    slider = new QSlider(Qt::Horizontal,this);//���Ż�����
    label = new QLabel;
    showImage = new ShowImage;
    connect(showImage, SIGNAL(get2beg(bool)),
            prevButton, SLOT(setDisabled(bool)));
    connect(showImage, SIGNAL(get2end(bool)),
            nextButton, SLOT(setDisabled(bool)));
    connect(showImage, SIGNAL(get2beg(bool)),
            checkBox, SLOT(setDisabled(bool)));
    connect(showImage, SIGNAL(turn2default(int)),//���ű���
            slider, SLOT(setValue(int)));

    connect(slider,SIGNAL(valueChanged(int)),
            this,SLOT(changelabel(int)));
    connect(slider,SIGNAL(valueChanged(int)),
            this,SLOT(scalethepix(int)));
    connect(indexButton,SIGNAL(clicked()),
            fileDialog,SLOT(show()));
    connect(fileDialog,SIGNAL(fileSelected(QString)),
            this,SLOT(dirChanged(QString)));
    connect(prevButton,SIGNAL(clicked()),
            this,SLOT(turn2prev()));
    connect(nextButton,SIGNAL(clicked()),
            this,SLOT(turn2next()));
    connect(checkBox,SIGNAL(toggled(bool)),
            this,SLOT(ChangeAutoPlayFlag(bool)));

    //set layout
    QGridLayout *windowLayout = new QGridLayout;
    QHBoxLayout *labelLayout = new QHBoxLayout;

    labelLayout->addWidget(slider);
    labelLayout->addWidget(label);//label��ʾ�ٷ�֮��
    label->setBuddy(slider);

    //����������չ����
    windowLayout->setColumnStretch(0,1);
    windowLayout->setColumnStretch(1,2);
    windowLayout->setColumnStretch(2,2);
    windowLayout->setColumnStretch(3,2);
    windowLayout->setColumnStretch(4,2);

    //windowLayout->addWidget();
    windowLayout->addWidget(showImage, 0, 0, 1, 9);//������0��0��λ��
    windowLayout->setRowMinimumHeight(1,6);//�ڵ�1������С�о࣬��λΪ����
    windowLayout->addWidget(indexButton, 2, 0, Qt::AlignLeft);
    windowLayout->addWidget(prevButton,2,2,Qt::AlignRight);//������2��1��λ�ã��Ҷ���
    windowLayout->addWidget(nextButton, 2, 3, Qt::AlignLeft);
    windowLayout->addLayout(labelLayout, 2, 4, Qt::AlignRight);
    windowLayout->addWidget(checkBox, 2, 1, Qt::AlignLeft);
//    label1 = new QLabel;
//    label1->setText(tr("Read"));
//    windowLayout->addWidget(label1, 2, 5, Qt::AlignLeft);

    setLayout(windowLayout);

    fileDialog->resize(450,300);//���öԻ����С

    //set the Tab order
    setTabOrder(nextButton,prevButton);
    nextButton->setDefault(true);

    prevButton->setShortcut(QKeySequence(Qt::Key_Left));//���ÿ�ݼ�
    nextButton->setShortcut(QKeySequence(Qt::Key_Right));

    slider->setRange(0,500);
    slider->setValue(100);
    prevButton->setDisabled(true);
    nextButton->setDisabled(true);
    checkBox->setDisabled(true);

    //set window name
    setWindowTitle(tr("ͼƬ�����"));//��ִ�г������
    setWindowIcon(QIcon(":/icons/qt-logo.png"));//��ִ�г���ͼ��

    AutoPlayFlag = false;
    QTimer *timer = new QTimer(this);//�½���ʱ��
    connect(timer,SIGNAL(timeout()),this,SLOT(AutoPlay()));
    //������ʱ�������źź���Ӧ�Ĳۺ���
    timer->start(5000);//��ʱ����ʼ��ʱ��1��

//    this->setMouseTracking(true);//����widget��������
}

Widget::~Widget()
{
    delete showImage;
}

void Widget::turn2next()
{
    showImage->show_next();
}

void Widget::turn2prev()
{
    showImage->show_prev();;
}

void Widget::dirChanged(QString newfile)
{
    showImage->init_path((fileDialog->directory()), newfile);
}

void Widget::scalethepix(int scale)
{
    showImage->arise_scale(scale);
}

//�������Ż�������ʾ�ٷ�֮��
void Widget::changelabel(int val)
{
    QString tmp;
    tmp.setNum(val);
    tmp += "%";
    label->setText(tmp);
}

void Widget::AutoPlay()
{
    if(AutoPlayFlag == true)
        showImage->show_next();
}

void Widget::ChangeAutoPlayFlag(bool flag)
{
    AutoPlayFlag = flag;
}

void Widget::wheelEvent(QWheelEvent *event)
{
    QString str;
    switch(event->orientation())//���ع��ַ���:ˮƽ��ֱ
    {
    case Qt::Horizontal:
        str = "Horizontal Whell Move";
        break;
    case Qt::Vertical:
        str = "Vertical Whell Move";
        break;
    default:
        break;
    }
    str += "\n";
    str += "    ";
    if(event->delta()>0)//���ع�������
        str += "go ahead";
    else
        str += "go back";
    qDebug()<<str;
    int numDegrees = event->delta() / 8;//15��
    int numSteps = numDegrees / 15;//1��
    int value = slider->value();
    slider->setValue(value+numDegrees);

}
