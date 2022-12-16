//##############################################
// Project: CustomerOrder Management System  ###						 ###
//##############################################

#include <algorithm>
#include <iomanip>
#include "CustomerOrder.h"
#include "Utilities.h"
namespace sdds
{
	CustomerOrder::CustomerOrder()
	{
		m_name = "";
		m_product = "";
		m_cntItem = 0;
		m_lstItem = nullptr;
	}
	CustomerOrder::CustomerOrder(const std::string &record)
	{
		Utilities ut;
		size_t next_pos = 0;
		bool more = true;
		m_name = ut.extractToken(record, next_pos, more);
		m_product = ut.extractToken(record, next_pos, more);
		m_cntItem = 0;
		for (int i = next_pos; record[i] != '\0'; i++)
		{
			if (record[i] == ut.getDelimiter())
			{
				m_cntItem++;
			}
		}
		m_cntItem++;
		m_lstItem = new Item *[m_cntItem];
		for (size_t i = 0; i < m_cntItem; i++)
		{
			m_lstItem[i] = new Item(ut.extractToken(record, next_pos, more));
		}
		m_widthField = std::max(m_widthField, ut.getFieldWidth());
	}
	CustomerOrder::CustomerOrder(const CustomerOrder &coObj)
	{
		throw "Exception";
	}
	CustomerOrder::CustomerOrder(CustomerOrder &&coObj) noexcept
	{
		m_lstItem = nullptr;
		*this = std::move(coObj);
	}
	CustomerOrder &CustomerOrder::operator=(CustomerOrder &&coObj) noexcept
	{
		if (this != &coObj)
		{
			if (m_lstItem)
			{
				// deallocation of m_lstItem
				for (size_t i = 0; i < m_cntItem; i++)
					delete m_lstItem[i];
				delete[] m_lstItem;
			}

			// copying the coObj to *this
			m_cntItem = coObj.m_cntItem;
			m_lstItem = coObj.m_lstItem;
			m_name = coObj.m_name;
			m_product = coObj.m_product;

			// initializing default values to coObj
			coObj.m_name = "";
			coObj.m_product = "";
			coObj.m_lstItem = nullptr;
			coObj.m_cntItem = 0;
		}
		return *this;
	}
	CustomerOrder::~CustomerOrder()
	{
		// deallocation of m_lstItem
		for (size_t i = 0; i < m_cntItem; i++)
			delete m_lstItem[i];
		delete[] m_lstItem;
	}
	bool CustomerOrder::isOrderFilled() const
	{
		bool orderFilled = true;
		for (size_t i = 0; i < m_cntItem && orderFilled; i++)
		{
			orderFilled = m_lstItem[i]->m_isFilled;
		}
		return orderFilled;
	}
	bool CustomerOrder::isItemFilled(const std::string &itemName) const
	{
		bool itemFilled = true;
		for (size_t i = 0; i < m_cntItem && itemFilled; i++)
		{
			if (m_lstItem[i]->m_itemName == itemName)
			{
				itemFilled = m_lstItem[i]->m_isFilled;
			}
		}
		return itemFilled;
	}
	void CustomerOrder::fillItem(Station &station, std::ostream &os)
	{
		bool flag = false;
		if (m_lstItem && m_cntItem > 0)
		{
			for (size_t i = 0; i < m_cntItem && !flag; i++)
			{
				if (!m_lstItem[i]->m_isFilled && m_lstItem[i]->m_itemName == station.getItemName())
				{
					if (station.getQuantity() > 0)
					{
						m_lstItem[i]->m_isFilled = true;
						os << std::setw(11) << std::right << "Filled " << m_name << ", " << m_product;
						os << " [" << m_lstItem[i]->m_itemName << "]" << std::endl;
						station.updateQuantity();
						m_lstItem[i]->m_serialNumber = station.getNextSerialNumber();
						flag = true;
					}
					else
					{
						os << "    Unable to fill " << m_name << ", " << m_product
						   << " [" << m_lstItem[i]->m_itemName << "]" << std::endl;
					}
				}
			}
		}
	}
	void CustomerOrder::display(std::ostream &os) const
	{
		os << m_name << " - " << m_product << std::endl;
		for (size_t i = 0; i < m_cntItem; i++)
		{
			os << "[" << std::setw(6) << std::setfill('0') << m_lstItem[i]->m_serialNumber << "] ";
			os << std::setfill(' ') << std::setw(m_widthField) << std::left << m_lstItem[i]->m_itemName;
			os << "   - " << std::right;

			if (m_lstItem[i]->m_isFilled)
			{
				os << "FILLED\n";
			}
			else
			{
				os << "TO BE FILLED\n";
			}
		}
	}
	size_t CustomerOrder::m_widthField = 0;
}