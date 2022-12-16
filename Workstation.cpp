//##############################################
// Project: CustomerOrder Management System  ###						 ###
//##############################################

#include "Workstation.h"
namespace sdds
{
    std::deque<CustomerOrder> g_pending;
    std::deque<CustomerOrder> g_completed;
    std::deque<CustomerOrder> g_incomplete;

    Workstation::Workstation(const std::string &record) : Station(record) {}
    void Workstation::fill(std::ostream &os)
    {
        if (m_orders.size())
        {
            m_orders.front().fillItem(*this, os);
        }
    }
    bool Workstation::attemptToMoveOrder()
    {
        bool orderMovedFlag = false;

        if (!m_orders.empty() && (m_orders.front().isItemFilled(getItemName()) || getQuantity() == 0))
        {
            if (m_pNextStation)
            {
                (*m_pNextStation) += std::move(m_orders.front());
                orderMovedFlag = true;
            }
            else if (m_orders.front().isOrderFilled())
                g_completed.push_back(std::move(m_orders.front()));
            else
                g_incomplete.push_back(std::move(m_orders.front()));

            m_orders.pop_front();
        }
        return orderMovedFlag;
    }
    void Workstation::setNextStation(Workstation *station)
    {
        m_pNextStation = station;
    }
    Workstation *Workstation::getNextStation() const
    {
        return m_pNextStation;
    }
    void Workstation::display(std::ostream &os) const
    {
        os << getItemName() << " --> ";
        if (m_pNextStation != nullptr)
        {
            os << m_pNextStation->getItemName();
            os << std::endl;
        }
        else
        {
            os << "End of Line\n";
        }
    }
    Workstation &Workstation::operator+=(CustomerOrder &&newOrder)
    {
        m_orders.push_back(std::move(newOrder));
        return *this;
    }
}