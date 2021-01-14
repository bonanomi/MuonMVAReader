#include "MuonMVAReader/Reader/interface/MuonGBRForestReader.hpp"

//================================
MuonGBRForestReader::MuonGBRForestReader( int year )
{

   if ( year == 2016 )
   {
   	fip_pT_5_  = edm::FileInPath("MuonMVAReader/Reader/data/MVAWeightFiles/Summer_16_ID_ISO_SIP/pT_5/weights_formatted.xml");
      fip_pT_10_ = edm::FileInPath("MuonMVAReader/Reader/data/MVAWeightFiles/Summer_16_ID_ISO_SIP/pT_10/weights_formatted.xml");
   }
   else if ( year == 2017 )
   {
   	fip_pT_5_  = edm::FileInPath("MuonMVAReader/Reader/data/MVAWeightFiles/Fall_17_ID_ISO_SIP/pT_5/weights_formatted.xml");
      fip_pT_10_ = edm::FileInPath("MuonMVAReader/Reader/data/MVAWeightFiles/Fall_17_ID_ISO_SIP/pT_10/weights_formatted.xml");
   }
   else if ( year == 2018 )
   {
   	fip_pT_5_  = edm::FileInPath("MuonMVAReader/Reader/data/MVAWeightFiles/Spring_18_ID_ISO_SIP/pT_5/weights_formatted.xml");
      fip_pT_10_ = edm::FileInPath("MuonMVAReader/Reader/data/MVAWeightFiles/Spring_18_ID_ISO_SIP/pT_10/weights_formatted.xml");
   }
   else
   {
      std::cerr << "[ERROR] MuonGBRForestReader: Year " << year << " is currently not supported!" << std::endl;
   }
   
   gbrForests_.push_back(createGBRForest(fip_pT_5_));
   gbrForests_.push_back(createGBRForest(fip_pT_10_));
      
}
//================================


//================================
MuonGBRForestReader::MuonGBRForestReader( int year, int num_of_eta_bins )
{

   if ( year == 2016 )
   {
   	fip_B_pT_5_  = edm::FileInPath("MuonMVAReader/Reader/data/MVAWeightFiles/Summer_16_ID_ISO/B_pT_5/weights_formatted.xml");
      fip_B_pT_10_ = edm::FileInPath("MuonMVAReader/Reader/data/MVAWeightFiles/Summer_16_ID_ISO/B_pT_10/weights_formatted.xml");
   	fip_E_pT_5_  = edm::FileInPath("MuonMVAReader/Reader/data/MVAWeightFiles/Summer_16_ID_ISO/E_pT_5/weights_formatted.xml");
      fip_E_pT_10_ = edm::FileInPath("MuonMVAReader/Reader/data/MVAWeightFiles/Summer_16_ID_ISO/E_pT_10/weights_formatted.xml");
   }
   else if ( year == 2017 )
   {
   	fip_B_pT_5_  = edm::FileInPath("MuonMVAReader/Reader/data/MVAWeightFiles/Fall_17_ID_ISO/B_pT_5/weights_formatted.xml");
      fip_B_pT_10_ = edm::FileInPath("MuonMVAReader/Reader/data/MVAWeightFiles/Fall_17_ID_ISO/B_pT_10/weights_formatted.xml");
   	fip_E_pT_5_  = edm::FileInPath("MuonMVAReader/Reader/data/MVAWeightFiles/Fall_17_ID_ISO/E_pT_5/weights_formatted.xml");
      fip_E_pT_10_ = edm::FileInPath("MuonMVAReader/Reader/data/MVAWeightFiles/Fall_17_ID_ISO/E_pT_10/weights_formatted.xml");
   }
   else if ( year == 2018 )
   {
   	fip_B_pT_5_  = edm::FileInPath("MuonMVAReader/Reader/data/MVAWeightFiles/Spring_18_ID_ISO/B_pT_5/weights_formatted.xml");
      fip_B_pT_10_ = edm::FileInPath("MuonMVAReader/Reader/data/MVAWeightFiles/Spring_18_ID_ISO/B_pT_10/weights_formatted.xml");
   	fip_E_pT_5_  = edm::FileInPath("MuonMVAReader/Reader/data/MVAWeightFiles/Spring_18_ID_ISO/E_pT_5/weights_formatted.xml");
      fip_E_pT_10_ = edm::FileInPath("MuonMVAReader/Reader/data/MVAWeightFiles/Spring_18_ID_ISO/E_pT_10/weights_formatted.xml");
   }
   else
   {
      std::cerr << "[ERROR] MuonGBRForestReader: Year " << year << " is currently not supported!" << std::endl;
   }
   
   gbrForests_.push_back(createGBRForest(fip_B_pT_5_));
   gbrForests_.push_back(createGBRForest(fip_B_pT_10_));
   gbrForests_.push_back(createGBRForest(fip_E_pT_5_));
   gbrForests_.push_back(createGBRForest(fip_E_pT_10_));
      
}
//================================




