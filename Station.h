//##############################################
// Project: CustomerOrder Management System  ###						 ###
//##############################################

#ifndef SDDS_STATION_H
#define SDDS_STATION_H
#include <iostream>
namespace sdds
{
    class Station
    {
        int stationId;
        std::string itemHandledName;
        std::string stationDescription;
        size_t nextSerialNumber;
        size_t currentStock;

        static size_t m_widthField;
        static size_t id_generator;

    public:
        Station(const std::string &record);
        const std::string &getItemName() const;
        size_t getNextSerialNumber();
        size_t getQuantity() const;
        void updateQuantity();
        void display(std::ostream &os, bool full) const;
    };
}
#endif