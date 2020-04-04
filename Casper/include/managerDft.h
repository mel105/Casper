#ifndef MANAGERDFT_H
#define MANAGERDFT_H

/**************************************************************************************************
 @Founder: Michal Elias
 @Linux Ubuntu 18.4.2 LTS
 @Last revision: 2020-02-01 10:08:45 Author: Michal Elias  

 @Brief: Ensures basic descriptive statistics calculation.
 @Details:
  
 @Reference:
***************************************************************************************************/

#include <map>
#include <vector>
#include <string>
#include <cstring>
#include <fstream>
#include <iostream>
#include <iomanip>

#include <nlohmann/json.hpp>

#include "timeStamp.h"
#include "coredata.h"
#include "setting.h"

using json = nlohmann::json;

using namespace std;
  
class t_managerDft //: public t_coredata
{
   
   typedef map<double, double> m_dd;
   typedef map<string, double> m_td;
   
 public:
   
   ///   Constructor
   t_managerDft( t_setting  * setting,  
	      t_coredata * coredata);
   
   ///   Destructor   
   virtual ~t_managerDft(){};
   
 protected:
   
   void _procDft();
   
   m_dd _data;
   m_td _Data;
   
   string _out;
   string _hst;   
   string _fmt;   
   string _gnp;   
   string _plot;
   
   double _res;
   
   bool _conv;
};
#endif