//=================================
MuonGBRForestReader::~MuonGBRForestReader(){}
//=================================


//============================================================================================================================================================================
float MuonGBRForestReader::Get_MVA_value( float mu_pT, float mu_eta, float mu_N_hits, float mu_N_pixel_hits, float mu_N_tracker_hits, float mu_chi_square, float mu_pf_photon_iso,
                                          float mu_pf_charged_had_iso, float mu_pf_neutral_had_iso, float mu_rho, float mu_sip, float mu_dxy, float mu_dz )
{  
   vars_.clear();

	vars_.push_back(mu_eta);
	vars_.push_back(mu_N_hits);
	vars_.push_back(mu_N_pixel_hits);
	vars_.push_back(mu_N_tracker_hits);
	vars_.push_back(mu_chi_square);
	vars_.push_back(mu_pf_photon_iso);
	vars_.push_back(mu_pf_charged_had_iso);
	vars_.push_back(mu_pf_neutral_had_iso);
	vars_.push_back(mu_rho);
	vars_.push_back(mu_sip);
	vars_.push_back(mu_dxy);
	vars_.push_back(mu_dz);
	
   if ( mu_pT < 10)
   {
  		return gbrForests_.at(0)->GetResponse(vars_.data());
   }
   else
   {
  		return gbrForests_.at(1)->GetResponse(vars_.data());
   }

}
//============================================================================================================================================================================


//============================================================================================================================================================================
float MuonGBRForestReader::Get_MVA_value_two_eta_bins( float mu_pT, float mu_eta, float glb_valid_mu_hits, float glb_chi2, float tk_valid_pixel_hits, float tk_valid_hits,
                                                       float mu_pf_photon_iso, float mu_pf_charged_had_iso, float mu_pf_neutral_had_iso, float mu_rho )
{  
   vars_.clear();

	vars_.push_back(glb_valid_mu_hits);
   vars_.push_back(glb_chi2);
	vars_.push_back(tk_valid_pixel_hits);
	vars_.push_back(tk_valid_hits);
	vars_.push_back(mu_pf_photon_iso);
	vars_.push_back(mu_pf_charged_had_iso);
	vars_.push_back(mu_pf_neutral_had_iso);
	vars_.push_back(mu_rho);
	
	
   if ( mu_pT < 10 && abs(mu_eta) < 1.2 )
   {
  		return gbrForests_.at(0)->GetResponse(vars_.data());
   }
   else if ( mu_pT >= 10 && abs(mu_eta) < 1.2 )
   {
      return gbrForests_.at(1)->GetResponse(vars_.data());
   }
   else if ( mu_pT < 10 && abs(mu_eta) >= 1.2 )
   {
  		return gbrForests_.at(2)->GetResponse(vars_.data());
   }
   else
   {
      return gbrForests_.at(3)->GetResponse(vars_.data());
   }

}
//============================================================================================================================================================================
