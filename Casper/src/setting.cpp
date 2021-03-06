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

#include "logger.hpp"
#include "casper.h"
#include "setting.h"
#include "workingdir.h"

// constructor
// --------------------
t_setting::t_setting()
{
  /// Get address of current working dir.
  t_workingDir workingDir;  string current_working_dir = workingDir.GetCurrentWorkingDir();
  
  /// Casper Declaration
  t_casper casper;
  
  /// Open configure file casper.json
  casper.OpenFile((current_working_dir + "/Casper/res/casper.json").c_str());
  
  /// Casper::general
  string plotOnOff {casper.getValue<string>({ "general", "plotOnOff"})}; _plotOnOff = plotOnOff;
  
  /// Casper::input
  string inputName {casper.getValue<string>({"input", "inputName"})}; _loadSetting.push_back(inputName);
  string inputFolder {casper.getValue<string>({"input", "inputFolder"})}; _loadSetting.push_back(inputFolder);
  string inputFormat {casper.getValue<string>({"input", "inputFormat"})}; _loadSetting.push_back(inputFormat);
  int inputDataCol {casper.getValue<int>({"input", "inputDataCol"})}; _inputDataCol = inputDataCol;
  bool inputConvTdDd {casper.getValue<bool>({"input", "inputConvTdDd"})}; _inputConvTdDd = inputConvTdDd;
  double inputResolution {casper.getValue<double>({"input", "inputResolution"})}; _inputResolution = inputResolution;
  
  /// Casper::output
  string outputName {casper.getValue<string>({"output", "outputName"})}; _outputName = outputName;
  string outputHist {casper.getValue<string>({"output", "outputHist"})}; _outputHist = outputHist;
  
  /// Casper::dft
  string dftOnOff {casper.getValue<string>({"dft", "dftOnOff"})}; _dftOnOff = dftOnOff;
  
  /// Casper::spectrogram
  string spectrogramOnOff {casper.getValue<string>({"spectrogram", "spectrogramOnOff"})}; _spectrogramOnOff = spectrogramOnOff;
  
  /// Log
  LOG2(":...t_setting::......Folder: ", inputFolder);
  LOG2(":...t_setting::......File: ", inputName);
  LOG2(":...t_setting::......Format: ", inputFormat);
  LOG2(":...t_setting::......Column: ", inputDataCol);   
  LOG2(":...t_setting::......Plot: ", plotOnOff);   
}

// general
string t_setting::getPlotOnOff() { return _plotOnOff; }
// input
vector <string> t_setting::getLoadSetting() { return _loadSetting; }
int t_setting::getInputDataCol() { return _inputDataCol; }
bool t_setting::getInputConvTdDd() { return _inputConvTdDd; }
double t_setting::getInputResolution() { return _inputResolution; }
// output   
string t_setting::getOutputName() { return _outputName; }
string t_setting::getOutputHist() { return _outputHist; }
// dft
string t_setting::getDftOnOff() { return _dftOnOff; }
// spectrogram
string t_setting::getSpectrogramOnOff() { return _spectrogramOnOff; }