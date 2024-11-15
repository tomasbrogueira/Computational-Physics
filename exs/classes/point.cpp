class Point2D{
    public:
    virtual Point2D (double xi, double yi);
    ~Point2D();

    private:

    double x;
    double y;

};

Point2D::Point2D (double xi, double yi){
        x=xi;
        y=yi;
    };


class Point3D
{
private:
    double z;
public:
    Point3D(double xi, double yi,double zi);
    ~Point3D();
};

Point3D::Point3D(double xi, double yi,double zi)
{
    Point2D(xi,yi);
    z=zi;
}
