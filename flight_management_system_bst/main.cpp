#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// Global currency settings
bool usdMode = false;
double exchangeRate = 1.0;

enum relationshipType { LESS, GREATER, EQUAL };

class Flight
{
private:
    int flightID;
    string source;
    string destination;
    string airline;

    int departureHour;
    int departureMinute;

    int arrivalHour;
    int arrivalMinute;

    int durationHours;
    int durationMinutes;

    double ticketPrice;
    string status;

public:

    Flight()
    {
        flightID = 0;
        departureHour = 0;
        departureMinute = 0;
        arrivalHour = 0;
        arrivalMinute = 0;
        durationHours = 0;
        durationMinutes = 0;
        ticketPrice = 0;
        status = "Scheduled";
    }

    relationshipType ComparedTo(Flight other)
    {
        if (flightID < other.flightID)
        {
            return LESS;
        }
        else if (flightID > other.flightID)
        {
            return GREATER;
        }
        else
        {
            return EQUAL;
        }
    }

    void CalculateDuration()
    {
        int departureTotal = departureHour * 60 + departureMinute;
        int arrivalTotal = arrivalHour * 60 + arrivalMinute;

        if (arrivalTotal < departureTotal)
        {
            arrivalTotal += 1440;
        }

        int totalDuration = arrivalTotal - departureTotal;

        durationHours = totalDuration / 60;
        durationMinutes = totalDuration % 60;
    }

    bool initialize()
    {
        cout << "Enter Flight ID: ";
        if (!(cin >> flightID))
        {
            return false;
        }

        cout << "Enter Source: ";
        cin >> source;

        cout << "Enter Destination: ";
        cin >> destination;

        cout << "Enter Airline: ";
        cin >> airline;

        cout << "Enter Departure Hour (0-23): ";
        cin >> departureHour;

        if (departureHour < 0 || departureHour > 23)
        {
            cout << "Invalid departure hour!" << endl;
            return false;
        }

        cout << "Enter Departure Minute (0-59): ";
        cin >> departureMinute;

        if (departureMinute < 0 || departureMinute > 59)
        {
            cout << "Invalid departure minute!" << endl;
            return false;
        }

        cout << "Enter Arrival Hour (0-23): ";
        cin >> arrivalHour;

        if (arrivalHour < 0 || arrivalHour > 23)
        {
            cout << "Invalid arrival hour!" << endl;
            return false;
        }

        cout << "Enter Arrival Minute (0-59): ";
        cin >> arrivalMinute;

        if (arrivalMinute < 0 || arrivalMinute > 59)
        {
            cout << "Invalid arrival minute!" << endl;
            return false;
        }

        cout << "Enter Ticket Price in PKR: ";
        cin >> ticketPrice;

        if (ticketPrice < 0)
        {
            cout << "Ticket price cannot be negative!" << endl;
            return false;
        }

        CalculateDuration();
        status = "Scheduled";

        return true;
    }

    void print()
    {
        cout << endl;
        cout << "Flight ID: " << flightID << endl;
        cout << "Source: " << source << endl;
        cout << "Destination: " << destination << endl;
        cout << "Airline: " << airline << endl;

        cout << "Departure Time: ";

        if (departureHour < 10)
        {
            cout << "0";
        }

        cout << departureHour << ":";

        if (departureMinute < 10)
        {
            cout << "0";
        }

        cout << departureMinute << endl;

        cout << "Arrival Time: ";

        if (arrivalHour < 10)
        {
            cout << "0";
        }

        cout << arrivalHour << ":";

        if (arrivalMinute < 10)
        {
            cout << "0";
        }

        cout << arrivalMinute << endl;

        cout << "Duration: " << durationHours
            << " hours " << durationMinutes << " minutes" << endl;

        if (usdMode)
        {
            cout << "Ticket Price: USD " << ticketPrice / exchangeRate << endl;
        }
        else
        {
            cout << "Ticket Price: PKR " << ticketPrice << endl;
        }

        cout << "Status: " << status << endl;
    }

    int getFlightID()
    {
        return flightID;
    }

    string getSource()
    {
        return source;
    }

    string getDestination()
    {
        return destination;
    }

    string getAirline()
    {
        return airline;
    }

    string getStatus()
    {
        return status;
    }

    double getTicketPrice()
    {
        return ticketPrice;
    }

    int getDepartureHour()
    {
        return departureHour;
    }

