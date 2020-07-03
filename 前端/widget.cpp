#include "widget.h"
#include "ui_widget.h"
#include "qt_head.h"
#include "x_mhead.h"
#include "x_filerw.h"
#include "x_tree.h"
#include "x_entrophy.h"


//判定函数
void judge(vector<vector<string>> data)
{

//    for(int i=1;i<data.size();i++)//每次循环对一行数据（即一个样本）进行判断
//   {
//        //假设已知根节点为Node p=rootNode,其属性为A[i],A的属性值为a[j]
//        if(data[i][])


//   }

}

  double change(string s)
{
    double out;
    stringstream ss;
    ss<<s;
    ss>>out;
    return out;
}//string转double函数

Widget::Widget(QWidget *parent) :
    QWidget(parent),

   ui(new Ui::Widget)
{
    ui->setupUi(this);
//几个预备的操作
    resultpath="result.csv";//存放result.csv的地址
    gainpath="Gain.txt";  //存放Gain.txt的地址
    this->setWindowIcon(QIcon(":/new\\w.jpg"));//设置窗口图标
    this->setWindowTitle("决策树");//设置窗口标题

//打开文件按钮
       connect(ui->openfilebutton,&QPushButton::clicked,[=]()
       {
       QString path= QFileDialog::getOpenFileName(this,"open","此电脑");
       ui->filepathlineEdit->setText(path); //将文件路径存入pathline

       QFile file(path);//选择打开的文件
       file.open(QIODevice::ReadOnly);//设置打开方式
       QByteArray arry=file.readAll(); //打开全部内容
       string xpath=datapath= path.toStdString();//将qstring类型的地址转为string类型，存入xpath中
       vector<vector<string>> data=myReadFile(xpath);//调用读取文件函数，返回结果存入二维数组data中
       pridata=transpose(data);//将二维数组data转置,赋给原始数据数组
       //在初始数据pridata被赋值后，可进行如下操作
       //为质量quality赋值
                 for(int i=0;i<pridata.size();i++)
                 quality.push_back(pridata[i][9]);
       //为属性与属性值的映射关系valuemap赋值
                 trandata=transpose(pridata);
                 MapGen(trandata,valuemap);

       //设置表格
       ui->pridatatableWidget->setColumnCount(9); //设置列数
       ui->pridatatableWidget->setHorizontalHeaderLabels(QStringList()<<"色泽"<<"根蒂"<<"敲声"<<"纹理"<<"脐部"<<"触感"<<"密度"<<"含糖率"<<"好瓜");//设置水平表头
       ui->pridatatableWidget->setRowCount(pridata.size()-1);//设置行数
       //设置表格内容
       for(int i=1;i<pridata.size();i++)
       {
           for(int j=1;j<10;j++)
           ui->pridatatableWidget->setItem(i-1,j-1,new QTableWidgetItem(  QString::fromStdString(pridata[i][j])));
       }

       });

//计算信息增益按钮
       connect(ui->gainpushButton,&QPushButton::clicked,[=]()

       {   //trandata为转置后的数据，quality为好坏这一列，valuemap为属性与属性值的映射

           for(int i=0;i<valuemap.size()-3;i++)//计算前6个属性的信息增益
             {
               gain.push_back(InfoGain(trandata[i+1.0],quality,valuemap));

              }
           for(int i=trandata.size()-3;i<trandata.size()-1;i++)//计算后两个属性的信息增益
              {
               {

                   double v;
                   vector<double> temp=vStr2vDouble(trandata[i]);
                   gain.push_back(InfoGain(trandata[i][0],temp,quality,valuemap,v));
               }
               }

//为信息增益的表格赋值
         ui->gaintableWidget->setColumnCount(2);
         ui->gaintableWidget->setHorizontalHeaderLabels(QStringList()<<"属性"<<"信息增益");
         ui->gaintableWidget->setRowCount(8);

         ui->gaintableWidget->setItem(0,0,new QTableWidgetItem(QString::fromStdString("色泽")));
         ui->gaintableWidget->setItem(0,1,new QTableWidgetItem(QString::number(gain[0], 10, 4)));

         ui->gaintableWidget->setItem(1,0,new QTableWidgetItem(QString::fromStdString("根蒂")));
         ui->gaintableWidget->setItem(1,1,new QTableWidgetItem(QString::number(gain[1], 10, 4)));

         ui->gaintableWidget->setItem(2,0,new QTableWidgetItem(QString::fromStdString("敲声")));
         ui->gaintableWidget->setItem(2,1,new QTableWidgetItem(QString::number(gain[2], 10, 4)));

         ui->gaintableWidget->setItem(3,0,new QTableWidgetItem(QString::fromStdString("纹理")));
         ui->gaintableWidget->setItem(3,1,new QTableWidgetItem(QString::number(gain[3], 10, 4)));

         ui->gaintableWidget->setItem(4,0,new QTableWidgetItem(QString::fromStdString("脐部")));
         ui->gaintableWidget->setItem(4,1,new QTableWidgetItem(QString::number(gain[4], 10, 4)));

         ui->gaintableWidget->setItem(5,0,new QTableWidgetItem(QString::fromStdString("触感")));
         ui->gaintableWidget->setItem(5,1,new QTableWidgetItem(QString::number(gain[5], 10, 4)));

         ui->gaintableWidget->setItem(6,0,new QTableWidgetItem(QString::fromStdString("密度")));
         ui->gaintableWidget->setItem(6,1,new QTableWidgetItem(QString::number(gain[6], 10, 4)));

         ui->gaintableWidget->setItem(7,0,new QTableWidgetItem(QString::fromStdString("含糖率")));
         ui->gaintableWidget->setItem(7,1,new QTableWidgetItem(QString::number(gain[7], 10, 4)));
        }
 );


//保存信息增益按钮
    connect(ui->savegainpushButton,&QPushButton::clicked,[=]()

       {
           //提取表头headline
           vector <string>headline;
           headline.clear();
           for (int i = 0; i < trandata.size(); i++)
           {
               headline.push_back(trandata[i][0]);
           }
              WriteGain(headline,gain,gainpath );
              QMessageBox::information(this,"提示","信息增益已保存至Gain.txt!");

       });


//生成决策树按钮
   connect(ui->treemakepushButton,&QPushButton::clicked,[=]()
     {
        Tree t;
        t.TreeGenerate(trandata,quality,valuemap);//调用生成决策树函数
        t.show(t.TreeGenerate(trandata,quality,valuemap),valuemap);

        //实例化一个窗口
         pixiv=new pictur;
         QTimer::singleShot(600,this,[=](){pixiv->show();});//延迟打开决策树图片
     });


//生成随机数据按钮
     connect(ui->randompushButton,&QPushButton::clicked,[=]()

 {
       vector<vector<string>> random_Generate(int n);//随机生成函数声明
       randomdata=random_Generate(ui->xiguanumlineEdit->text().toInt());//调用随机函数生成样本,返回值赋给随机数据数组
       //设置表格
       ui->randomdatatableWidget->setColumnCount(9);//设置列数
       ui->randomdatatableWidget->setHorizontalHeaderLabels(QStringList()<<"色泽"<<"根蒂"<<"敲声"<<"纹理"<<"脐部"<<"触感"<<"密度"<<"含糖率"<<"好瓜");//设置水平表头
       ui->randomdatatableWidget->setRowCount(randomdata.size()-1);//设置行数
       //设置表格内容
       for(int m=1;m<randomdata.size();m++)
               {
                   for(int n=1;n<10;n++)
                   ui->randomdatatableWidget->setItem(m-1,n-1,new QTableWidgetItem(  QString::fromStdString(randomdata[m][n]) ));
               }
 });



//判定按钮
   connect(ui->judgepushButton,&QPushButton::clicked,[=]()

   {
     clock_t start=clock();//记录起始时间

    for(int t=1;t<randomdata.size();t++)
    {    if(randomdata[t][4]=="模糊")
             randomdata[t][9]="否";
         else if(randomdata[t][4]=="稍糊")
         {if(randomdata[t][6]=="硬滑") randomdata[t][9]= "否";
          if(randomdata[t][6]=="软黏") randomdata[t][9]= "是";
         }

     else if(randomdata[t][4]=="清晰")
         {
             if(change(randomdata[t][7])<=0.3815)
                 randomdata[t][9]="否";
             if(change(randomdata[t][7])>0.3815)
                 randomdata[t][9]="是";
         }
        ui->randomdatatableWidget->setItem(t-1,8,new QTableWidgetItem(QString::fromStdString(randomdata[t][9])));
        }

      clock_t end=clock();//记录结束时间
      double t=(double)(end - start) / CLOCKS_PER_SEC;
      ui->timelineEdit->setText(QString::number(t, 10, 4));//将时间显示到窗口
   });


//保存随机数据按钮
    connect(ui->savedatapushButton,&QPushButton::clicked,[=]()
     {

       WriteFile(randomdata,resultpath);
       QMessageBox::information(this,"提示","结果已保存至result.csv！");

     });

}


Widget::~Widget()
{
    delete ui;
}
