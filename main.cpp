#include <iostream>
#include <vector>

using namespace std;

enum class PizzaSize
{
    SMALL,
    MEDIUM,
    LARGE
};

enum class PizzaName {
    Margherita,
    CustomizedMargherita,
    Paneer,
    CustomizedPaneer,
    Chicken,
    CustomizedChicken
};

enum class Toppings
{
    CHEESE,
    PANEER,
    CHICKEN,
    MUSHROOM,
    ONION,
    TOMATO,
    EXTRA_CHEESE,
    BLACK_OLIVES,
    GREEN_PEPPERS
};

class Pizza
{
private:
    double _basePrice;

string displayPizzaName(){
        switch (_pizzaName)
        {
        case PizzaName::Margherita :
            return "Margharita Pizza";
        
        case PizzaName::Paneer :
            return "Paneer Pizza";
        
        case PizzaName::Chicken :
            return "Chicken Pizza";

        case PizzaName::CustomizedMargherita :
            return "Customized Margharita Pizza";

        case PizzaName::CustomizedPaneer :
            return "Customized Paneer Pizza";

        case PizzaName::CustomizedChicken :
            return "Customized Chicken Pizza";
        
        default:
            return "";
        }

    }

string getPizzaSize(){
        return _pizzaSize;
    }

    
protected:
    PizzaName _pizzaName;
    PizzaSize _size;
    
    string _pizzaSize;

    
    void setPizzaPrice()
    {
        switch (_size)
        {
        case PizzaSize::SMALL:
            _basePrice = 200;
            break;

        case PizzaSize::MEDIUM:
            _basePrice = 300;
            break;

        case PizzaSize::LARGE:
            _basePrice = 500;
            break;

        default:
            break;
        }
    }

    void setPizzaSize()
    {
        switch (_size)
        {
        case PizzaSize::SMALL:
            _pizzaSize = "Small";
            _basePrice = 200;
            break;

        case PizzaSize::MEDIUM:
            _pizzaSize = "Medium";
            _basePrice = 300;
            break;

        case PizzaSize::LARGE:
            _pizzaSize = "Large";
            _basePrice = 500;
            break;

        default:
            break;
        }
    }

    string displayToppings(const Toppings &t)
    {
        switch (t)
        {
        case Toppings::CHEESE:
            return "Cheese";
        case Toppings::PANEER:
            return "Paneer";
        case Toppings::CHICKEN:
            return "Chicken";
        case Toppings::ONION:
            return "Onion";
        case Toppings::GREEN_PEPPERS:
            return "Green Pepper";
        case Toppings::TOMATO:
            return "Tomato";
        case Toppings::MUSHROOM:
            return "Mushroom";
        case Toppings::EXTRA_CHEESE:
            return "Extra Cheese";
        case Toppings::BLACK_OLIVES:
            return "Black Olives";
        default:
            return "";
        }
    }

    double getToppingsPrize(const Toppings &t)
    {
        switch (t)
        {
        case Toppings::CHEESE:
            return 15;
        case Toppings::PANEER:
            return 20;
        case Toppings::CHICKEN:
            return 40;
        case Toppings::ONION:
            return 10;
        case Toppings::GREEN_PEPPERS:
            return 15;
        case Toppings::TOMATO:
            return 12;
        case Toppings::MUSHROOM:
            return 10;
        case Toppings::EXTRA_CHEESE:
            return 35;
        case Toppings::BLACK_OLIVES:
            return 20;
        default:
            return 0;
        }
    }

    
public:
    Pizza(PizzaName name, PizzaSize size) : _size(size)
    {

        _pizzaName = name;
        setPizzaSize();
        setPizzaPrice();
    };


    
    void displayOrder() 
    {

        cout << "Pizza Name :: " << displayPizzaName() << "\n";
        cout << "Pizza Size :: " << getPizzaSize() << "\n";
        displayPizzaOrder();
        cout<< "Total Order Value :: "<<calculateOrderPrice()<<"\n";
    }

    double calculateOrderPrice(){
        double amount = 0;
        amount += _basePrice;
        amount += calculatePrice();
        return amount;

    }

    virtual double calculatePrice() = 0;
    virtual void displayPizzaOrder() = 0;
    virtual void addTopping(const vector<Toppings> &toppings = {}) = 0;

    virtual ~Pizza() = default;
};


