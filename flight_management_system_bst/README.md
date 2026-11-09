# Flight Management System (C++ / Binary Search Tree)

A console-based flight management system written in C++ for the **Data Structures and Algorithms** course (Project, Module 1). Flight records are stored in a **Binary Search Tree (BST)** keyed by Flight ID, which keeps insertion, search and deletion efficient and gives sorted output through in-order traversal.

**Kinnaird College for Women University, Lahore, Department of Computer Science**

## Authors

| Name | 
| --- |
| Eman Fatima |
| Azka Khalid |

---

## Features

### Core features

| # | Feature | Description |
| --- | --- | --- |
| 1 | Add flight | Enter flight details with input validation. Duplicate Flight IDs are rejected. |
| 2 | Search flight | Find a flight by its ID. |
| 3 | Delete flight | Remove a flight by ID (handles leaf, one-child and two-child cases using successor and transplant). |
| 4 | Display all flights | Prints every flight in ascending Flight ID order (in-order traversal). |
| 5 | Duration and ETA | Calculates the expected arrival time, then compares it to the actual arrival time and updates the status automatically. |
| 6 | Update flight status | Manually set status to `Scheduled`, `Early`, `OnTime`, `Delayed` or `Cancelled`. |
| 7 | Save to file | Writes all flights to `flights.txt`. |
| 8 | Load from file | Reads flights back from `flights.txt` into the BST. |
| 9 | Change currency | Switch ticket price display between PKR and USD. |
| 0 | Exit | Saves all flights automatically and quits. |

### Additional features implemented

**1. Global currency conversion (PKR to USD)**
Users can switch the displayed ticket prices between PKR and USD. It uses two global variables, `usdMode` and `exchangeRate`. `ChangeCurrency()` takes the user's choice and the PKR value of 1 USD, and `Flight::print()` converts by dividing the PKR price by the exchange rate. Prices are always stored in PKR; only the display changes.

**2. Alternative flight suggestions for cancelled flights**
When a searched flight is cancelled, the program automatically lists other flights with the same source and destination, excluding the cancelled flight and any other cancelled flights. This is done by the recursive `FindAlternatives()` function, which traverses the BST and checks each flight's route and status.

---

## Data Structure Overview

- **`Flight`** class: stores flight details (ID, source, destination, airline, departure/arrival time, duration, ticket price, status). Includes `ComparedTo()` for ordering by Flight ID and `CalculateDuration()`, which handles flights that arrive after midnight.
- **`Node`** struct: holds a `Flight` plus `left`, `right` and `parent` pointers.
- **`BST`** class: manages the tree.

### Time complexity

| Operation | Average | Worst case (skewed tree) |
| --- | --- | --- |
| Insert | O(log n) | O(n) |
| Search | O(log n) | O(n) |
| Delete | O(log n) | O(n) |
| Display (in-order) | O(n) | O(n) |
| Find alternatives | O(n) | O(n) |

---

## Getting Started

### Requirements

- A C++ compiler with C++11 support or later (g++, clang++, or MSVC)

### Compile

```bash
g++ -o flight_system main.cpp
```

### Run

```bash
./flight_system        # Linux / macOS
flight_system.exe      # Windows
```

> Replace `main.cpp` with the actual name of your source file.

---

## Usage

On startup the program loads saved flights from `flights.txt` (if it exists) and shows this menu:

```
1. Add New Flight
2. Search Flight by ID
3. Delete Flight by ID
4. Display All Flights
5. Calculate Flight Duration and ETA
6. Update Flight Status
7. Save Flights to File
8. Load Flights from File
9. Change Currency (PKR/USD)
0. Exit
```

### Example: adding a flight

```
Enter Flight ID: 101
Enter Source: Lahore
Enter Destination: Karachi
Enter Airline: PIA
Enter Departure Hour (0-23): 9
Enter Departure Minute (0-59): 30
Enter Arrival Hour (0-23): 11
Enter Arrival Minute (0-59): 15
Enter Ticket Price in PKR: 35000
Flight added successfully!
```

### Example: displaying a flight

```
Flight ID: 101
Source: Lahore
Destination: Karachi
Airline: PIA
Departure Time: 09:30
Arrival Time: 11:15
Duration: 1 hours 45 minutes
Ticket Price: PKR 35000
Status: Scheduled
```

---

## File Format

Flights are saved to `flights.txt`, one flight per line, as comma-separated values:

```
FlightID,Source,Destination,Airline,DepartureTime,ArrivalTime,Duration,Price,Status
```

Example line:

```
101,Lahore,Karachi,PIA,09:30,11:15,1:45/1.75,35000,Scheduled
```

The `flights.txt` file is created in the folder the program is run from.

---

## Input Validation

- Departure and arrival hours must be between 0 and 23
- Departure and arrival minutes must be between 0 and 59
- Ticket price cannot be negative
- Flight IDs must be unique
- The exchange rate must be greater than 0
- Status must be one of `Scheduled`, `Early`, `OnTime`, `Delayed`, `Cancelled`

## Known Limitations

- Source, destination and airline are read with `cin >>`, so they must be a single word (use `NewYork`, not `New York`).
- The BST is not self-balancing, so performance can degrade to O(n) if flights are inserted in sorted ID order.
- The exchange rate is entered manually and is not fetched live.

---

## Project Structure

```
.
├── main.cpp        # Source code
├── flights.txt     # Saved flight records (created at runtime)
└── README.md
```

## License

This project was created for academic purposes.
