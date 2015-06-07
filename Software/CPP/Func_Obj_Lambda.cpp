#include <iostream>

class func_obj_add_sub
{
    public:
        func_obj_add_sub (int mode): _mode {mode} {};

        int operator() (const int a, const int b)
        {
            if (_mode == 0) {
                _mode = 1;
                return a + b;
            } else {
                _mode = 0;
                return a - b;
            }
        }
    private:
        int _mode;
};

int main()
{
   auto add = [](const int a, const int b){return a + b;};
    auto sub = [](const int a, const int b){return a - b;};
    
    func_obj_add_sub add_sub{0};
    
    std::cout << "1st call " << add_sub (6, 4) << "\n";
    std::cout << "2nd call " << add_sub (6, 4) << "\n";
    std::cout << add (6, 4) << " " << sub (6, 4) << "\n";
        
}
