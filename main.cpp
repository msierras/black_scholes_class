#include <iostream> 
#include <array>
#include <cmath>
#include <numbers>



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

    // The non-trivial case for pricing an option is before it has expired (time_to_exp_ > 0.0). In this case, the Black-Scholes formula is applied.
    if(time_to_exp_ > 0.0){
        // Calculating the values of d1 and d2, which will be used as arguments in the standard normal CDF
        auto norm_args = compute_norm_args_(vol);

        // d1 and d2 are stored in the array<double, 2> container norm_args and accessed by using the usual square bracket operator. 
        double d1 = norm_args[0];
        double d2 = norm_args[1];

        // We get the N(d1) and N(d2) values via a lambda expression that invokes the error function erf(.)  
        auto norm_cdf = [](double x){
            return (1.0 + std::erf(x / std::numbers::sqrt2)) / 2.0;
        };

        // Calculating nd_1 and nd_2 via the norm_cdf lambda expression we declared above 
        double nd_1 = norm_cdf(phi * d1);   // N(d1)
        double nd_2 = norm_cdf(phi * d2);   // N(d2)

        // Computing the discount factor from T back to time t (time_to_exp_ = T - t) 
        double disc_fctr = exp(-rate_ * time_to_exp_);

        return phi * (spot_* exp(-div_ * time_to_exp_) * nd_1 - disc_fctr * strike_ * nd_2); 
    }
    else{   // In the event the option is expired, its value is simply the raw payoff
        return std::max(phi * (spot_ - strike_), 0.0);
    }

}


std::array<double, 2> BlackScholes::compute_norm_args_(double vol){
    double numer = log(spot_ / strike_) + (rate_ - div_ + 0.5 * vol * vol) * time_to_exp_;
    
    // calculating d1 and d2
    double d1 = numer / (vol * sqrt(time_to_exp_));
    double d2 = d1 - vol * sqrt(time_to_exp_);
    
    return std::array<double, 2>{d1, d2}; 
}



int main(){

    // Variables that will store the user's choices. 
    std::string strike_input, spot_input, time_to_exp_input, rate_input, vol_input, div_input;


    std::string payoff_type_input;
    PayoffType payoff_type; 
    


    for(;;){

            /* Menu */

            std::cout << "What payoff type? (Call/Put):\n";
            std::getline(std::cin, payoff_type_input);

            if(payoff_type_input == "Call" || payoff_type_input == "call"){
                payoff_type = PayoffType::Call;    // auto payoff_type = 1;
            }
            else if(payoff_type_input == "Put" || payoff_type_input == "put"){
                payoff_type = PayoffType::Put;     // auto payoff_type = -1; 
            }
            else{
                std::cout << "Invalid payoff type. Exiting.....";
                break;
            }


            std::cout << "Enter a strike price:\n";
            std::getline(std::cin, strike_input);
            double strike = std::stod(strike_input);



            std::cout << "Enter a spot price:\n";
            std::getline(std::cin, spot_input);
            double spot = std::stod(spot_input);


            std::cout << "Enter an expiration time:\n";
            std::getline(std::cin, time_to_exp_input);
            double time_to_exp = std::stod(time_to_exp_input);
            
            
            std::cout << "Enter a rate\n";
            std::getline(std::cin, rate_input);
            double rate = std::stod(rate_input);
            

            std::cout << "Enter a vol:\n";
            std::getline(std::cin, vol_input);
            double vol = std::stod(vol_input);


            std::cout << "Enter dividend yield (or press Enter to use default value 0.0):\n";
            std::getline(std::cin, div_input);

            // Once we have all user inputs we create a BlackScholes object
            
            // If user enters a value
            if( !(div_input.empty()) ){
                double div = std::stod(div_input);
                BlackScholes test{strike, spot, time_to_exp, payoff_type, rate, div};

                // add calculations here later .........
            }
            else{   // Else user presses Enter to use default dividend value of 0.0
                BlackScholes test{strike, spot, time_to_exp, payoff_type, rate};
                // add calculations here later .........
            }

            
        } 

    

    

    // double strike = 75.0;
    // double spot = 100.0;
    // double time_to_exp = 0.0; 
    // auto payoff_type = PayoffType::Call;    // auto payoff_type = 1; 
    // double rate = 0.05;
    
    // double vol = 0.25;
    
    
    // //double strike, double spot, double time_to_exp, PayoffType payoff_type, double rate, double div = 0.0
    // // ITM Call at expiration (time_to_exp = 0);
    // BlackScholes bsc_itm_exp{strike, spot, time_to_exp, payoff_type, rate};

    // double value = bsc_itm_exp(vol);
    // std::cout << value;


    return 0;
}