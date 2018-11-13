#include "FlightBooking.h"//
// Created by gudmundur on 25.10.2018.
//

#include "FlightBooking.h"

FlightBooking::FlightBooking(int id, int capacity, int reserved)
{
    this->id = id;
    this->capacity = capacity;
    if (!isAllowedReservation(reserved))
    {
        throw invalid_argument("Reserved value above capacity");
    }
    if (reserved < 0) reserved = 0; // Ef það er í mínus breytist það í núll
    this->reserved = reserved;
}
void FlightBooking::printStatus()
{
    const float seatsReserved = ((float)reserved) / ((float)capacity) * 100.0f;
    cout << "Flight " << id << " : " << reserved << "/" << capacity << " (" << seatsReserved << "%) seats reserved" << endl;
}
bool FlightBooking::reserveSeats(int number_ob_seats)
{
    if (isAllowedReservation(number_ob_seats + reserved) && number_ob_seats >= 0) // Ef niðurstaðan eftir breytingar er leyfileg og talan sem var sett inn er ekki í mínus
    {
        reserved += number_ob_seats;
        return true;
    }
    return false;
}
bool FlightBooking::canceReservations(int number_ob_seats)
{
    if (reserved - number_ob_seats >= 0 && number_ob_seats >= 0) // Ef niðurstaðan eftir breytingu verður hærri en núll og talan sem var sett inn er ekki í mínus
    {
        reserved -= number_ob_seats;
        return true;
    }
    return false;
}
bool FlightBooking::isAllowedReservation(int reservation)
{
    return ((float)reservation) / ((float)capacity) < 1.05; // Skilar true eða false eftir því hvort það sé yfir leyfilega magninu sem er 105%
}

// FlightBooking list

FlightBookingList::FlightBookingList()
{
    first = nullptr;
    last = nullptr;
}

bool FlightBookingList::add(int id, FlightBooking *booking)
{
    if (!has(id)) return false;

    FlightBookingElement *el = new FlightBookingElement;
    el->id = id;
    el->booking = booking;

    if (first == nullptr)
    {
        first = el;
        last = el;
        return true;
    }
    if (first->id > id)
    {
        el->next = first;
        first = el;
        return true;
    }
    if (last->id < id)
    {
        last->next = el;
        last = el;
        return true;
    }
    FlightBookingElement* elBefore = getElementBefore(id);
    if (elBefore == nullptr) return false;
    el->next = elBefore->next;
    elBefore->next = el;
    /*FlightBookingElement *el = new FlightBookingElement;
    el->id = id;
    el->booking = booking;
    if (first == nullptr)
    {
        first = el;
    }
    if (last != nullptr)
    {
        last->next = el;
    }
    last = el;*/
}

FlightBooking* FlightBookingList::get(int id)
{
    if (has(id)) return getElement(id)->booking;
    return nullptr;
}

FlightBookingElement *FlightBookingList::getElement(int id)
{
    FlightBookingElement *current = first;
    while (current != nullptr)
    {
        if (current->id == id) return current;
        current = current->next;
    }
    return nullptr;
}

FlightBookingElement *FlightBookingList::getElementBefore(int id)
{
    FlightBookingElement *current = first;
    FlightBookingElement *last = nullptr;
    while (current != nullptr)
    {
        if (current->id == id) return last;
        last = current;
        current = current->next;
    }
    return nullptr;
}

bool FlightBookingList::has(int id)
{
    return getElement(id) != nullptr;
}

void FlightBookingList::remove(int id)
{
    FlightBookingElement *current = first;
    FlightBookingElement *last = nullptr;
    while (current != nullptr)
    {
        if (current->id == id) {
            if (last != nullptr) last->next = current->next;
            if (this->last == current) this->last = last;
            if (first == current){
                if (first->next != nullptr) first = first->next;
                else first = nullptr;
            }
            return;
        }

        last = current;
        current = current->next;
    }
}