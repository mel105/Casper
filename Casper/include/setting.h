#ifndef SETTING_H
#define SETTING_H

/**************************************************************************************************
 @Founder: Michal Elias
 @Linux Ubuntu 18.4.2 LTS
 @Last revision: 2020-02-01 21:35:15 Author: Michal Elias  

 @Brief: Setting
 @Details: Method reads settings from json configuration.
  
 @Reference:
***************************************************************************************************/

#include <iostream>
#include <map>
#include <vector>
#include <algorithm>

#include <nlohmann/json.hpp>

using namespace std;

class t_setting
{
 public:
   
   t_setting();
   virtual ~t_setting(){};
   
   vector <string> getLoadSetting();
   
   string getOutputHist();   
   string getOutputName();
   string getPlotOnOff();
   string getDftOnOff();
   string getSpectrogramOnOff();   
   
   double getInputResolution();
   
   int    getOutMethod();
   int    getInputDataCol();
   
   bool   getInputConvTdDd();
   
 protected:
   
   vector <string> _loadSetting;
   
   string _outputName;
   string _outputHist;
   string _dftOnOff;
   string _spectrogramOnOff;   
   string _plotOnOff;
   
   double _iqrCnfd;   
   double _inputResolution;
   
   int    _inputDataCol;
   
   bool   _inputConvTdDd;
};

#endif