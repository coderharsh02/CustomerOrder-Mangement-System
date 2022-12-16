//##############################################
// Project: CustomerOrder Management System  ###						 ###
//##############################################

#ifndef SDDS_LINE_MANAGER_H
#define SDDS_LINE_MANAGER_H
#include <vector>
#include "Workstation.h"
namespace sdds
{
    class LineManager
    {
        std::vector<Workstation *> activeLine;
        std::size_t m_cntCustomerOrder{0};
        Workstation *m_firstStation{nullptr};

    public:
        LineManager(const std::string &file, const std::vector<Workstation *> &stations);
        void reorderStations();
        bool run(std::ostream &os);
        void display(std::ostream &os) const;
    };
}
#endif