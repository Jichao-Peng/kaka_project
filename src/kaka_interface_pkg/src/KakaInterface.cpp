//
// Created by leo on 18-4-19.
//

#include "KakaInterface.h"

namespace kaka_interface_pkg
{
    KakaInterface::KakaInterface(QWidget *parent)
            : rviz::Panel(parent)
    {
        QVBoxLayout *VLayout = new QVBoxLayout;
        VLayout->addWidget(new QLabel("Calibration Controll: "));
        StartButton = new QPushButton("Start",this);
        VLayout->addWidget(StartButton);
        StopButton = new QPushButton("Stop",this);
        VLayout->addWidget(StopButton);
        SampleButton = new QPushButton("Sample",this);
        VLayout->addWidget(SampleButton);
        CalculateButton = new QPushButton("Calculate",this);
        VLayout->addWidget(CalculateButton);

        QHBoxLayout *HLayout = new QHBoxLayout;
        HLayout->addLayout(VLayout);
        setLayout(HLayout);

        connect(StartButton, SIGNAL(clicked()), this, SLOT(on_StartButton_clicked()));
        connect(StopButton, SIGNAL(clicked()), this, SLOT(on_StopButton_clicked()));
        connect(SampleButton, SIGNAL(clicked()), this, SLOT(on_SampleButton_clicked()));
        connect(CalculateButton, SIGNAL(clicked()), this, SLOT(on_CalculateButton_clicked()));

        CalibCmdPub = Node.advertise<kaka_interface_pkg::InterfaceCtrl>("/calibration_cmd",1000);
    }


    void KakaInterface::on_StartButton_clicked()
    {
        ROS_INFO("[KAKA_INTERFACE] Start!");
        CalibCmd.Cmd = 1;
        CalibCmdPub.publish(CalibCmd);
    }

    void KakaInterface::on_StopButton_clicked()
    {
        ROS_INFO("[KAKA_INTERFACE] Stop!");
        CalibCmd.Cmd = 2;
        CalibCmdPub.publish(CalibCmd);
    }

    void KakaInterface::on_SampleButton_clicked()
    {
        ROS_INFO("[KAKA_INTERFACE] Sample!");
        CalibCmd.Cmd = 3;
        CalibCmdPub.publish(CalibCmd);
    }

    void KakaInterface::on_CalculateButton_clicked()
    {
        ROS_INFO("[KAKA_INTERFACE] Calculate!");
        CalibCmd.Cmd = 4;
        CalibCmdPub.publish(CalibCmd);
    }

    //save和load是rviz固定的接口
    void KakaInterface::save(rviz::Config config) const
    {
        rviz::Panel::save(config);
    }

    void KakaInterface::load(const rviz::Config &config)
    {
        rviz::Panel::load(config);
    }

}
//申明此类是rviz的一个插件
#include <pluginlib/class_list_macros.h>
PLUGINLIB_EXPORT_CLASS(kaka_interface_pkg::KakaInterface, rviz::Panel);
