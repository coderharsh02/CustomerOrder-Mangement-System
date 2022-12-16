//##############################################
// Project: CustomerOrder Management System  ###						 ###
//##############################################

#include <string>
#include <iomanip>
#include "Utilities.h"
#include "Station.h"
namespace sdds
{
    size_t Station::m_widthField = 0;
    size_t Station::id_generator = 0;
    Station::Station(const std::string &record)
    {
        Utilities ut;
        size_t next_pos = 0;
        bool more = true;
        stationId = ++id_generator;
        itemHandledName = ut.extractToken(record, next_pos, more);
        nextSerialNumber = (size_t)(std::stoi(ut.extractToken(record, next_pos, more)));
        currentStock = (size_t)(std::stoi(ut.extractToken(record, next_pos, more)));
        m_widthField = std::max(m_widthField, ut.getFieldWidth());
        stationDescription = ut.extractToken(record, next_pos, more);
    }
    const std::string &Station::getItemName() const
    {
        return this->itemHandledName;
    }
    size_t Station::getNextSerialNumber()
    {
        return this->nextSerialNumber++;
    }
    size_t Station::getQuantity() const
    {
        return this->currentStock;
    }
    void Station::updateQuantity()
    {
        currentStock = (currentStock == 0) ? (0) : (currentStock - 1);
    }
    void Station::display(std::ostream &os, bool full) const
    {
        os << std::setw(3) << std::setfill('0') << stationId << " | ";
        os << std::setw(m_widthField + 1) << std::setfill(' ') << std::left << itemHandledName << " | ";
        os << std::setw(6) << std::setfill('0') << std::right << nextSerialNumber << " | ";
        os << std::setfill(' ');
        if (full)
        {
            os << std::setw(4) << currentStock << " | ";
            os << stationDescription;
        }
        os << std::endl;
    }
}