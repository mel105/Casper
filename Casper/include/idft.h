#ifndef IDFT_H
#define IDFT_H

/**************************************************************************************************
 @Founder: Michal Elias
 @Linux Ubuntu 18.4.2 LTS
 @Last revision: 2020-02-01 Author: Michal Elias  

 @Details: Method returns results of DFT.
  
 @Reference:
***************************************************************************************************/

#include <iostream>
#include <map>
#include <vector>
#include <algorithm>

#include <nlohmann/json.hpp>

#define G_PI 3.1415926535897932384626433832795028841971

using namespace std;

class t_idft
{
 public:
   
   t_idft(const vector<double> & data);
   virtual ~t_idft(){};

   /*
   void calcMean();
   void calcMode();
   void calcMedian();
   void calc1Qt();
   void calc3Qt();
   void calcIQR();
   void calcSdev();
   void calcVare();
   void calcMinMax();
   double calcQuantile(const double reqQ);
   
   double getMean();
   double getMedian();
   double get1Qt();
   double get3Qt();
   double getIQR();
   double getUPP();
   double getLOW();
   double getSdev();
   double getVare();
   double getMin();
   double getMax();
   double getModeFreq();
   vector<double> getMode();
   */
 protected:
   
   // Functions
   void _setData( const vector<double> & data);
   void _idft();
   
   // Containers
   vector<double> _data;
   vector<double> _re;
   vector<double> _im;
   
   /*
   void _calcMean();
   void _calcMode();
   void _calcMedian();
   void _calc1Qt();
   void _calc3Qt();
   void _calcIQR();
   void _calcSdev();
   void _calcVare();
   void _calcMinMax();
   void _calcQuantile(const double reqQ);
   
   vector<double> _minmax;
   
   double _iqrCnfd;
   double _mean;
   double _median;
   double _1Qt;
   double _3Qt;
   double _iqr;
   double _upp;
   double _low;
   double _sdev;
   double _vare;
   double _min;
   double _max;
   double _quantile;
   double _modeF;
   vector<double> _mode;
   */
};

#endif