#include <iostream>
#include <string>

using namespace std;
class Customer;
class Pet
{
public:
    string breed;
    int numbers;
    int price;
    Pet() {}
    Pet(string breed, int numbers, int price)
    {
        this->breed = breed;
        this->numbers = numbers;
        this->price = price;
    }
};

class Customer
{
public:
    string name;
    string address;
    int orderCode;
    bool orderStatus;
    int bill;
    Pet pets[5]; // Assuming each customer can have up to 5 pets
    int numPets; // Number of pets owned by the customer

    Customer()
    {
        numPets = 0;
    }

    Customer(string name, string address, int orderCode, bool orderStatus)
    {
        this->name = name;
        this->address = address;
        this->orderCode = orderCode;
        this->orderStatus = orderStatus;
        bill=0;
        numPets = 0;
        cout << "You can add at most 5 breeds of pet\n";
        int a=1,price=0;
        cout << "Please Add pets.\n";
add:
        if(a==1)
        {
            string breed;
            int numbers;
            cout << "Enter pet breed: ";
            cin >> breed;
            cout << "Enter the number of pets: ";
            cin >> numbers;
            cout << "Enter the price per pet: ";
            cin >> price;
            // Create a pet object and add it to the customer
            Pet pet(breed, numbers, price);
            if(addPet(pet)) bill+=numbers*price;
            cout << "(1) Add pets\n(2) Done\nChoice: ";
            cin >> a;
            goto add;
        }
    }

    bool addPet(Pet pet)
    {
        if (numPets < 5)
        {
            // Assuming each customer can have up to 5 pets
            pets[numPets++] = pet;
            return 1;
        }
        else
        {
            cout << "Cannot add more pets. Maximum limit reached." << endl;
            return 0;
        }
    }

    int calculatePetRevenueByBreed(string breed)
    {
        int revenue = 0;
        for (int i = 0; i < numPets; i++)
        {
            if (pets[i].breed == breed)
            {
                revenue += pets[i].price * pets[i].numbers;
            }
        }
        return revenue;
    }
    friend void displayCustomer(const Customer& customer);
};
void displayCustomer(const Customer& customer)
{
    cout << "Name: " << customer.name << endl;
    cout << "Address: " << customer.address << endl;
    cout << "Order Code: " << customer.orderCode << endl;
    cout << "Order Status: " << customer.orderStatus << endl;
    cout << "Bill: " << customer.bill << endl;
}


class CustomerManagement
{

    Customer customerRecord[10];
    int no_of_customers;
public:
    CustomerManagement()
    {
        no_of_customers = 0;
    }

    void addCustomer(Customer customer)
    {
        if(no_of_customers>=10)
            cout << "The maximum number of Customer exceeds!!" << endl;
        customerRecord[no_of_customers++] = customer;
    }

    Customer getCustomerByCode(int orderCode)
    {
        for (int i = 0; i < no_of_customers; i++)
        {
            if (customerRecord[i].orderCode == orderCode)
            {
                return customerRecord[i];
            }
        }
        return Customer();
    }

    int getRevenue()
    {
        int revenue = 0;
        for (int i = 0; i < no_of_customers; i++)
        {
            if (customerRecord[i].orderStatus == true)
            {
                revenue += customerRecord[i].bill;
            }
        }
        return revenue;
    }

    void printCustomers()
    {
        if(no_of_customers==0)
        {
            cout << "There is no customer in our record.\n";
            return;
        }
        for (int i = 0; i < no_of_customers; i++)
        {
            cout << "Customer " << i + 1 << ":\nName: " << customerRecord[i].name << endl;
            cout << "Address: " <<customerRecord[i].address << endl;
            cout << "Order Code: "<<customerRecord[i].orderCode << endl;
            cout << "Order Status: " << customerRecord[i].orderStatus << endl;
            cout << "Bill: " << customerRecord[i].bill << endl;
        }
    }

    int getRevenueByPet(string breed)
    {
        int revenue = 0;
        for (int i = 0; i < no_of_customers; i++)
        {
            revenue += customerRecord[i].calculatePetRevenueByBreed(breed);
        }
        return revenue;
    }
    ~CustomerManagement()
    {
        cout << "Thanks for Using.\nHave a Nice Day!!\n";
    }
};

int main()
{

    CustomerManagement customerManagement;
    system("cls");
    while (true)
    {
        cout << "Menu:" << endl;
        cout << "1. Add Customer" << endl;
        cout << "2. Find Customer" << endl;
        cout << "3. Print Customers" << endl;
        cout << "4. Get Revenue by Pet" << endl;
        cout << "5. Total Revenue" << endl;
        cout << "6. Exit" << endl;

        int choice;
        cout << "Enter your choice: ";
        cin >> choice;
        system("cls");

        if (choice == 1)
        {
            // Get user input for customer data
            string name;
            string orders;
            string address;
            int orderCode;
            bool orderStatus;
            int bill;

            cout << "Enter customer name: ";
            cin >> name;
            cout << "Enter customer address: ";
            cin >> address;
            cout << "Enter customer order code: ";
            cin >> orderCode;
            cout << "Enter customer order status (true/false): ";
            cin >> orderStatus;
            if(orderStatus==0)
            {
                system("pause");
                system("cls");
                continue;
            }

            // Create a customer object and add it to the customer record
            Customer customer(name, address, orderCode, orderStatus);
            customerManagement.addCustomer(customer);
        }
        else if (choice == 2)
        {
            cout << "Enter Order Code: ";
            int orderCode;
            cin >> orderCode;
            Customer customerRecord = customerManagement.getCustomerByCode(orderCode);
            displayCustomer(customerRecord);

        }
        else if (choice == 3)
        {
            // Print the list of customers
            customerManagement.printCustomers();
        }
        else if (choice == 4)
        {
            // Get revenue by pet
            string breed;
            cout << "Enter pet breed: ";
            cin >> breed;
            int revenue = customerManagement.getRevenueByPet(breed);
            cout << "Revenue for " << breed << " is " << revenue << endl;
        }
        else if(choice==5)
        {
            cout << "Total Revenue is " << customerManagement.getRevenue() << "TK\n";
        }
        else if (choice == 6)
        {
            // Exit the program
            break;
        }
        else
        {
            cout << "Invalid choice. Please try again." << endl;
        }
        system("pause");
        system("cls");
    }
    return 0;
}

