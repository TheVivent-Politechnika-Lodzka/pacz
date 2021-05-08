#include <iostream>
#include <boost/date_time.hpp>
#include "SingleTicket.h"
#include "GroupTicket.h"
#include "Client.h"
#include "Aquarium.h"
#include "Attraction.h"

namespace pt = boost::posix_time;
namespace gr = boost::gregorian;


using namespace std;

int main(){

    Aquarium *a1=new Aquarium(5,10);

    a1->addToAttractionList(0.01,96,"Rollercoaster z Pawełem Jaśpińskim");
    a1->addToAttractionList(420,69,"Rollercoaster z Weroniką Pacyniak");
    a1->clients()->registerClient("Damian","Szczeciński","Posejdon");
    a1->clients()->registerClient("Adam","Kapuściński","Hefajstos");
    a1->tickets()->registerTicket("uno",pt::not_a_date_time,a1->clients()->getByIndex(0),STUDENT);
    a1->tickets()->addToAttractionList(a1->attractions()->getAttractionByIndex(0));
    a1->tickets()->addToAttractionList(a1->attractions()->getAttractionByIndex(1));
    a1->tickets()->registerTicket("dos",pt::not_a_date_time,a1->clients()->getByIndex(1),4,FAMILY);
    a1->tickets()->registerTicket("tres",pt::not_a_date_time,nullptr,10,TOUR);

    cout<< *a1 << endl;

    return 0;
}
