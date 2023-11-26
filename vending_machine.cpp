#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Payment
{
public:
    virtual void Pay() = 0;
};

class Cash : public Payment
{
public:
    Cash(){}
    void Pay()
    {
        cout << "Cash Payment" << endl;
    }
};

class Card : public Payment
{
public:
    Card(){}
    void Pay()
    {
        cout << "Card Payment" << endl;
    }
};

class Product
{
private:
    string name;
    int price;

public:
    Product(string n, int p){
        name = n;
        price = p;
    }
    string GetName()
    {
        return name;
    }
    int GetPrice()
    {
        return price;
    }
};

class User
{
private:
    vector<Product*> inventory;
    string name;
    float money;
    Payment* paymentMethod;
public:
    User(string n, float m, Payment* pm){
        name = n;
        money = m;
        paymentMethod = pm;
    }
    void ShowInventory()
    {
        cout << name << " Inventory: " << endl;
        for (int i = 0; i < inventory.size(); i++)
        {
            cout << inventory[i]->GetName() << " $" << inventory[i]->GetPrice() << endl;
        }
    }
    string GetName()
    {
        return name;
    }
    float GetMoney()
    {
        return money;
    }
    void SetMoney(float money)
    {
        this->money = money;
    }
    vector<Product*> &GetInventory()
    {
        return inventory;
    }
    void SetInventory(vector<Product*> inventory)
    {
        this->inventory = inventory;
    }
    Payment* GetPaymentMethod()
    {
        return paymentMethod;
    }
};

class VendingMachine
{
private:
    vector<Product*> products;
public:
    void GetProducts()
    {
        cout << "Products that are available: " << endl;
        cout << endl;
        for(int i = 0; i < products.size(); i++)
        {
            cout << "[" << i << "]" << products[i]->GetName() << " " << products[i]->GetPrice() << "$" << endl;
        }
    }
    void AddProduct(Product* product)
    {
        products.push_back(product);
    }
    void BuyProduct(int index, User* user)
    {
        if(user->GetMoney() >= products[index]->GetPrice())
        {
            user->SetMoney(user->GetMoney() - products[index]->GetPrice());
            user->GetInventory().push_back(products[index]);
            cout << "You bought " << products[index]->GetName() << endl;
        }
        else
        {
            cout << "You don't have enough money to buy this product." << endl;
        }
    }
};

int main()
{
    cout << "Pat Vending Machine" << endl;
    cout << endl;

    VendingMachine V;
    
    V.AddProduct(new Product("Coca Cola", 15));
    V.AddProduct(new Product("Pepsi", 20));
    V.AddProduct(new Product("Kiwi Juice", 50));
    V.AddProduct(new Product("Github Pro Code", 80));
    
    Cash* cashPayment = new Cash();
    User* U1 = new User("Pat", 100, cashPayment);
    
    V.GetProducts();
    cout << endl;
    
    V.BuyProduct(0, U1);
    V.BuyProduct(2, U1);
    cout << endl;
    
    cout << "Payment: ";
    U1->GetPaymentMethod()->Pay();
    
    cout << endl;
    U1->ShowInventory();
    
    return 0;
}