    int getDepartureMinute()
    {
        return departureMinute;
    }

    int getArrivalHour()
    {
        return arrivalHour;
    }

    int getArrivalMinute()
    {
        return arrivalMinute;
    }

    int getDurationHours()
    {
        return durationHours;
    }

    int getDurationMinutes()
    {
        return durationMinutes;
    }

    void setStatus(string st)
    {
        status = st;
    }

    void setFlightData(int id, string src, string dest,
        string air, int dh, int dm, int ah, int am,
        double price, string st)
    {
        flightID = id;
        source = src;
        destination = dest;
        airline = air;

        departureHour = dh;
        departureMinute = dm;

        arrivalHour = ah;
        arrivalMinute = am;

        ticketPrice = price;
        status = st;

        CalculateDuration();
    }
};

struct Node
{
    Flight info;
    Node* left;
    Node* right;
    Node* parent;

    Node()
    {
        left = NULL;
        right = NULL;
        parent = NULL;
    }
};

class BST
{
private:

    Node* root;

   
    Node* Search(Node* x, int key)
    {
        if (x == NULL || x->info.getFlightID() == key)
        {
            return x;
        }

        if (key < x->info.getFlightID())
        {
            return Search(x->left, key);
        }

        return Search(x->right, key);
    }

    // Inorder Traversal

    void Inorder(Node* x)
    {
        if (x != NULL)
        {
            Inorder(x->left);
            x->info.print();
            Inorder(x->right);
        }
    }

 
    void FindAlternatives(Node* x, string src, string dest,
        int excludedID, bool& found)
    {
        if (x != NULL)
        {
            FindAlternatives(x->left, src, dest, excludedID, found);

            if (x->info.getFlightID() != excludedID &&
                x->info.getSource() == src &&
                x->info.getDestination() == dest &&
                x->info.getStatus() != "Cancelled")
            {
                x->info.print();
                found = true;
            }

            FindAlternatives(x->right, src, dest, excludedID, found);
        }
    }


    Node* Minimum(Node* x)
    {
        while (x->left != NULL)
        {
            x = x->left;
        }

        return x;
    }

    
    void Transplant(Node* u, Node* v)
    {
        if (u->parent == NULL)
        {
            root = v;
        }
        else if (u == u->parent->left)
        {
            u->parent->left = v;
        }
        else
        {
            u->parent->right = v;
        }

        if (v != NULL)
        {
            v->parent = u->parent;
        }
    }

    
    void WriteTime(ofstream& fout, int hour, int minute)
    {
        if (hour < 10)
        {
            fout << "0";
        }

        fout << hour << ":";

        if (minute < 10)
        {
            fout << "0";
        }

        fout << minute;
    }

    void SaveRecords(Node* x, ofstream& fout)
    {
        if (x != NULL)
        {
            SaveRecords(x->left, fout);

            fout << x->info.getFlightID() << ","
                << x->info.getSource() << ","
                << x->info.getDestination() << ","
                << x->info.getAirline() << ",";

            WriteTime(fout, x->info.getDepartureHour(),
                x->info.getDepartureMinute());

            fout << ",";

            WriteTime(fout, x->info.getArrivalHour(),
                x->info.getArrivalMinute());

            fout << ",";

            fout << x->info.getDurationHours() << ":";

            if (x->info.getDurationMinutes() < 10)
            {
                fout << "0";
            }

            fout << x->info.getDurationMinutes() << "/";

            double duration = x->info.getDurationHours() +
                x->info.getDurationMinutes() / 60.0;

            fout << duration << ","
                << x->info.getTicketPrice() << ","
                << x->info.getStatus() << endl;

            SaveRecords(x->right, fout);
        }
    }

    
    void Destroy(Node* x)
    {
        if (x != NULL)
        {
            Destroy(x->left);
            Destroy(x->right);
            delete x;
        }
    }

public:

    BST()
    {
        root = NULL;
    }

    ~BST()
    {
        Destroy(root);
    }

    bool Insert(Node* z)
    {
        Node* y = NULL;
        Node* x = root;

        while (x != NULL)
        {
            y = x;

            if (z->info.ComparedTo(x->info) == LESS)
            {
                x = x->left;
            }
            else if (z->info.ComparedTo(x->info) == GREATER)
            {
                x = x->right;
            }
            else
            {
                cout << "Duplicate Flight ID! Not inserted." << endl;
                delete z;
                return false;
            }
        }

        z->parent = y;

        if (y == NULL)
        {
            root = z;
        }
        else if (z->info.ComparedTo(y->info) == LESS)
        {
            y->left = z;
        }
        else
        {
            y->right = z;
        }

        z->left = NULL;
        z->right = NULL;

        return true;
    }

