#include <iostream> 
#include <array>

// PayoffType will represent a call (1) or a put (-1) 
enum class PayoffType{
    Call = 1,
    Put = -1 
};

class BlackScholes{
    public:
        /* BlackScholes constructor(s) */
        BlackScholes(double strike, double spot, double time_to_exp, PayoffType payoff_type, double rate, double div = 0.0);
        
        /* Operator overloading function(s) */
        double operator()(double vol); 

    private:
        // Using trailing underscores for private member variables and private member functions. 
        
        std::array<double, 2> compute_norm_args_(double vol);

        
        double strike_, spot_, time_to_exp_;
        PayoffType payoff_type_;
        double rate_, div_; 


    


};


int main(){




    return 0;
}