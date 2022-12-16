//##############################################
// Project: CustomerOrder Management System  ###						 ###
//##############################################

#include <fstream>
#include <algorithm>
#include<string>
#include "LineManager.h"
#include "Utilities.h"
using namespace std;
namespace sdds
{
    LineManager::LineManager(const string &file, const vector<Workstation *> &stations)
    {
        ifstream fp(file);
        if (!fp)
        {
            throw string("Unable to open [") + file + "] file.";
        }
        while (!fp.eof())
        {
            string str, currWS, nextWS;
            getline(fp, str);
            Utilities localObj;
            size_t next_pos = 0;
            bool more = true;
            currWS = localObj.extractToken(str, next_pos, more);
            nextWS = "";
            if (more)
            {
                nextWS = localObj.extractToken(str, next_pos, more);
            }
            auto currWorkStation = find_if(stations.begin(), stations.end(),
            [&](Workstation *ws)
            {
                bool flag = false;
                if (ws->getItemName() == currWS)
                {
                    flag = true;
                }
                return flag;
            });
            if (nextWS != "")
            {
                auto nextWorkStation = find_if(stations.begin(), stations.end(),
                [&](Workstation *ws)
                {
                    bool flag = false;
                    if (ws->getItemName() == nextWS)
                    {
                        flag = true;
                    }
                    return flag;
                });
                if (nextWorkStation != stations.end())
                {
                    (*currWorkStation)->setNextStation(*nextWorkStation);
                }
            }
            else
            {
                m_firstStation = *currWorkStation; // currently stores last station
            }
            activeLine.push_back(move(*currWorkStation));
        }
        fp.close();
        m_cntCustomerOrder = g_pending.size();
    }
    void LineManager::reorderStations()
    {
        auto lastWorkStation = find_if(activeLine.begin(), activeLine.end(), [&](Workstation *ws)
        { return ws == m_firstStation; });
        iter_swap(lastWorkStation, activeLine.begin());
        string find = "";
        size_t iter = 0;
        for_each(activeLine.begin(), activeLine.end(), [&](Workstation *ws)
        {
            iter++;
            auto prevWorkStation = find_if(activeLine.begin() + iter, activeLine.end(), [&](Workstation *pws){ return ws == pws->getNextStation(); } );
            if (prevWorkStation != activeLine.end())
            {
                iter_swap(activeLine.begin() + iter, prevWorkStation);
            } 
        });
        reverse(activeLine.begin(), activeLine.end());
        m_firstStation = *activeLine.begin();
    }
    bool LineManager::run(ostream &os)
    {
        static size_t counter = 0u;
        os << "Line Manager Iteration: " << ++counter << "\n";
        if (g_pending.size())
        {
            *m_firstStation += (move(g_pending.front()));
            g_pending.pop_front();
        }
        for_each(activeLine.begin(), activeLine.end(), [&](Workstation *station)
        { 
            station->fill(os); 
        });
        for_each(activeLine.begin(), activeLine.end(), [&](Workstation *station)
        {
            station->attemptToMoveOrder(); 
        });
        return (g_incomplete.size() + g_completed.size()) == m_cntCustomerOrder;
    }
    void LineManager::display(ostream &os) const
    {
        for_each(activeLine.begin(), activeLine.end(), [&](Workstation *station)
        { 
            station->display(os); 
        });
    }
}