    void AddFlight()
    {
        Flight f;

        if (!f.initialize())
        {
            cout << "Flight was not added because the input was invalid." << endl;
            return;
        }

        Node* z = new Node;
        z->info = f;

        if (Insert(z))
        {
            cout << "Flight added successfully!" << endl;
        }
    }

    
    void SearchFlight(int key)
    {
        Node* result = Search(root, key);

        if (result == NULL)
        {
            cout << "Flight not found!" << endl;
            return;
        }

        result->info.print();

        if (result->info.getStatus() == "Cancelled")
        {
            cout << endl;
            cout << "This flight is cancelled." << endl;
            cout << "Other available flights on the same route:" << endl;

            bool found = false;

            FindAlternatives(root, result->info.getSource(),
                result->info.getDestination(), key, found);

            if (!found)
            {
                cout << "No alternative flights available." << endl;
            }
        }
    }

    // Delete flight

    void Delete(int key)
    {
        Node* z = Search(root, key);

        if (z == NULL)
        {
            cout << "Flight not found!" << endl;
            return;
        }

        if (z->left == NULL)
        {
            Transplant(z, z->right);
        }
        else if (z->right == NULL)
        {
            Transplant(z, z->left);
        }
        else
        {
            Node* y = Minimum(z->right);

            if (y->parent != z)
            {
                Transplant(y, y->right);
                y->right = z->right;
                y->right->parent = y;
            }

            Transplant(z, y);

            y->left = z->left;
            y->left->parent = y;
        }

        delete z;

        cout << "Flight deleted successfully!" << endl;
    }

    // Display all flights

    void DisplayFlights()
    {
        if (root == NULL)
        {
            cout << "No flights available!" << endl;
            return;
        }

        Inorder(root);
    }

    
    void CalculateETA(int key)
    {
        Node* x = Search(root, key);

        if (x == NULL)
        {
            cout << "Flight not found!" << endl;
            return;
        }

        int departure = x->info.getDepartureHour() * 60 +
            x->info.getDepartureMinute();

        int duration = x->info.getDurationHours() * 60 +
            x->info.getDurationMinutes();

        int eta = (departure + duration) % 1440;

        int etaHour = eta / 60;
        int etaMinute = eta % 60;

        cout << endl;
        cout << "Expected Time of Arrival: ";

        if (etaHour < 10)
        {
            cout << "0";
        }

        cout << etaHour << ":";

        if (etaMinute < 10)
        {
            cout << "0";
        }

        cout << etaMinute << endl;

        if (x->info.getStatus() == "Cancelled")
        {
            cout << "Flight is Cancelled." << endl;
            return;
        }

        int actualHour, actualMinute;

        cout << "Enter Actual Arrival Hour (0-23):";
        cin >> actualHour;

        if (actualHour < 0 || actualHour > 23)
        {
            cout << "Invalid arrival hour" << endl;
            return;
        }

        cout << "Enter Actual Arrival Minute (0-59): ";
        cin >> actualMinute;

        if (actualMinute < 0 || actualMinute > 59)
        {
            cout << "Invalid arrival minute!" << endl;
            return;
        }

        int actual = actualHour * 60 + actualMinute;

        int difference = actual - eta;

        if (difference < -720)
        {
            difference += 1440;
        }
        else if (difference > 720)
        {
            difference -= 1440;
        }

        if (difference < 0)
        {
            x->info.setStatus("Early");
        }
        else if (difference == 0)
        {
            x->info.setStatus("OnTime");
        }
        else
        {
            x->info.setStatus("Delayed");
        }

        cout << "Updated Flight Status: "
            << x->info.getStatus() << endl;
    }

    
    void UpdateFlightStatus(int key)
    {
        Node* x = Search(root, key);

        if (x == NULL)
        {
            cout << "Flight not found!" << endl;
            return;
        }

        string st;

        cout << "Enter new status (Scheduled, Early, OnTime, Delayed, Cancelled): ";
        cin >> st;

        if (st != "Scheduled" &&
            st != "Early" &&
            st != "OnTime" &&
            st != "Delayed" &&
            st != "Cancelled")
        {
            cout << "Invalid status!" << endl;
            return;
        }

        x->info.setStatus(st);

        cout << "Flight status updated successfully!" << endl;
    }