class MargheritaPizza : public Pizza
{
protected:
    vector<Toppings> _toppings;

public:
    MargheritaPizza(PizzaName name, PizzaSize size) : Pizza(name, size)
    {

        addTopping(_toppings);
    }

    void addTopping(const vector<Toppings> &toppings = {}) override
    {
        if (toppings.empty())
        {
            _toppings.push_back(Toppings::CHEESE);
        }
        else
        {
            for (auto &topping : toppings)
            {
                _toppings.push_back(topping);
            }
        }
    }

    double countToppings(const vector<Toppings> &toppings = vector<Toppings>())
    {
        vector<Toppings> toppingsToConsider = toppings.empty() ? _toppings : toppings;
        double amount = 0;
        for (auto &topping : toppingsToConsider)
        {
            amount += Pizza::getToppingsPrize(topping);
        }
        return amount;
    }

    double calculatePrice() override
    {
        double amount = 0;
        amount += countToppings();
        return amount;
    }

    void addToppings(const vector<Toppings> &toppings = {})
    {

        if (toppings.empty())
        {
            cout << Pizza::displayToppings(_toppings[0]) << " ";
        }
        else
        {
            for (auto &topping : toppings)
            {
                cout << Pizza::displayToppings(topping) << " ";
            }
        }
    }


    

    

    void getMargheritaPizzaToppings(const vector<Toppings> &toppings = vector<Toppings>())
    {
        vector<Toppings> toppingsToPrint = toppings.empty() ? _toppings : toppings;

        for (auto &topping : toppingsToPrint)
        {
            cout << Pizza::displayToppings(topping) << " ";
        }
    }

    void displayPizzaOrder() override
    {
        

        cout << "Pizza Toppings :: ";
        getMargheritaPizzaToppings();
        cout << "\n";
        
    }
};

class CustomizedMargheritaPizza : public MargheritaPizza
{

private:
    vector<Toppings> _toppings;
    PizzaSize _size;

public:
    CustomizedMargheritaPizza(PizzaName name, PizzaSize size) : MargheritaPizza(name, size)
    {
        _toppings = MargheritaPizza::_toppings;
        _size = size;
    }

    void addTopping(const vector<Toppings> &topping) override
    {
        for (auto &t : topping)
        {
            _toppings.push_back(t);
        }
    }

    double calculatePrice() override
    {
        double amount = MargheritaPizza::calculatePrice();

        if (_toppings.size() > 1)
        {
            vector<Toppings> customizedToppings(_toppings.begin() + 1, _toppings.end());
            amount += MargheritaPizza::countToppings(customizedToppings);
        }
        return amount;
    }

    void displayPizzaOrder() override
    {
        cout << "Pizza Toppings :: ";
        MargheritaPizza::getMargheritaPizzaToppings(_toppings);
        cout << "\n";
        
    }
};


class PaneerPizza : public Pizza
{
protected:
    vector<Toppings> _toppings;

public:
    PaneerPizza(PizzaName name, PizzaSize size) : Pizza(name,size)
    {

        addTopping(_toppings);
    }

    void addTopping(const vector<Toppings> &toppings = {}) override
    {
        if (toppings.empty())
        {
            _toppings.push_back(Toppings::PANEER);
            _toppings.push_back(Toppings::ONION);
        }
        else
        {
            for (auto &topping : toppings)
            {
                _toppings.push_back(topping);
            }
        }
    }

    double countToppings(const vector<Toppings> &toppings = {})
    {
        vector<Toppings> toppingsToConsider = toppings.empty() ? _toppings : toppings;
        double amount = 0;
        for (auto &topping : toppingsToConsider)
        {
            amount += Pizza::getToppingsPrize(topping);
        }
        return amount;
    }

    double calculatePrice() override
    {
        double amount = 0;
        

        amount += countToppings();
        return amount;
    }

    

    

    void getPaneerPizzaToppings(const vector<Toppings> &toppings = {})
    {

        if (toppings.empty())
        {
            for (int i = 0; i < 2; i++)
            {
                cout << Pizza::displayToppings(_toppings[i]) << " ";
            }
        }
        else
        {
            for (auto &topping : toppings)
            {
                cout << Pizza::displayToppings(topping) << " ";
            }
        }
    }


