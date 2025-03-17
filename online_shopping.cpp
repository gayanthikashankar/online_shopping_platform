#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <stack>
#include <queue>
#include <limits> 

//fw declarations
class User;
class ShoppingCart;

//base class
class Product {
protected:
    std::string name;
    double price;
    static int totalProducts; 

public:
    //constructor
    Product(std::string n, double p) {
        this->name = n;
        this->price = p;
        totalProducts++;
    }
    
    //virt destructor
    virtual ~Product() {
        totalProducts--;
    }
    
    std::string getName() const { return name; }
    double getPrice() const { return price; }
    void setPrice(double p) { price = p; }
    
    static int getTotalProducts() { return totalProducts; }
    
    virtual void displayDetails() const = 0;
    
    //price comparison
    bool operator>(const Product& other) const {
        return price > other.price;
    }
    
    bool operator<(const Product& other) const {
        return price < other.price;
    }
    
    friend void applyDiscount(Product& product, double percentage);
};

int Product::totalProducts = 0;

void applyDiscount(Product& product, double percentage) {
    product.price -= (product.price * percentage / 100);
}

//derived class
class Electronics : public Product {
private:
    std::string brand;
    int warrantyMonths;
    
public:
    Electronics(std::string n, double p, std::string b, int w)
        : Product(n, p) {
        this->brand = b;
        this->warrantyMonths = w;
    }
    
    void displayDetails() const /* override */ {
        std::cout << "Electronics: " << name << ", Brand: " << brand
                  << ", Price: $" << price << ", Warranty: " << warrantyMonths << " months" << std::endl;
    }
};

class Clothing : public Product {
private:
    std::string size;
    std::string material;
    
public:
    Clothing(std::string n, double p, std::string s, std::string m)
        : Product(n, p) {
        this->size = s;
        this->material = m;
    }
    
    void displayDetails() const {
        std::cout << "Clothing: " << name << ", Size: " << size
                  << ", Material: " << material << ", Price: $" << price << std::endl;
    }
};

class Book : public Product {
private:
    std::string author;
    int pages;
    
public:
    Book(std::string n, double p, std::string a, int pg)
        : Product(n, p) {
        this->author = a;
        this->pages = pg;
    }
    
    void displayDetails() const {
        std::cout << "Book: " << name << ", Author: " << author
                  << ", Pages: " << pages << ", Price: $" << price << std::endl;
    }
};


class ShoppingCart {
private:
    //smart pointers for products 
    std::vector<std::shared_ptr<Product> > items; 
    
public:
    ShoppingCart() {} //constructor
    void addProduct(std::shared_ptr<Product> product) {
        items.push_back(product);
        std::cout << "Added to cart: ";
        product->displayDetails();
    }
    
    void removeProduct(int index) {
        if (index >= 0 && index < items.size()) {
            std::cout << "Removed from cart: ";
            items[index]->displayDetails();
            items.erase(items.begin() + index);
        } else {
            std::cout << "Invalid item index!" << std::endl;
        }
    }
    
    void displayCart() const {
        if (items.empty()) {
            std::cout << "The cart is empty" << std::endl;
            return;
        }
        
        std::cout << "\n-----Shopping Cart Contents-----" << std::endl;
        double total = 0.0;
        for (size_t i = 0; i < items.size(); i++) {
            std::cout << i+1 << ". ";
            items[i]->displayDetails();
            total += items[i]->getPrice();
        }
        std::cout << "--------------------------------" << std::endl;
        std::cout << "Total: $" << total << std::endl;
        std::cout << "--------------------------------" << std::endl;
    }
    
    double calculateTotal() const {
        double total = 0.0;
        for (size_t i = 0; i < items.size(); i++) {
            total += items[i]->getPrice();
        }
        return total;
    }
    
    size_t getItemCount() const {
        return items.size();
    }
    
    void clearCart() {
        items.clear();
    }
    
    friend class User;
};