    // Global currency conversion

    void ChangeCurrency()
    {
        int choice;

        cout << endl;
        cout << "1. PKR" << endl;
        cout << "2. USD" << endl;
        cout << "Choose currency: ";
        cin >> choice;

        if (choice == 1)
        {
            usdMode = false;
            cout << "Ticket prices will now be displayed in PKR." << endl;
        }
        else if (choice == 2)
        {
            cout << "Enter current PKR value of 1 USD: ";
            cin >> exchangeRate;

            if (exchangeRate <= 0)
            {
                cout << "Invalid exchange rate!" << endl;
                exchangeRate = 1.0;
                usdMode = false;
                return;
            }

            usdMode = true;

            cout << "Ticket prices will now be displayed in USD." << endl;
        }
        else
        {
            cout << "Invalid choice!" << endl;
        }
    }

    
    void SaveFlights()
    {
        ofstream fout("flights.txt");

        if (!fout)
        {
            cout << "File could not be opened!" << endl;
            return;
        }

        SaveRecords(root, fout);

        fout.close();

        cout << "Flights saved successfully!" << endl;
    }

    // Load records from flights.txt

    void LoadFlights()
    {
        ifstream fin("flights.txt");

        if (!fin)
        {
            cout << "No saved flight file found. Starting empty." << endl;
            return;
        }

        
        Destroy(root);
        root = NULL;

        int id, dh, dm, ah, am;
        double price;

        char comma, colon;

        string src, dest, air, duration, st;

        while (fin >> id >> comma)
        {
            if (comma != ',')
            {
                break;
            }

            getline(fin, src, ',');
            getline(fin, dest, ',');
            getline(fin, air, ',');

            fin >> dh >> colon >> dm >> comma;

            if (!fin || colon != ':' || comma != ',')
            {
                break;
            }

            fin >> ah >> colon >> am >> comma;

            if (!fin || colon != ':' || comma != ',')
            {
                break;
            }

            getline(fin, duration, ',');

            fin >> price >> comma;

            if (!fin || comma != ',')
            {
                break;
            }

            getline(fin, st);

            Flight f;

            f.setFlightData(id, src, dest, air,
                dh, dm, ah, am, price, st);

            Node* z = new Node;
            z->info = f;

            Insert(z);
        }

        fin.close();

        cout << "Flights loaded successfully!" << endl;
    }
};

int main()
{
    BST flights;

    // Load saved records when the program starts

    flights.LoadFlights();

    int choice;
    int id;

    do
    {
        cout << endl;
        cout << "1. Add New Flight" << endl;
        cout << "2. Search Flight by ID" << endl;
        cout << "3. Delete Flight by ID" << endl;
        cout << "4. Display All Flights" << endl;
        cout << "5. Calculate Flight Duration and ETA" << endl;
        cout << "6. Update Flight Status" << endl;
        cout << "7. Save Flights to File" << endl;
        cout << "8. Load Flights from File" << endl;
        cout << "9. Change Currency (PKR/USD)" << endl;
        cout << "0. Exit" << endl;

        cout << "Enter your choice:";
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            flights.AddFlight();
            break;
        }

        case 2:
        {
            cout << "Enter Flightid: ";
            cin >> id;
            flights.SearchFlight(id);
            break;
        }

        case 3:
        {
            cout << "Enter Flightid: ";
            cin >> id;
            flights.Delete(id);
            break;
        }

        case 4:
        {
            flights.DisplayFlights();
            break;
        }

        case 5:
        {
            cout << "Enter Flight id: ";
            cin >> id;
            flights.CalculateETA(id);
            break;
        }

        case 6:
        {
            cout << "Enter Flight id:";
            cin >> id;
            flights.UpdateFlightStatus(id);
            break;
        }

        case 7:
        {
            flights.SaveFlights();
            break;
        }

        case 8:
        {
            flights.LoadFlights();
            break;
        }

        case 9:
        {
            flights.ChangeCurrency();
            break;
        }

        case 0:
        {
            flights.SaveFlights();
            cout << "Exiting" << endl;
            break;
        }

        default:
        {
            cout << "Invalid choice" << endl;
        }
        }

    } while (choice != 0);

    return 0;
}