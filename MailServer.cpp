#include "MailServer.hpp"
#include "email.hpp"
#include "UserAccount.hpp"
#include <iostream>

using std::cout;
using std::endl;

 // MailServer sends an email From Sender to Server //
void MailServer::sendMailsToServer( Email &E )
{
    EmailsToSend.push(E);
    E.from.SentMails.push(E);
}


// After Receiving Emails Server Processes them //
// Send Them to Destination
bool MailServer::sendEmailToDestination( Email &E )
{
    E.to.MailBox.push(E);
}


 bool MailServer::checkReachDestination( Email &E ) const
 {
     return E.to.MailBox.contains( E );
 }


 bool MailServer::contains ( Email & E ) const
 {
     return find(E.to.MailBox.begin(), E.to.MailBox.end() !=E.to.MailBox.end() );
 }


 Email MailServer::keepEmailCopy ( Email & E ) const
 {
     if( ! ( checkReachDestination( E )))
        // overloading email obj equality is required //
        Email mailCopy = E;
        return mailCopy;
 }


// Resend the Copy of the UNSENT EMAIL //
bool MailServer::resendEmail( Email &E )
{
    Email mailCopy=keepEmailCopy ( E );
    EmailsToSend.push( E );
}

// an Email is RESENT if Sender has NO NEW MSSGS TO SEND //
            // AND //
// it has not been sent 3 times
            // AND //
// it has not reached destination

bool MailServer::reSendEmailConditions( UserAccount Sender, Email E ) const
{
    return (Sender.SentMails.top()== E && E.sendingTimes<3 && !(checkReachDestination( E )));
}



void MailServer::destroyEmail()
{
    int n=3;
    for(int i=0; i<n; i++)
    {
        EmailsToSend.deque();
    }
}


void MailServer::notifySenderOfAnError() const
{
    cout<<" EMAIL HAS NOT REACHED DESTINATION !! "<<endl;
}



