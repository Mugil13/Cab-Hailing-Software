# Software system for Hailing Cab

This software system is designed to efficiently assign cabs to customers based on their requests and locations. It considers various factors such as customer preferences, driver availability, distance, and fare calculations. The system aims to provide a seamless experience for customers while optimizing cab allocation.

# Problem Statement

The objective of this project is to develop a software system that can assign cabs to customers based on their requests and locations. The system should consider the following aspects:

* Customer requests include their pickup location, destination, and preferred mode of travel (e.g., auto, mini sedan, sedan, SUV, Innova, etc.).
* Each customer is charged a fixed base fare plus additional fare based on the distance traveled.
* During peak demand times, a surge fee should be applied.
* Customers can make advance bookings, which will include advance booking fees.
* If a customer cancels a ride, a cancellation fee should be charged.
  
The software system needs to meet the following constraints:

* Assign a driver with the minimum waiting time for the customer.
* Assign the best available driver based on their average rating.
* Minimize the distance the assigned driver needs to drive to pick up the customer
  
# Requirements
Compilers like gcc or Clang that are capable of compiling a C code.<br/>
We have used gcc for demonstration.

# Input
The system takes the following inputs:

* Set of customer requests, each comprising the pickup location, destination, and mode of travel.
* Number of vehicles available in each category (auto, mini sedan, sedan, SUV, Innova, etc.).

# Output
The system provides the following outputs:

* Allocation of suitable cabs to customers based on their requests and locations.
* Generation of the bill for each customer, including the base fare, distance-based fare, surge fee (if applicable), and advance booking fees (if applicable).

# Features and Components

The software system includes the following features and components:

1. **Customer Management:** Handles customer details, requests, and booking information.
2. **Driver Management:** Manages driver information, availability, and ratings.
3. **Cab Allocation:** Assigns the most suitable cab to each customer based on their request and available drivers.
4. **Distance Calculation:** Determines the distance between the pickup and drop-off locations.
5. **Fare Calculation:** Calculates the fare based on the distance traveled and selected mode of travel, considering the base fare and any additional charges (surge fee, advance booking fee).
6. **Billing and Payment:** Generates bills for customers, including the calculated fare and any applicable fees.

# How to run the System

Compilation of the code is done by
```
gcc main.c -o main -lm
```
The code is run by
```
./main
```

# Authors
Mugilkrishna D U<br/>
Nikilesh Jayaguptha<br/>
Neha Shanmitha

# Acknowledgements
https://www.youtube.com/watch?v=-L-WgKMFuhE<br/>
https://www.uber.com/global/en/price-estimate/<br/>
https://economictimes.indiatimes.com/news/politics-and-nation/all-taxis-to-charge-government-set-fares-after-aug-22-high-court/articleshow/53654050.cms?from=mdr<br/>
https://www.numbeo.com/taxi-fare/in/Chennai<br/>
https://neo4j.com/developer/graph-data-science/path-finding-graph-algorithms/<br/>

# Conclusion

This software system provides efficient solution for assigning cabs to customers based on their locations and requests. It considers various factors such as customer preferences, driver availability, distance, and fare calculations to ensure a smooth and reliable cab booking experience.









