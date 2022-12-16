//##############################################
// Project: CustomerOrder Management System  ###						 ###
//##############################################

#include "Utilities.h"
namespace sdds
{
    char Utilities::m_delimiter = '\0';
    void Utilities::setFieldWidth(size_t newWidth)
    {
        this->m_widthField = newWidth;
    }
    size_t Utilities::getFieldWidth() const
    {
        return this->m_widthField;
    }
    void Utilities::setDelimiter(char newDelimiter)
    {
        m_delimiter = newDelimiter;
    }
    char Utilities::getDelimiter()
    {
        return m_delimiter;
    }
    std::string Utilities::extractToken(const std::string &str, size_t &next_pos, bool &more)
    {
        more = false;
        std::string token = "";
        size_t prev_next_pos = next_pos;
        next_pos = str.find(Utilities::m_delimiter, prev_next_pos);
        if (next_pos == std::string::npos)
        {
            token = str.substr(prev_next_pos);
        }
        else if (prev_next_pos == next_pos)
        {
            throw std::string("Error: No Token Found");
        }
        else
        {
            token = str.substr(prev_next_pos, next_pos - prev_next_pos);
            more = true;
        }
        // Remove Spaces
        token.erase(0, token.find_first_not_of(' '));
        token.erase(token.find_last_not_of(' ') + 1);
        if (token.length() > this->m_widthField)
        {
            this->m_widthField = token.length();
        }
        next_pos++;
        return token;
    }
}