    void displayPizzaOrder() override
    {
        
        cout << "Pizza Toppings :: ";
        getPaneerPizzaToppings();
        cout << "\n";
        
    }
};

class CustomizedPaneerPizza : public PaneerPizza
{
private:
    vector<Toppings> _toppings;
    PizzaSize _size;

public:
    CustomizedPaneerPizza(PizzaName name, PizzaSize size) : PaneerPizza(name, size)
    {
        _toppings = PaneerPizza::_toppings;
        _size = size;
    }

    void addTopping(const vector<Toppings> &topping) override
    {
        for (auto &t : topping)
        {
            _toppings.push_back(t);
        }
    }

    double calculatePrice() override
    {
        double amount = PaneerPizza::calculatePrice();

        if (_toppings.size() > 2)
        {
            vector<Toppings> customizedToppings(_toppings.begin() + 2, _toppings.end());
            amount += PaneerPizza::countToppings(customizedToppings);
        }
        return amount;
    }

    void displayPizzaOrder() override
    {
        
        cout << "Pizza Toppings :: ";
        PaneerPizza::getPaneerPizzaToppings(_toppings);
        cout << "\n";
        
    }
};


class ChickenPizza : public Pizza
{

protected:
    vector<Toppings> _toppings;

public:
    ChickenPizza(PizzaName name, PizzaSize size) : Pizza( name, size)
    {
        addTopping();
    }

    void addTopping(const vector<Toppings> &toppings = {}) override
    {
        if (toppings.empty())
        {
            _toppings.push_back(Toppings::CHICKEN);
            _toppings.push_back(Toppings::GREEN_PEPPERS);
        }
        else
        {
            for (auto &topping : toppings)
            {
                _toppings.push_back(topping);
            }
        }
    }

    double countToppings(const vector<Toppings> &toppings = vector<Toppings>())
    {
        vector<Toppings> toppingsToConsider = toppings.empty() ? _toppings : toppings;
        double amount = 0;
        for (auto &topping : toppingsToConsider)
        {
            amount += Pizza::getToppingsPrize(topping);
        }
        return amount;
    }

    double calculatePrice() override
    {
        double amount = 0;
        

        amount += countToppings();
        return amount;
    }

    

    

    void getChickenPizzaToppings(const vector<Toppings> &toppings = {})
    {

        if (toppings.empty())
        {
            for (int i = 0; i < 2; i++)
            {
                cout << Pizza::displayToppings(_toppings[i]) << " ";
            }
        }
        else
        {
            for (auto &topping : toppings)
            {
                cout << Pizza::displayToppings(topping) << " ";
            }
        }
    }

    void displayPizzaOrder() override
    {

        
        cout << "Pizza Toppings :: ";
        getChickenPizzaToppings();
        cout << "\n";
        
    }
};

class CustomizedChickenPizza : public ChickenPizza
{
private:
    vector<Toppings> _toppings;
    

public:
    CustomizedChickenPizza(PizzaName name, PizzaSize size) : ChickenPizza(name, size)
    {
        _toppings = ChickenPizza::_toppings;
        
    }

    void addTopping(const vector<Toppings> &topping) override
    {
        for (auto &t : topping)
        {
            _toppings.push_back(t);
        }
    }

    double calculatePrice() override
    {
        double amount = ChickenPizza::calculatePrice();

        if (_toppings.size() > 2)
        {
            vector<Toppings> customizedToppings(_toppings.begin() + 2, _toppings.end());
            amount += ChickenPizza::countToppings(customizedToppings);
        }
        return amount;
    }

    void displayPizzaOrder()
    {
        
        cout << "Pizza Toppings :: ";
        ChickenPizza::getChickenPizzaToppings(_toppings);
        cout << "\n";
        
    }
};

int main()
{

    Pizza *pizza1 = new PaneerPizza(PizzaName::Paneer, PizzaSize::MEDIUM);

    
    
    pizza1->displayOrder();

    cout << "\n";


    

    Pizza *pizza2 = new ChickenPizza(PizzaName::Chicken, PizzaSize::LARGE);

    
    pizza2->displayOrder();

    cout << "\n";

    Pizza *pizza3 = new MargheritaPizza(PizzaName::Margherita, PizzaSize::SMALL);

    
    
    pizza3->displayOrder();

    cout << "\n";

    

    




    delete pizza1;
    delete pizza2;
    delete pizza3;
}
