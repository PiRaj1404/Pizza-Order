#include <iostream>
#include <vector>

using namespace std;

enum class PizzaSize
{
    SMALL,
    MEDIUM,
    LARGE
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
protected:
    PizzaSize _size;
    double _basePrice;
    string _pizzaSize;

public:
    Pizza(PizzaSize size) : _size(size)
    {

        setPizzaSize();
        setPizzaPrice();
    };

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
            break;

        case PizzaSize::MEDIUM:
            _pizzaSize = "Medium";
            break;

        case PizzaSize::LARGE:
            _pizzaSize = "Large";
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

    virtual double calculatePrice() = 0;
    virtual void displayPizza() = 0;
    virtual void addTopping(const vector<Toppings> &toppings = {}) = 0;

    virtual ~Pizza() = default;
};


class MargheritaPizza : public Pizza
{
protected:
    vector<Toppings> _toppings;

public:
    MargheritaPizza(PizzaSize size) : Pizza(size)
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
        amount += _basePrice;

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


    string getMargheritaPizzaName()
    {
        return "Margherita Pizza";
    }

    string getMargheritaPizzaSize()
    {
        return _pizzaSize;
    }

    void getMargheritaPizzaToppings(const vector<Toppings> &toppings = vector<Toppings>())
    {
        vector<Toppings> toppingsToPrint = toppings.empty() ? _toppings : toppings;

        for (auto &topping : toppingsToPrint)
        {
            cout << Pizza::displayToppings(topping) << " ";
        }
    }

    void displayPizza() override
    {
        cout << "Pizza Name :: " << getMargheritaPizzaName() << "\n";
        cout << "Pizza Size :: " << getMargheritaPizzaSize() << "\n";
        cout << "Pizza Toppings :: ";
        getMargheritaPizzaToppings();
        cout << "\n";
        cout << "Total amount :: " << calculatePrice();
    }
};

class CustomizedMargheritaPizza : public MargheritaPizza
{

private:
    vector<Toppings> _toppings;
    PizzaSize _size;

public:
    CustomizedMargheritaPizza(PizzaSize size) : MargheritaPizza(size)
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

    void displayPizza()
    {
        cout << "Pizza Name :: Customized " << MargheritaPizza::getMargheritaPizzaName() << "\n";
        cout << "Pizza Size :: " << _pizzaSize << "\n";
        cout << "Pizza Toppings :: ";
        MargheritaPizza::getMargheritaPizzaToppings(_toppings);
        cout << "\n";
        cout << "Total amount :: " << calculatePrice() << "\n";
    }
};


class PaneerPizza : public Pizza
{
protected:
    vector<Toppings> _toppings;

public:
    PaneerPizza(PizzaSize size) : Pizza(size)
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
        amount += _basePrice;

        amount += countToppings();
        return amount;
    }

    string getPaneerPizzaName()
    {
        return "Paneer Pizza";
    }

    string getPaneerPizzaSize()
    {
        return _pizzaSize;
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


    void displayPizza() override
    {
        cout << "Pizza Name :: " << getPaneerPizzaName() << "\n";
        cout << "Pizza Size :: " << getPaneerPizzaSize() << "\n";
        cout << "Pizza Toppings :: ";
        getPaneerPizzaToppings();
        cout << "\n";
        cout << "Total amount :: " << calculatePrice() << "\n";
    }
};

class CustomizedPaneerPizza : public PaneerPizza
{
private:
    vector<Toppings> _toppings;
    PizzaSize _size;

public:
    CustomizedPaneerPizza(PizzaSize size) : PaneerPizza(size)
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

    void displayPizza()
    {
        cout << "Pizza Name :: Customized " << PaneerPizza::getPaneerPizzaName() << "\n";
        cout << "Pizza Size :: " << _pizzaSize << "\n";
        cout << "Pizza Toppings :: ";
        PaneerPizza::getPaneerPizzaToppings(_toppings);
        cout << "\n";
        cout << "Total amount :: " << calculatePrice() << "\n";
    }
};


class ChickenPizza : public Pizza
{
private:
    string _name;

protected:
    vector<Toppings> _toppings;

public:
    ChickenPizza(PizzaSize size) : Pizza(size)
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
        amount += _basePrice;

        amount += countToppings();
        return amount;
    }

    string getChickenPizzaName()
    {
        return "Chicken Pizza";
    }

    string getChickenPizzaSize()
    {
        return _pizzaSize;
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

    void displayPizza() override
    {

        cout << "Pizza Name :: " << getChickenPizzaName() << "\n";
        cout << "Pizza Size :: " << getChickenPizzaSize() << "\n";
        cout << "Pizza Toppings :: ";
        getChickenPizzaToppings();
        cout << "\n";
        cout << "Total amount :: " << calculatePrice() << "\n";
    }
};

class CustomizedChickenPizza : public ChickenPizza
{
private:
    vector<Toppings> _toppings;
    PizzaSize _size;

public:
    CustomizedChickenPizza(PizzaSize size) : ChickenPizza(size)
    {
        _toppings = ChickenPizza::_toppings;
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
        double amount = ChickenPizza::calculatePrice();

        if (_toppings.size() > 2)
        {
            vector<Toppings> customizedToppings(_toppings.begin() + 2, _toppings.end());
            amount += ChickenPizza::countToppings(customizedToppings);
        }
        return amount;
    }

    void displayPizza()
    {
        cout << "Pizza Name :: Customized " << ChickenPizza::getChickenPizzaName() << "\n";
        cout << "Pizza Size :: " << _pizzaSize << "\n";
        cout << "Pizza Toppings :: ";
        ChickenPizza::getChickenPizzaToppings(_toppings);
        cout << "\n";
        cout << "Total amount :: " << calculatePrice() << "\n";
    }
};

int main()
{

    Pizza *pizza1 = new CustomizedPaneerPizza(PizzaSize::MEDIUM);

    
    pizza1->addTopping({Toppings::BLACK_OLIVES, Toppings::TOMATO});
    pizza1->displayPizza();

    cout << "\n";

    Pizza *pizza2 = new CustomizedChickenPizza(PizzaSize::MEDIUM);

    
    pizza2->addTopping({Toppings::ONION, Toppings::CHEESE});
    pizza2->displayPizza();

    cout << "\n";

    Pizza *pizza3 = new CustomizedMargheritaPizza(PizzaSize::LARGE);
    
    pizza3->addTopping({Toppings::ONION, Toppings::TOMATO});
    pizza3->displayPizza();

    cout << "\n";

    Pizza *pizza4 = new MargheritaPizza(PizzaSize::LARGE);
    pizza3->calculatePrice();
    pizza3->addTopping();
    pizza3->displayPizza();




    delete pizza1;
    delete pizza2;
    delete pizza3;
    delete pizza4;
}
