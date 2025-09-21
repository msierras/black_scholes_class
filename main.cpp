#include <iostream> 
#include <array>
#include <cmath>

// 𝜙 = PayoffType will represent a call (1) or a put (-1) 
enum class PayoffType{
    Call = 1,
    Put = -1 
};

class BlackScholes{
    public:
        /* BlackScholes constructor(s) prototype(s) */
        BlackScholes(double strike, double spot, double time_to_exp, PayoffType payoff_type, double rate, double div = 0.0);
        
        /* Operator overloading function(s) prototype(s) */
        double operator()(double vol); 

    private:
        // Using trailing underscores for private member variables and private member functions. 
        
        std::array<double, 2> compute_norm_args_(double vol);   // will calculate the d1 and d2 values, and return them in a fixed two-element std::array container.

        double strike_, spot_, time_to_exp_;
        PayoffType payoff_type_;
        double rate_, div_; 
};

// Implementing the BlackScholes class constructor
BlackScholes::BlackScholes(double strike, double spot, double time_to_exp, PayoffType payoff_type, double rate, double div) : strike_{strike}, spot_{spot}, time_to_exp_{time_to_exp}, payoff_type_{payoff_type}, rate_{rate}, div_{div} {};

// Implementing the BlackScholes () operator overloading 
double BlackScholes::operator()(double vol){
    using std::exp;

    const int phi = static_cast<int>(payoff_type_); // recovering the value of phi by casting the payoff type enumerator to its constant integer equivalent

    if(time_to_exp_ > 0.0){
        auto norm_args = compute_norm_args_(vol);
        double d1 = norm_args[0];
        double d2 = norm_args[1];

        auto norm_cdf = [](double x){
            return (1.0 + std::erf(x / std::numbers::sqrt2)) / 2.0;
        };

        double nd_1 = norm_cdf(phi * d2);   // N(d1)
        double nd_2 = norm_cdf(phi * d2);   // N(d2)
        double disc_fctr = exp(-rate_ * time_to_exp_);

        return phi * (spot_* exp(-div_ * time_to_exp_) * nd_1 - disc_fctr * strike_ * nd_2);
    }
    else{
        return std::max(phi * (spot_ - strike_), 0.0);
    }

}




int main(){




    return 0;
}