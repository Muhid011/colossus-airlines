# Colossus Airlines Program

## Program Main Goal
The goal is to create a program that manages seat reservations for a plane with 48 seats. The plane has two flights, both inbound and outbound. This program lets the user view empty seats, assign new seats, delete seats, and see a list of passengers, even in alphabetical order.

## Solution
I used an array of structures to store seat information. Each seat has a seat number, whether it is taken, and the passenger’s first and last name.  

This program has two menus:
- The first menu lets the user choose outbound, inbound, or quit  
- The second menu lets the user choose between:
  - see empty seats
  - list empty seats
  - see seats in alphabetical order
  - assign a seat
  - delete a seat  

I also added file handling to make the data permanent
-This program saves data using fwrite
-This program also loads the data by using fread whenever it starts
This program also runs until the user chooses to quit, and afterward, all the data is lost when the program ends.

## Pros and Cons

**Pros:**
- Easy to use and understand the menu system  
- You can assign and remove seats easily  
- Shows seats in alphabetical order  
- Works for both inbound and outbound flights 
- Data is saved when the program ends

**Cons:**
- Only works for up to 48 seats  
- Files aren't readable
- No error if the file is corrupted
- Basic text interface is not really creative  

## My Screenshots
<img width="825" height="922" alt="image" src="https://github.com/user-attachments/assets/cdc9885b-d0d3-462d-93ba-4a7c986c71b5" />
<img width="1086" height="963" alt="image" src="https://github.com/user-attachments/assets/daebaa91-f3bb-49eb-867f-1ccbdb6c7ae1" />
<img width="443" height="810" alt="image" src="https://github.com/user-attachments/assets/2af93e65-5185-4235-983b-9d4b17dccfea" />



