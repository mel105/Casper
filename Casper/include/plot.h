#ifndef PLOT_H
#define PLOT_H

/**************************************************************************************************
 @Founder: Michal Elias
 @Linux Ubuntu 18.4.2 LTS
 @Last revision: 2017-03-06 10:08:45 Author: Michal Elias  

 @Brief: Class contains some basic scripts for figures plotting.
 @Details:
  
 @Reference:
***************************************************************************************************/

#include <map>
#include <vector>
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

class t_plot
{
   
 public:
   
   void acf();     // corelogram
   void line();    // simple line plot
   void tline();
   void magnitude();
   void phase();
   void imagSpec();
   void realSpec();

   
};

#endif