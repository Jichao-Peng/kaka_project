//
// Created by leo on 18-4-19.
//

#ifndef PROJECT_KAKAINTERFACE_H
#define PROJECT_KAKAINTERFACE_H

#include <ros/ros.h>
#include <rviz/panel.h>
#include <ros/console.h>
#include <geometry_msgs/Twist.h>
#include <kaka_interface_pkg/InterfaceCtrl.h>
#include <QLabel>
#include <QTimer>
#include <QDebug>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>



namespace kaka_interface_pkg
{

    class KakaInterface : public rviz::Panel
    {
        Q_OBJECT

    public:
        KakaInterface(QWidget *parent = 0);

        //重载rviz::Panel中的函数，用于保存、加载配置文件中的数据，在这个plugin中，数据就是topic的名称
        virtual void load(const rviz::Config &config);
        virtual void save(rviz::Config config) const;

    public Q_SLOTS:
        void on_StartButton_clicked();
        void on_StopButton_clicked();
        void on_SampleButton_clicked();
        void on_CalculateButton_clicked();

    protected:
        ros::NodeHandle Node;
        ros::Publisher CalibCmdPub;

        QString OutputTopic;
        QPushButton *StartButton;
        QPushButton *StopButton;
        QPushButton *SampleButton;
        QPushButton *CalculateButton;

        kaka_interface_pkg::InterfaceCtrl CalibCmd;
    };

}


#endif //PROJECT_KAKAINTERFACE_H