class User {
private:
    std::string username;
    ShoppingCart cart;
    std::stack<std::shared_ptr<Product> > orderHistory; 
    
public:
    User(std::string name) {
        this->username = name;
    }
    
    std::string getUsername() const { return username; }
    
    //access to user's cart
    ShoppingCart& getCart() { return cart; }
    
    //adds current cart items to order history stack (While placing order)
    bool placeOrder() {
        if (cart.items.empty()) {
            std::cout << "CYour cart is empty, we cannot place the order " << std::endl;
            return false;
        }
        
        std::cout << "\n----------- Order Confirmation -----------" << std::endl;
        std::cout << "Customer: " << username << std::endl;
        cart.displayCart();
        std::cout << "Total amount: $" << cart.calculateTotal() << std::endl;
        
        char confirm;
        std::cout << "Confirm order? (y/n): ";
        std::cin >> confirm;
        
        if (confirm != 'y' && confirm != 'Y') {
            std::cout << "Order cancelled" << std::endl;
            return false;
        }
        
        //additems to order history
        for (size_t i = 0; i < cart.items.size(); i++) {
            orderHistory.push(cart.items[i]);
        }
        
        std::cout << "Your order has been  placed successfully" << std::endl;
        
        cart.clearCart();
        return true;
    }
    
    void displayOrderHistory() const {
        if (orderHistory.empty()) {
            std::cout << "No order history available" << std::endl;
            return;
        }
        
        std::cout << "\n----------- Order History -----------" << std::endl;
        std::cout << "Last ordered item: ";
        orderHistory.top()->displayDetails();
        std::cout << "Total items ordered: " << orderHistory.size() << std::endl;
    }
};

class OrderProcessor {
private:
    std::queue<User*> orderQueue; //processing order
public:
    //add order to processing queue
    void addOrder(User* user) {
        orderQueue.push(user);
        std::cout << "Order from " << user->getUsername() << " added to processing queue" << std::endl;
    }
    
    void processNextOrder() {
        if (orderQueue.empty()) {
            std::cout << "No orders to process" << std::endl;
            return;
        }
        
        User* user = orderQueue.front();
        orderQueue.pop();
        
        std::cout << "Processing order for user: " << user->getUsername() << std::endl;
        std::cout << "- Checking inventory..." << std::endl;
        std::cout << "- Verifying payment..." << std::endl;
        std::cout << "- Preparing shipment..." << std::endl;
        std::cout << "Your order has been  placed successfully" << std::endl;
    }
    
    int getPendingOrderCount() const {
        return orderQueue.size();
    }
};

//clear input buffer
void clearInputBuffer() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void displayMainMenu() {
    std::cout << "\n-------- Online shopping SystemM--------" << std::endl;
    std::cout << "1) Browse Products" << std::endl;
    std::cout << "2) View Cart" << std::endl;
    std::cout << "3) Remove Item from Cart" << std::endl;
    std::cout << "4) Checkout" << std::endl;
    std::cout << "5) View Order History" << std::endl;
    std::cout << "6) Exit" << std::endl;
    std::cout << "----------------------------------------" << std::endl;
    std::cout << "Enter your choice: ";
}

void displayProductCatalog(const std::vector<std::shared_ptr<Product> >& inventory) {
    std::cout << "\n-------- Products Available: --------" << std::endl;
    for (size_t i = 0; i < inventory.size(); i++) {
        std::cout << i+1 << ". ";
        inventory[i]->displayDetails();
    }
    std::cout << inventory.size()+1 << ". Back to Main Menu" << std::endl;
    std::cout << "----------------------------------------" << std::endl;
    std::cout << "Select a product to add to cart (1-" << inventory.size() << ") or " 
              << inventory.size()+1 << " to return: ";
}

