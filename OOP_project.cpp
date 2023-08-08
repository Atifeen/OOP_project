#include<iostream>
#include<string>

using namespace std;


class Customer 
{
	string name;
	string phone;
	
	public:
	
	void setCustomer (string name, string phone)
	{
		this -> name = name;
		this -> phone = phone;
	}
	
	string getName()
	{
		return name;
	}
	
	string getPhone()
	{
		return phone;
	}
	
};


class Seat
{
	int seatNo;
	int hallNo;
	string seatType;
	string hallType;
	bool bookingStatus;
	Customer customer;
	string customerName;
	string customerPhone;
	
	public:
	
	Seat()
	{
		bookingStatus = false;
	}
	
	int getSeatNo()
	{
		return seatNo;
	}
	
	int getHallNo()
	{
		return hallNo;
	}
	
	string getCustomerPhone()
	{
		return customerPhone;
	}
	
	bool getbookingStatus()
	{
		return bookingStatus;
	}
	
	bool assign (Customer c, int hNo, int sNo)
	{
		if (bookingStatus)
		{
			cout << "This seat is not available for booking!"<< endl;
			return false;
		}
		
		else
		{
			customerName = c.getName();
			customerPhone = c.getPhone();
			seatNo = sNo;
			hallNo = hNo;
			hallType = (hallNo > 3)? "2D" : "3D";
			seatType = (seatNo > 30)? "Regular" : "Premium";
			bookingStatus = true;
			cout << "Ticket booking successfull!" << endl;
			return true;
		}
	}
	
	void cancel()
	{
		bookingStatus = false;
		customerPhone = "";
		cout << "Ticket cancellation successful!" << endl;
		cout << "You have been refunded" << endl;
	}
	
	void displaySeatDetails()
	{
		if (bookingStatus)
		{
			cout << "Name: " << customerName << endl;
			cout << "Phone: " << customerPhone << endl;
			cout << "Hall No: " << hallNo << endl;
			cout << "Hall Type: " << hallType << endl;
			cout << "Seat No: " << seatNo << endl;
			cout << "Seat Type: " << seatType << endl;
		}
		
		else
		{
			cout << "This seat is not booked yet!" << endl;
		}
	}
	
};

class Hall 
{
	Seat seat[60];
		
	public:
	
	Seat* getSeat()
	{
		return seat;
	}
	
};

class MovieTheatre
{
	Hall hall[6];
	
	public:
	
	Hall* getHall ()
	{
		return hall;
	}
	
	bool bookTicket(Customer c, int hNo, int sNo)
	{
		return hall[hNo-1].getSeat()[sNo-1].assign(c, hNo, sNo);
	}
	
	void displayAvailableSeats(int hallNo, bool seatType)
	{
		int i = (seatType)? 1 : 31;
		
		for (int count = 1; count <= 30; count++, i++)
		{
			if(hall[hallNo-1].getSeat()[i-1].getbookingStatus())
			{
				cout.width(4);
				cout << "B";
			}
			
			else 
			{
				cout.width(4);
				cout << i;
			}
			
			if (count%6==0)
			{
				cout << endl;
			}
			
			else if(count%3 == 0)
			{
				cout.width(4);
				cout << "";
			}
		}
	}
		
	void displayBookedTicketsDetails()
	{
		Seat seat;
		bool found;
		for (int hallNo = 0; hallNo < 6; hallNo++)
		{
			for (int seatNo = 0; seatNo < 60; seatNo++)
			{
				seat = getHall()[hallNo].getSeat()[seatNo];
				
				if (seat.getbookingStatus())
				{
					found = true;
					seat.displaySeatDetails();
					cout << endl;
				}
			}
		}
		if (!found)
		{
			cout << "No ticket found" << endl << endl;
		}
	}
	
	void displaySeatDetails(int hallNo, int seatNo)
	{
		hall[hallNo-1].getSeat()[seatNo-1].displaySeatDetails();
	}
	
	friend void search(MovieTheatre*, string phone, string );
};


void search(MovieTheatre* obj, string phone, string arg)
{
	Seat* seat;
	bool found = false;
	
	for (int hallNo = 0; hallNo < 6; hallNo++)
	{
		for (int seatNo = 0; seatNo < 60; seatNo++)
		{
			seat = &obj->getHall()[hallNo].getSeat()[seatNo];
			if (seat->getCustomerPhone() == phone)
			{
				found = true;
				if (arg == "display")
					{
						cout << endl;
						seat->displaySeatDetails();
					}
				if (arg == "cancel")
					seat->cancel();
			}
		}
	}
	
	if (!found)
	{
		cout << "No ticket found" << endl << endl;
	}
}



