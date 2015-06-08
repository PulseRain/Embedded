class my_complex 
{
    public:
        
        explicit my_complex(int x) : _x {x}, _y {0} {}
        explicit my_complex(int x, int y) : _x {x}, _y {y} {}
        
        friend my_complex operator*(const my_complex &a, 
                                      const my_complex &b)
        {
            int x, y;
    
            x = a._x * b._x - a._y * b._y;
            y = a._x * b._y + a._y * b._x;
            
            my_complex tmp{x, y};
            
            return tmp;
        }
    
    private :
        int _x, _y;
    
};

template <typename T>
T mult_neg (const T& a, const T& b)
{
    T minus_one{-1};
    
    return (a * b * minus_one);
}

int main() 
{
    
    my_complex aaa{1,2};
    my_complex bbb{3,7};
    
    //int t = mult_neg(2,3);
    my_complex ccc = mult_neg(aaa, bbb);
    my_complex ddd = mult_neg(bbb, aaa);
}
