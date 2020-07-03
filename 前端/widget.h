#ifndef WIDGET_H
#define WIDGET_H
#include "pictur.h"
#include "x_mhead.h"
#include <QWidget>
#include <QPainter>
namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    std::vector<std::vector<std::string>> pridata;//定义一个全局的二维数组来储存原始数据
    std::vector<std::vector<std::string>> trandata;//pridata转置后的数组
    std::vector<std::vector<std::string>> randomdata;//定义一个全局的二维数组来储存随机数据
    std::string datapath;//定义一个全局变量来储存data.scv的地址
    std::string resultpath;//定义一个全局变量来储存result.scv的地址
    std::string gainpath;//定义一个全局变量来储存Gain.txt的地址
    map<std::string,std::vector<std::string>>  valuemap;//定义一个map，用以储存属性与属性值的映射关系
    std::vector<std::string> quality;//定义一个向量来储存原始数据的好坏这一列
    std::vector<double> gain;//定义一个数组来储存信息增益
    pictur * pixiv=NULL;//定义一个新的窗口


private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
