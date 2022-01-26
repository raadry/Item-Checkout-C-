//Raad Khan
//Assignment 6

#include <iostream>

using namespace std;

//Currency class provided in Course Documents
class Currency
{
private:
	double amount;

public:
	//constructors
	Currency() : amount(0)
	{}
	Currency(int d, int c)
	{
		amount = d + (c * 0.01);
	}
	Currency(double amt)
	{
		amount = amt;
	}

	//access functions
	int getDollars()
	{
		return static_cast<int>(amount);
	}

	int getCents()
	{
		return static_cast<int>((amount - getDollars()) * 100);
	}

	Currency Add(Currency c);

	//Overriden == operator
	bool  operator ==(Currency c)
	{
		return (amount == c.amount);
	}
	//Overriden > operator
	bool operator > (Currency c)
	{
		return amount > c.amount;
	}

	//Overriden < operator
	bool operator < (Currency c)
	{
		return amount < c.amount;
	}
	//mutator/modifier functions
	void setDollars(int d)
	{
		amount = d + (getCents() * 0.01);
	}

	void setCents(int c)
	{
		amount = getDollars() + (c * 0.01);
	}

	void AddTo(Currency c);

	//Overriden << operator
	friend ostream& operator << (ostream& output, const Currency& C)
	{
		output << C.amount;
		return output;
	}

	//Overriden >> operator
	friend istream& operator >> (istream& input, Currency& C)
	{
		input >> C.amount;
		return input;
	}

	//Overridden prefix and postfix operators
	Currency operator++()
	{
		Currency result;
		int temp;
		double temp2;
		

		temp2 = amount;
		temp = static_cast<int>(amount);
		amount = temp + 1;
		
		return Currency(amount);
	}
	Currency operator++(int)
	{
		Currency result;
		int temp;
		double temp2;

		temp2 = amount;
		temp = static_cast<int>(amount);
		amount = temp +1;
		return Currency(temp2);
	}

	//input and output functions
	void Read();
	void Write();
	Currency Multiply(Currency amt);
};

Currency Currency::Add(Currency c)
{
	Currency result;

	result.amount = amount + c.amount;

	return result;
}

void Currency::AddTo(Currency c)
{
	amount += c.amount;
}

void Currency::Read()
{
	cin >> amount;
}

void Currency::Write()
{
	cout << amount;
}

//function that multiplies two objects of Currency class
Currency Currency::Multiply(Currency amt)
{

	Currency result;

	result.amount = amount * amt.amount;

	return result;

}



//Create InventoryItem class
class InventoryItem {

private:
	string Name;	//Name of item
	int ItemNumber, Quantity;	//Item Number and Quantity of items
	Currency UnitPrice;	//Unit price of each item
	Currency TotalValue;	//Total price of transaction of item
	Currency FinalPrice; //Total sum of all the transactions




public:
	//Default Constructor
	InventoryItem() : Name(), ItemNumber(0), Quantity(0), UnitPrice(0)
	{}

	InventoryItem(string n, int iNum, Currency up, int q)
	{

		Name = n;
		ItemNumber = iNum;
		UnitPrice = up;
		Quantity = q;


	}

	//Access Functions
	string getName()
	{
		return Name;
	}

	double getItemNum()
	{
		return ItemNumber;
	}

	Currency getUnitPrice()
	{
		return UnitPrice;
	}
	int getQuantity()
	{
		return Quantity;
	}

	Currency getTotalValue() {


		TotalValue = UnitPrice.Multiply(Quantity);
		return TotalValue;
	}

	Currency getTotalValueCount()
	{
		FinalPrice = FinalPrice.Add(TotalValue);
		return FinalPrice;
	}


	//Modifier Functions
	void setName(string n)
	{
		Name = n;
	}

	void setItemNum(int n)
	{
		ItemNumber = n;
	}

	void setUnitPrice(Currency u)
	{
		UnitPrice = u;
	}

	void setQuantity(int q)
	{
		Quantity = q;
	}

	//Extracts items for array
	void GetItem(InventoryItem list[], int& count)
	{
		double value;
		int ValCount;

		InventoryItem Value;

		ValCount = 0;

		cout << "Please enter number of items: ";
		cin >> count;

		//Keeps repeating until maximum number of items input
		for (int ValCount = 0; ValCount < count; ValCount++)
		{
			cout << "\nEnter values for Item Number " << ValCount + 1;
		
			list[ValCount].Read(); 
		}

	}

	//Sorts ascending or descending
	void Sort(InventoryItem list[], int count, char order)
	{
		//selecting descending
		if (order == 'd' || order == 'D')
		{
			for (int i = count - 1; i > 0; i--)
				for (int j = 0; j < i; j++)
					if (list[j].getTotalValue() < list[j + 1].getTotalValue())

						swap(list[j], list[j + 1]);
		}

		//selecting ascending
		else
		{
			order = 'A';
			for (int i = count - 1; i > 0; i--)
				for (int j = 0; j < i; j++)
					if (list[j].getTotalValue() > list[j + 1].getTotalValue())

						swap(list[j], list[j + 1]);
		}
	}

	//Input and output functions
	void Read();
	void Write();

};

//Inputs values for item
void InventoryItem::Read()
{
	
	cout << "\nEnter product name: ";
	cin >> Name;
	cout << "\nThe item number: ";
	cin >> ItemNumber;
	cout << "\nUnit price: ";
	UnitPrice.Read();

	cout << "\nQuantity in hand: ";
	cin >> Quantity;


}

//Prints values for item
void InventoryItem::Write()
{
	cout << "\nProduct: " << Name;
	cout << "\tItem number: " << ItemNumber;
	cout << "\tQuantity: " << Quantity << endl;
	cout << "\tUnit price: ";
	UnitPrice.Write();

	cout << "\tTotal price: ";
	getTotalValue();

	TotalValue.Write();

	cout << "\n";

}


int main()
{
	InventoryItem item1;	//all data is manipulated using item1
	InventoryItem mylist[100];	
	char ADorder;	//selecting ascending or descending
	int ItemCount;	//count of total items

	//extracts values for the array
	item1.GetItem(mylist, ItemCount);

	//prompts user for ascending or descending
	cout << "Type 'A' to sort in ascending order or 'D' for descending order: ";
	cin >> ADorder;
	//runs until valid input is put in
	while (ADorder!= 'A' && ADorder != 'a' && ADorder != 'd' && ADorder != 'D')
	{
		cout << "Invalid value. Please enter 'A' or 'D'" << endl;
		cin >> ADorder;
	}

	//sorts the array
	item1.Sort(mylist, ItemCount, ADorder);
	
	//displays values
	for (int ValCount = 0; ValCount < ItemCount; ValCount++)
	{
		mylist[ValCount].Write();
	}


	

}
