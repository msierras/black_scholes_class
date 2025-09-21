#include <iostream> 
#include <array>

// 𝜙 = PayoffType will represent a call (1) or a put (-1) 
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
        
        std::array<double, 2> compute_norm_args_(double vol);   // will calculate the d1 and 2 values, and return them in a fixed two-element std::array container.

        double strike_, spot_, time_to_exp_;
        PayoffType payoff_type_;
        double rate_, div_; 
};

// Implementing the BlackScholes class constructor
BlackScholes::BlackScholes(double strike, double spot, double time_to_exp, PayoffType payoff_type, double rate, double div) : strike_{strike}, spot_{spot}, time_to_exp_{time_to_exp}, payoff_type_{payoff_type}, rate_{rate}, div_{div} {};





int main(){




    return 0;
}