int main()
{
	MovieTheatre ABC;
	
	
	while (true)
	{
		int choice;
		
		cout << "\t";
		cout << "ABC Cineplex" << endl;
		
		cout << "1. Book ticket" << endl;
        cout << "2. View booked tickets informatoon" << endl;
        cout << "3. View specific ticket information" << endl;
        cout << "4. Cancel ticket" << endl;
        cout << "0. Exit" << endl << endl;
        
        cin >> choice;
        cout << endl;
        
        if (choice == 1)
        {
        	Customer c;
        	string name, phone;
            int hallNo, seatNo, hallType, seatType;
            
        	cin.ignore();
        	
            cout << "Enter customer name:" << endl;
            getline(cin, name);
            cout << "Enter customer phone no:" << endl;
            cin >> phone;
            
            cout << "Enter hall type:" << endl;
            cout << "1. 3D" << endl;
            cout << "2. 2D" << endl;
            cin >> hallType;
            
            
            if (hallType == 1)
            {
            	cout << "Select a hall" << endl;
            	cout << "\t1\t2\t3" << endl;
            	cin >> hallNo;
            	
            	if (hallNo < 1 || hallNo > 3)
            	{
            		cout << "Invalid input!" << endl << endl;
            		continue;
         	   }
            }
            
            else 
            {
            	cout << "Select a hall" << endl;
            	cout << "\t4\t5\t6" << endl;
            	cin >> hallNo;
            	
            	if (hallNo < 4 || hallNo > 6)
            	{
            		cout << "Invalid input!" << endl << endl;
            		continue;
         	   }
            }
            
            cout << "Enter seat type:" << endl;
            cout << "1. Premium" << endl;
            cout << "2. Regular" << endl;
            cin >> seatType;
            
            c.setCustomer(name, phone);
            
            cout << "Select a seat" << endl;
            ABC.displayAvailableSeats(hallNo, seatType == 1);
			cin >> seatNo;
			
			if ((seatType == 1) && (seatNo < 1 || seatNo > 30))
            {
            	cout << "Invalid input!" << endl << endl;
            	continue;
            }
            
            if (!(seatType == 1)&&(seatNo < 30 || seatNo > 60))
            {
            	cout << "Invalid input!" << endl << endl;
            	continue;
            }
            
			while(!ABC.bookTicket(c, hallNo, seatNo))
			{
				cout << "Plz select another seat" << endl;
				cin >> seatNo;
			}
			cout << endl;
			
			int reply;
			
			cout << "1. View details" << endl;
			cout << "2. Go to main menu" << endl;
			cin >> reply;
			
			if (reply == 1)
			{
				cout << endl << "Ticket details:" << endl;
				ABC.displaySeatDetails(hallNo, seatNo);
			}
			
			cout << endl;
		}
		
		else if (choice == 2)
		{
			cout << "Booked Tickets Details: " << endl;
			ABC.displayBookedTicketsDetails();
			cout << endl;
		}
		
		else if (choice == 3)
		{
			int choice;
			
			cout << "1. By customer phone no" << endl;
			cout << "2. By booked seat no" << endl;
			cin >> choice;
			
			if (choice == 1)
			{
				string phone;
				cout << "Enter phone no:" << endl;
				cin >> phone;
				search(&ABC, phone, "display");
			}
			
			else if (choice == 2)
			{
				int hallNo, seatNo;
				cout << "Enter hall no:" << endl;
				cin >> hallNo;
				cout << "Enter seat no:" << endl;
				cin >> seatNo;
				ABC.displaySeatDetails(hallNo, seatNo);
			}
			else
			{
				cout << "Invalid input!" << endl << endl;
				continue;
			}
			
			cout << endl;
		}
		
		else if (choice == 4)
		{
			string phone;
			cout << "Enter customer phone no:" << endl;
			cin >> phone;
			search(&ABC, phone, "cancel");
			cout << endl;
		}
		

		else if (choice == 0)
		{
			return 0;
		}
		
		else 
		{
			cout << "Invalid input" << endl << endl;
		}
		
	}
	
}