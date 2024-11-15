void sum(const std::array<double,100>& a){
    double s = 0;
    for (int i = 0; i < 100; i++){
        s += a[i];
    }
    std::cout << "sum = " << s << std::endl;
}

// nao pq recebe um array por referencia

double sum(const std::array<double,100>& a){
    double s = 0;
    for (int i = 0; i < 100; i++){
        s += a[i];
    }
    return s;
}