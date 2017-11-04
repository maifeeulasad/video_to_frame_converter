#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<bits/stdc++.h>
#include<direct.h>
#include<windows.h>
#include<sys/types.h>
#include<sys/stat.h>


using namespace cv;
using namespace std;


bool is_dir(string pathname);
string n_num(string x);
const char * csa(string x);
string p_name();
string create_dir(string filename);


string cur_dir=p_name();


int main()
{
    string filename;
    printf("Supported formats *.avi , *.mp4 , *.3gp , *.flv , *.wmv , *.AVI , *.MP4 , *.3GP , *.FLV , *.WMV\n");
    printf("PLease enter a video file name (with proper extension) : \n");
    cin >> filename;
    ifstream test(filename);
    if(!test)
        cout << filename << " doesn't exist" << endl;
    else
    {
        VideoCapture capture(filename);
        Mat frame;
        if(!capture.isOpened())
            throw "Error when reading steam_video";
        string loc=create_dir(filename);
        string se = "0" ;
        int total = capture.get(CV_CAP_PROP_FRAME_COUNT);
        for(int ct=0; ; ct++, se = n_num(se))
        {
            capture >> frame;
            if(frame.empty())
                break;
            imwrite(loc+"/frame_"+se+".jpg", frame);
            printf("[%3.2lf%c] - done (written - frame_",(100*(double)ct)/(double)total,37);
            cout << se + ".jpg )" << endl;
        }
        printf("[%3d%c] - done ",100,37);
    }
    return 0;
}


bool is_dir(string pathname)
{
    struct stat info;
    if( stat( pathname.c_str(), &info ) != 0 )
        return false;
    if( info.st_mode & S_IFDIR )
        return true;
    return false;
}


string n_num(string x)
{
    int len=x.size();
    int c9=0;
    for(int i=0; i<len; i++)
    {
        if(x[i]=='9')
            ++c9;
    }
    if(c9==len)
    {
        for(int i=0; i<len; i++)
            x[i]='0';
        return "1"+x;
    }
    while(x[--len]=='9')
        x[len]='0';
    x[len]++;
    return x;
}


const char * csa(string x)
{
    const char *tem = x.c_str();
    return tem;
}


string p_name()
{
    char buffer[MAX_PATH];
    GetModuleFileName(NULL,buffer,MAX_PATH );
    string::size_type pos=string(buffer).find_last_of("\\/");
    return string(buffer).substr(0,pos);
}


string create_dir(string filename )
{
    string ser = "1";
    mkdir(csa(cur_dir+"/generated_files"));
    if(is_dir(csa(cur_dir+"/generated_files/"+filename))!=true)
    {
        mkdir(csa(cur_dir+"/generated_files/"+filename));
        return cur_dir+"/generated_files/"+filename;
    }
    while(is_dir(csa(cur_dir+"/generated_files/"+filename+ser))!=false)
        ser=n_num(ser);
    mkdir(csa(cur_dir+"/generated_files/"+filename+ser));
    return cur_dir+"/generated_files/"+filename+ser;
}
