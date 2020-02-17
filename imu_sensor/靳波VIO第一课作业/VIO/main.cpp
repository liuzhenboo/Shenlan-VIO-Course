#include <QCoreApplication>
#include<iostream>
#include<Eigen/Eigen>
using namespace std;
using namespace Eigen;
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Matrix3d R;

    AngleAxisd v(M_PI/4,Vector3d(0,0,1));//旋转向量
    R=v.toRotationMatrix();//旋转向量转为旋转矩阵
    cout<<" Rotation Matrix:"<<endl<<endl;
    cout<<R<<endl;
    cout<<endl;

    Quaterniond q(R);//旋转矩阵转四元数
    cout<<" Quaternion:"<<endl<<endl;
    cout<<q.w()<<" "<<q.x()<<" "<<q.y()<<" "<<q.z()<<endl;
    cout<<endl;

    Vector3d w(0.01,0.02,0.03);//三维向量，求其对应轴角，然后使用罗德里格斯公式计算旋转矩阵
    double angle=pow(w(0)*w(0)+w(1)*w(1)+w(2)*w(2),0.5);//求三维向量对应角
    Vector3d axis=w/angle;//求三维向量对应轴
    Matrix3d detR;//求旋转矩阵

    Matrix3d I;
    I.setIdentity();//单位矩阵
    Matrix3d n;//轴对应的反对称矩阵
    n<<0,-axis(2),axis(1),
       axis(2),0,-axis(0),
       -axis(1),axis(0),0;
    detR=cos(angle)*I+(1-cos(angle))*axis*axis.transpose()+sin(angle)*n;//使用罗德里格斯公式计算旋转矩阵

    R=R*detR;//更新矩阵
    cout<<" Updated Rotation Matrix:"<<endl<<endl;
    cout<<R<<endl;
    cout<<endl;


    Quaterniond detq(1,0.5*w(0),0.5*w(1),0.5*w(2));
    q=q*detq;//更新四元数
    cout<<" Updated Quaternion:"<<endl<<endl;
    cout<<q.w()<<" "<<q.x()<<" "<<q.y()<<" "<<q.z()<<endl;
    cout<<endl;

    q.normalized();
    Matrix3d R1=q.toRotationMatrix();
    cout<<" Updated Rotation Matrix from Quaternion:"<<endl<<endl;
    cout<<R1<<endl;
    cout<<endl;

    cout<<"更新旋转矩阵和更新四元数得到的结果基本相同"<<endl;

    return a.exec();
}

