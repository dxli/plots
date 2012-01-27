//plot ascan.txt
#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>
#include<iterator>
#include<algorithm>
#include<string>
#include<cmath>
#include<grace_np.h>
#include<fftw3.h>
using namespace std;
int main(int argc,char *argv[])
{
    string fn0,fn1;
    if(argc<2) {
        cout<<"usage::  plotGrasp <grasp data file>"<<std::endl;
        fn0=string("~/jintronixGit/code/bin/Aquabulb_GloveGraspData.csv");
    }else{
        fn0=string(argv[1]);
    }
        cout<<"Plotting default Grasp Data file "<<fn0<<endl;
    if (GraceOpen(20480) == -1) {
        fprintf(stderr, "Can't run Grace. \n");
        exit(EXIT_FAILURE);
    }
    vector<string> legends;
    legends.push_back(string("Index"));
    legends.push_back(string("Middle"));
    legends.push_back(string("Thumb"));
    for(unsigned int i=0;i<3;i++){
    GracePrintf("s%1d on",i);
    GracePrintf("s%1d symbol 0",i);
    GracePrintf("s%1d line linestyle 1",i);
    GracePrintf("s%1d legend \"%s\"",i,legends[i].c_str());
    }
    ifstream in1(fn0.c_str());
    if(!in1.is_open()) {
        cout<<"can not read "<<fn0<<endl;
        exit(0);
    }
    string linebuf;
    vector<vector<double> > v_pe;
    getline(in1,linebuf); //discard the first comment line
    while (getline(in1,linebuf)){
        replace_if(linebuf.begin(),linebuf.end(),[](char input)->bool{return input==',';},' ');
        istringstream iss(linebuf);
        vector<double> va;
        copy(istream_iterator<double>(iss), istream_iterator<double>(), back_inserter(va));
        if(va.size() < 2) break;
        v_pe.push_back(va);
    }
    in1.close();

    for(unsigned int i0=0;i0<v_pe.size();i0++){
        for(unsigned int j=0;j<3;j++){
    GracePrintf("s%1d point %g,%g",j,v_pe[i0][0],v_pe[i0][j+1]);
        }
    }
    GracePrintf("autoscale");
    GracePrintf("xaxis  tick major grid on");
    GracePrintf("redraw");
    GraceFlush();
    return 0;
}

