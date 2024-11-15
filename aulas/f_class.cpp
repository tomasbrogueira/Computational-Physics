#include<iostream>
#include<array>
#include<string>
#include<cstdio>
#include<TROOT.h>


using namespace std;

//////////////////////////////////////////
// classes declarations

class Point2D{

    public:
    Point2D(float x = 0, float y = 0, string name="");
    ~Point2D();
    
    void Print() const;

    Point2D(const Point2D&);

    //operator
    Point2D operator =(const Point2D&);
    Point2D operator +(const Point2D&);


    //output
    friend ostream& operator << (ostream&, const Point2D&);


    private:
    string name;
    array<float,2> coo;
};


class Point3D : public Point2D {
    public:
    Point3D(float x=0, float y=0, float z_=0, string name="") : Point2D(x,y,name), z(z_){}
    private:
    float z;
};


//////////////////////////////////////////
// implementation

Point2D :: Point2D(float x, float y, string name_){
    coo = {x,y};
    name = name_;
    printf("[%s] %s:(%.1f,%.1f)\n",__PRETTY_FUNCTION__,name.c_str(),coo[0],coo[1]);

};

Point2D :: ~Point2D(){};  // feito automaticamente pelo compilador

void Point2D :: Print() const{
    printf("[%s] %s: (%.1f,%.1f)\n",__PRETTY_FUNCTION__,name.c_str(),coo[0],coo[1]);
};

Point2D :: Point2D(const Point2D& P){
    name = P.name+"_copy";
    coo = P.coo;

};


// operators
Point2D  Point2D :: operator =(const Point2D& P){
    if(this != &P){
        name = P.name;
        coo = P.coo;
    }
    cout << "operator=" << endl;
    return Point2D(*this);
};

Point2D Point2D :: operator+(const Point2D& P){
    return Point2D(coo[0]+P.coo[0],coo[1]+P.coo[1], Form("%s_sum_%s",name.c_str(),P.name.c_str()));  //form é do root tb existe sprintf(valverde)
}



// friends (!)

ostream& operator << (ostream& s, const Point2D& P){
    s << P.name << ": (" << P.coo[0] << P.coo[1] << ")";
    return s;
}

/////////////////////////////////////////
// main program

int main(){
    {
    Point2D P0;
    Point2D* p = new Point2D(3,3,"Pdynamic");
    printf("& de p: [%p]\n",p);
    delete p;    // objetos que estao a ser pointed nao sao deleted a n ser que o facamos nos proprios
    }
    Point2D P1(6,9,"noice");
    Point2D P2(P1);
    Point2D P3;

    cout << P1 << P2 << endl;
    P3 =P1=P2;
    cout <<P3 <<endl;
}