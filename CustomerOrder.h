//##############################################
// Project: CustomerOrder Management System  ###						 ###
//##############################################

#ifndef SDDS_CUSTOMERORDER_H
#define SDDS_CUSTOMERORDER_H
#include "Station.h"
namespace sdds
{
	class CustomerOrder
	{
		struct Item
		{
			std::string m_itemName;
			size_t m_serialNumber{0};
			bool m_isFilled{false};
			Item(const std::string &src) : m_itemName(src){};
		};
		std::string m_name;
		std::string m_product;
		size_t m_cntItem;
		Item **m_lstItem;
		static size_t m_widthField;

	public:
		CustomerOrder();
		CustomerOrder(const std::string &record);
		CustomerOrder(const CustomerOrder &coObj);
		CustomerOrder &operator=(const CustomerOrder &coObj) = delete;
		CustomerOrder(CustomerOrder &&coObj) noexcept;
		CustomerOrder &operator=(CustomerOrder &&coObj) noexcept;
		~CustomerOrder();
		bool isOrderFilled() const;
		bool isItemFilled(const std::string &itemName) const;
		void fillItem(Station &station, std::ostream &os);
		void display(std::ostream &os) const;
	};
}
#endif