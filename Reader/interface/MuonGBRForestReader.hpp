#ifndef MuonGBRForestReader_hpp
#define MuonGBRForestReader_hpp

#include <vector>
#include <TROOT.h>
#include <iostream>

#include "FWCore/ParameterSet/interface/FileInPath.h"
#include "CommonTools/MVAUtils/interface/GBRForestTools.h"

using namespace std;
using namespace edm;

class MuonGBRForestReader
{
   public:
   
      MuonGBRForestReader( int );
      MuonGBRForestReader( int, int );
      ~MuonGBRForestReader();
      
      float Get_MVA_value( float, float, float, float, float, float, float, float, float, float, float, float, float );
      float Get_MVA_value_two_eta_bins( float, float, float, float, float, float, float, float, float, float );
    
   private:
         
      FileInPath fip_pT_5_, fip_pT_10_;
      FileInPath fip_B_pT_5_, fip_B_pT_10_, fip_E_pT_5_, fip_E_pT_10_;
      
      string weights_pT_5_, weights_pT_10_;
      string weights_B_pT_5_, weights_B_pT_10_, weights_E_pT_5_, weights_E_pT_10_;
            
      GBRForestTools model_;
      
      vector<float> vars_;
      
      vector<unique_ptr<const GBRForest> > gbrForests_;
};

#endif
