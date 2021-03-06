/************************************************************************************************** 
 Casper - software development library
  
 (c) 2020 Michal Elias
  
 This file is part of the Casper C++ library.
  
 This library is free software; you can redistribute it and/or  modify it under the terms of the GNU
 General Public License as  published by the Free Software Foundation; either version 3 of the 
 License, or (at your option) any later version.
  
 This library is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without 
 even the implied warranty of  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 General Public License for more details.
  
 You should have received a copy of the GNU General Public License  along with this program; if not,
 see <http://www.gnu.org/licenses>.
***************************************************************************************************/

#include <stdio.h>
#include <iostream>
#include <string>
#include <ctime>
#include <time.h>

#include "newmat/newmat.h"
#include "logger.hpp"
#include "casper.h"
#include "load.h"
#include "coredata.h"
#include "version.h"
#include "help.h"
#include "timeStamp.h"
#include "setting.h"

#include "managerDft.h"
#include "managerSpectrogram.h"

using json = nlohmann::json;

using namespace std;

const char* const COMPILED = __DATE__ " @ " __TIME__;

int main(int argc, char ** argv)
{
  
  LOG1(":.main::*** Software: Casper (app started) ");
  time_t now = time(0); tm* localtm = localtime(&now);
  clock_t start = clock();
  
  /// Set&Get Version
  t_version version("0","0","1", "alpha");
  LOG1(":.main::*** Version: " , version.Version());
  LOG1(":.main::*** Compiled: ", COMPILED);
  
  /// Get Settig
  t_setting * setting = new t_setting();
  if(setting != NULL){ 
    
    LOG1(":.main::...Loaded configuration file"); 
  }
  else {
    
    ERR(":.main::...Problem with configuration file loading!");
  }
  
  vector <string> loadSetting = setting->getLoadSetting();
  string inputName = loadSetting[0];
  string inputFormat = loadSetting[2];
  
  string outputName = setting->getOutputName();
  string outputHist = setting->getOutputHist();
  string dftOnOff = setting->getDftOnOff();
  string spectrogramOnOff = setting->getSpectrogramOnOff();
  
  bool convTdDd = setting->getInputConvTdDd(); //cout << convTdDd << endl;
  
  remove(outputName.c_str()); ofstream ofile; ofile.open(outputName.c_str(), ios::out | ios::app);
  remove(outputHist.c_str()); ofstream hfile; hfile.open(outputHist.c_str(), ios::out | ios::app);
  
  /// History
  
  /// Casper::DATA LOADING
  t_load load(setting);
  
  map<double, double>  testval;
  map<string, double> Testval;

  if ( inputFormat == "dd" ) {

    testval = load.getTestval();
  }
  else if ( inputFormat == "td" ) {
    
    if (convTdDd) {
      
      Testval = load.getTimeTestval();
    }
    else {
      
      testval = load.getTestval();
    }
  }
  else {  }
  
  /// Casper::SET LOG FILE
  if(!testval.empty() || !Testval.empty()) {
    
    LOG1(":.main::...Loaded data file");
    if(inputFormat == "dd") {
       
      LOG1(":.main::...Data container size: ", testval.size());
    }
    else if(inputFormat == "td" && convTdDd == true) {
       
      LOG1(":.main::...Data container size: ", Testval.size()); 
     }
    else if(inputFormat == "td" && convTdDd == false) {
       
      LOG1(":.main::...Data container size: ", testval.size()); 
    }    
     else{ 
       
       ERR(":.main::...Input data format %s is not supported: ", inputFormat); return -1; 
     }
   }
  else {
    
    ERR(":.main::...Data container is empty!"); return -1; 
  }
  
  /// Casper::DATA Filling to the coredata class
  ofile << "# Software: Casper\n";
  ofile << "# Version: " << version.Version() << "\n";
  ofile << "# ----------------\n";
  ofile << "# Protocol created: " << asctime(localtm) << endl;
  
  /// Casper::Copy pointers into the coredata object.   TU MAM ASI PROBLEM S ROZHODOVANIM
  if (inputFormat == "dd") {
  
    /// Pointer
    t_coredata * coredata = new t_coredata(testval);
    
    /// Log
    if(coredata != NULL){
      
      LOG1(":.main::...Pointer to coredata obj.");
    }

    /// Casper::Call Applications
    if (dftOnOff == "on") {
      
      LOG1(":.main::...Request for DFT (Discrete Fourier Transformation)"); new t_managerDft(setting, coredata);
    }
    
    if (spectrogramOnOff == "on") {
      
      LOG1(":.main::...Request for Spectrogram"); new t_managerSpectrogram(setting, coredata);
    }

    /// Delete
    if ( coredata ) delete coredata ;
  }
  else if (inputFormat == "td") {
    
    /// Pointer
    t_coredata * Coredata = new t_coredata(Testval);
    t_coredata * coredata = new t_coredata(testval);
    
    /// Log
    if(Coredata != NULL) {
      
      LOG1(":.main::...Pointer to Coredata obj.");
    }
    
    /// Casper::Call Applications
    if ( convTdDd ) {

      if (dftOnOff == "on") { 
        
        LOG1(":.main::...Request for DFT (Discrete Fourier Transformation)"); new t_managerDft(setting, Coredata);
      }
      
      if (spectrogramOnOff == "on") {
        
        LOG1(":.main::...Request for Spectrogram"); new t_managerSpectrogram(setting, Coredata);
      }
    
    }
    else {
      
      if (dftOnOff == "on") { 
        
        LOG1(":.main::...Request for DFT (Discrete Fourier Transformation)"); new t_managerDft(setting, coredata);
      }
      
      if (spectrogramOnOff == "on") {
        
        LOG1(":.main::...Request for Spectrogram"); new t_managerSpectrogram(setting, coredata);
      }
    }
    
    /// Delete
    if ( Coredata ) delete Coredata ;
    if ( coredata ) delete coredata ;
    
  }
  else { 
    
    ERR(":.main::...Requested input data format is not supported!");
  }
  
  /// Clear/Close/Delete
  LOG1(":.main::...Clear/Close/Delete");
  testval.clear();
  Testval.clear();
  
  ofile.close();
  hfile.close();
  
  if ( setting  ) delete setting  ;
  
  /// Casper::Finish
  clock_t stop = clock();
  double duration = double(stop - start) / CLOCKS_PER_SEC;
   
  LOG1(":.main::*** Casper (app finished)");
  LOG1(":.main::*** TOTAL TIME TAKEN: ", duration, " [s]!");
  
   // Version
   if(argc == 2 && strcmp(argv[1], "--version")==0) {
      cout << "\n\nCasper [--version]: " << version.Version() << endl;
   }   
   
   // help
   if(argc == 2 && strcmp(argv[1], "--help")==0) {
      cout << "\n\nCasper [--help]\n" <<endl;
      t_help lh; lh.lokiHelp();
   }
  
  return 0;
}
