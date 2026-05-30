#include "clsQueueLine.h"
using namespace std;
int main()
{
    clsQueueLine Que("A", 10);
    Que.IssueTicket();
    Que.IssueTicket();
    Que.IssueTicket();
    Que.IssueTicket();
    Que.IssueTicket();
    Que.IssueTicket();
    Que.Print();
    Que.ServedClient();
    Que.ServedClient();
    Que.Print();
    Que.PrintFromLTR();
    Que.PrintFromRTL();
    cin.get();
    return 0;
}