int main() {
    //create inventory with smart pointers
    std::vector<std::shared_ptr<Product> > inventory;
    
    //create shared pointers with new instead of make_shared
    inventory.push_back(std::shared_ptr<Electronics>(new Electronics("Laptop", 999.99, "TechBrand", 24)));
    inventory.push_back(std::shared_ptr<Electronics>(new Electronics("Smartphone", 699.99, "PhoneCo", 12)));
    inventory.push_back(std::shared_ptr<Electronics>(new Electronics("Headphones", 149.99, "AudioTech", 6)));
    inventory.push_back(std::shared_ptr<Clothing>(new Clothing("T-Shirt", 19.99, "M", "Cotton")));
    inventory.push_back(std::shared_ptr<Clothing>(new Clothing("Jeans", 49.99, "32", "Denim")));
    inventory.push_back(std::shared_ptr<Clothing>(new Clothing("Hoodie", 39.99, "L", "Fleece")));
    inventory.push_back(std::shared_ptr<Book>(new Book("Programming C++", 39.99, "Albert E. ", 450)));
    inventory.push_back(std::shared_ptr<Book>(new Book("Data Structures and Algorithms", 29.99, "Martha Williams", 380)));
    
    OrderProcessor processor;
    
    std::string userName;
    std::cout << "Welcome to the Online Shopping System" << std::endl;
    std::cout << "Please enter your name: ";
    std::getline(std::cin, userName);
    
    User user(userName);
    std::cout << "Hello, " << user.getUsername() << ", let's start shopping." << std::endl;
    
    bool exitProgram = false;
    int choice;
    
    while (!exitProgram) {
        displayMainMenu();
        
        if (!(std::cin >> choice)) {
            std::cout << "Invalid input. Please enter a number." << std::endl;
            clearInputBuffer();
            continue;
        }
        
        switch (choice) {
            case 1: { 
                int productChoice;
                do {
                    displayProductCatalog(inventory);
                    
                    if (!(std::cin >> productChoice)) {
                        std::cout << "Invalid input, please enter a number." << std::endl;
                        clearInputBuffer();
                        continue;
                    }
                    
                    if (productChoice >= 1 && productChoice <= static_cast<int>(inventory.size())) {
                        user.getCart().addProduct(inventory[productChoice-1]);
                    } else if (productChoice != inventory.size()+1) {
                        std::cout << "Invalid product number, please try again." << std::endl;
                    }
                } while (productChoice != inventory.size()+1);
                break;
            }
            
            case 2: 
                user.getCart().displayCart();
                break;
                
            case 3: { 
                if (user.getCart().getItemCount() == 0) {
                    std::cout << "Your cart is empty" << std::endl;
                    break;
                }
                
                user.getCart().displayCart();
                std::cout << "Enter the item number to remove (0 to cancel): ";
                int itemToRemove;
                
                if (!(std::cin >> itemToRemove)) {
                    std::cout << "Invalid input, please enter a number." << std::endl;
                    clearInputBuffer();
                    break;
                }
                
                if (itemToRemove == 0) {
                    std::cout << "Operation cancelled" << std::endl;
                } else if (itemToRemove >= 1 && itemToRemove <= static_cast<int>(user.getCart().getItemCount())) {
                    user.getCart().removeProduct(itemToRemove-1);
                } else {
                    std::cout << "Invalid item number" << std::endl;
                }
                break;
            }
            
            case 4: 
                if (user.placeOrder()) {
                    processor.addOrder(&user);
                    processor.processNextOrder();
                }
                break;
                
            case 5: 
                user.displayOrderHistory();
                break;
                
            case 6: //exit
                std::cout << "Thank you for shopping with us, " << user.getUsername() << "!" << std::endl;
                exitProgram = true;
                break;
                
            default:
                std::cout << "Invalid choice., please try again" << std::endl;
        }
        
        if (!exitProgram) {
            std::cout << "\n****Press Enter to continue****";
            clearInputBuffer();
            std::cin.get();
        }
    }
    
    std::cout << "\nProgram terminated" << std::endl;
}