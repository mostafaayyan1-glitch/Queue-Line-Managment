#pragma once
#include <iostream>
#include <string>
#include "clsDate.h"
#include <queue>
#include <stack>
using namespace std;
/**
 * Class: clsQueueLine
 * ------------------
 * Manages the entire queue system: issuing tickets, serving clients,
 * and displaying queue statistics.
 */
class clsQueueLine
{
private:
    string _prifix;
    int _Total_Tickets = 0;
    int _Average_Serve_Time = 0;
    /**
     * Inner Class: clsTicket
     * ----------------------
     * Represents an individual ticket with its specific data.
     */
    class clsTicket
    {
    private:
        string _Time_of_Ticket;
        int _Average_Serve_Time;
        int _Waiting_Clients;
        int _Number_of_Ticket;
        string _Prifix;

    public:
        // Constructor: Initializes ticket data at the moment of issuance
        clsTicket(int average, int waiting, int number, string prifix)
        {
            _Time_of_Ticket = clsDate::GetSystemDateTimeString();
            _Average_Serve_Time = average;
            _Waiting_Clients = waiting;
            _Number_of_Ticket = number;
            _Prifix = prifix;
        }
        string TimeOfTickets() const { return _Time_of_Ticket; }
        int AverageServeTime() const { return _Average_Serve_Time; }
        // Calculates estimated wait time based on the number of people in line
        int ExpectedForServe() const { return _Average_Serve_Time * _Waiting_Clients; }
        int NumberOfTicket() const { return _Number_of_Ticket; }
        int NumberOfWaitingClients() const { return _Waiting_Clients; }
        string Prifix() const { return _Prifix; }
        // Returns the ticket unique identifier (e.g., A1, A2)
        string FullName() const { return _Prifix + to_string(_Number_of_Ticket); }
        // Prints ticket details in a formatted UI
        void Print() const
        {
            cout << "\n----------------------------------------\n";
            cout << "              Ticket Info               \n";
            cout << "----------------------------------------\n";
            cout << "Prifix               : " << _Prifix << endl;
            cout << "Time Of This Ticket  : " << _Time_of_Ticket << endl;
            cout << "Waiting Clients      : " << _Waiting_Clients << endl;
            cout << "Expected Served Time : " << ExpectedForServe() << " Minutes" << endl;
            cout << "----------------------------------------\n";
        }
    };
public:
    queue<clsTicket> QueueLine;
    // Initializes the system with a prefix and average service time per client
    clsQueueLine(string Prif, int Average)
        : _prifix(Prif), _Average_Serve_Time(Average), _Total_Tickets(0) {
    }
    string Prif() const { return _prifix; }
    int TotalTickets() const { return _Total_Tickets; }
    int AverageServeTime() const { return _Average_Serve_Time; }
    // Generates a new ticket and pushes it to the queue
    void IssueTicket()
    {
        _Total_Tickets++;
        clsTicket Ticket(_Average_Serve_Time, (int)QueueLine.size(), _Total_Tickets, _prifix);
        QueueLine.push(Ticket);
    }
    // Removes the next client from the queue
    bool ServedClient()
    {
        if (QueueLine.empty()) return false;
        QueueLine.pop();
        return true;
    }
    // Returns the ID of the next client in line
    string WhoIsNext() const
    {
        return QueueLine.empty() ? "Not Found Any Client Yet :( " : QueueLine.front().FullName();
    }
    // Returns the total number of clients served so far
    int NumberOfServedClients() const
    {
        return _Total_Tickets - (int)QueueLine.size();
    }
    // Displays current queue statistics
    void Print() const
    {
        cout << "\n----------------------------------\n";
        cout << "             Queue Info           \n";
        cout << "----------------------------------\n";
        cout << "Prifix         : " << Prif() << endl;
        cout << "Total Tickets  : " << TotalTickets() << endl;
        cout << "Waiting Clients: " << QueueLine.size() << endl;
        cout << "Served Clients : " << NumberOfServedClients() << endl;
        cout << "----------------------------------\n";
    }
    // Prints queue from the front to the end (Left-to-Right)
    void PrintFromLTR()
    {
        queue<clsTicket> Temp = QueueLine;
        cout << "-->";
        while (!Temp.empty()) {
            cout << Temp.front().FullName() << "-->";
            Temp.pop();
        }
        cout << endl;
    }
    // Prints queue from end to front (Right-to-Left) using a Stack
    void PrintFromRTL()
    {
        queue<clsTicket> TempQueue = QueueLine;
        stack<clsTicket> TempStack;
        while (!TempQueue.empty()) {
            TempStack.push(TempQueue.front());
            TempQueue.pop();
        }
        cout << "<--";
        while (!TempStack.empty()) {
            cout << TempStack.top().FullName() << "<--";
            TempStack.pop();
        }
        cout << endl;
    }
    // Prints detailed info for every ticket currently in the queue
    void PrintAllTickets()
    {
        queue<clsTicket> TempQueue = QueueLine;
        while (!TempQueue.empty())
        {
            TempQueue.front().Print();
            TempQueue.pop();
        }
    }
};