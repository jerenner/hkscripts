#include <stdio.h>
#include <stdlib.h>

void read_PMT(char *filename=NULL) {

  /* MODIFIED FROM:
   * https://github.com/WCTE/WCSim/blob/nuPRISM/develop/sample-root-scripts/read_PMT.C
   */

  gROOT->Reset();
  char* wcsimdirenv;
  wcsimdirenv = getenv ("WCSIMDIR");
  if(wcsimdirenv !=  NULL){
    gSystem->Load("${WCSIMDIR}/libWCSimRoot.so");
  }else{
    gSystem->Load("../libWCSimRoot.so");
  }
  gStyle->SetOptStat(1);

  TFile *f;
  if (filename==NULL){
    f = new TFile("../wcsim.root");
  }else{
    f = new TFile(filename);
  }
  if (!f->IsOpen()){
    cout << "Error, could not open input file: " << filename << endl;
    return -1;
  }

  TTree  *wcsimT = f->Get("wcsimT");
  TTree  *wcsimGeoT = f->Get("wcsimGeoT");

  // Get the number of PMTs from the geometry branch.
  WCSimRootGeom *wcsimrootgeom = new WCSimRootGeom();
  wcsimGeoT->SetBranchAddress("wcsimrootgeom",&wcsimrootgeom);
  wcsimGeoT->GetEvent(0);
  int npmts = wcsimrootgeom->GetWCNumPMT();


  // Create a vector that will hold information for each PMT.
  vector<int> vpmts;
  ofstream outfile;
  outfile.open("nuPRISMShort_mPMT_hits_9MeV_100k.dat");
  outfile << "evt ntriggers ";
  for(int ipmt = 0; ipmt < npmts; ipmt++) {
    outfile << "pmt" << ipmt+1 << " ";
    vpmts.push_back(0);
  }
  outfile << endl;
  cout << "An array of size " << vpmts.size() << endl;

  WCSimRootEvent *wcsimrootsuperevent = new WCSimRootEvent();
  wcsimT->SetBranchAddress("wcsimrootevent",&wcsimrootsuperevent);

  // Force deletion to prevent memory leak when issuing multiple
  // calls to GetEvent()
  wcsimT->GetBranch("wcsimrootevent")->SetAutoDelete(kTRUE);
  cout << "Number of entries: " << wcsimT->GetEntries() << "\n";

  // Loop over all events and record the hits.
  for(int ievt = 0; ievt < wcsimT->GetEntries(); ievt++) {

    // Get the entry in the TTree.
    wcsimT->GetEvent(ievt);

    cout << "-------------------------------------------------------------------" << endl;
    cout << "EVENT " << ievt << endl;
    cout << "Number of triggers " << wcsimrootsuperevent->GetNumberOfEvents() << endl;
    WCSimRootTrigger *wcsimrootevent = wcsimrootsuperevent->GetTrigger(0);
    //--------------------------
    // As you can see, there are lots of ways to get the number of hits.
    cout << "Number of tube hits " << wcsimrootevent->GetNumTubesHit() << endl;
    cout << "Number of Cherenkov tube hits " << wcsimrootevent->GetNcherenkovhits() << endl;
    cout << "Number of Cherenkov tube hits " << wcsimrootevent->GetCherenkovHits()->GetEntries() << endl;
    cout << "Number of digitized tube hits " << wcsimrootevent->GetNumDigiTubesHit() << endl;
    cout << "Number of digitized Cherenkov tube hits " << wcsimrootevent->GetNcherenkovdigihits() << endl;
    cout << "Number of digitized Cherenkov tube hits " << wcsimrootevent->GetCherenkovDigiHits()->GetEntries() << endl;
    cout << "Number of photoelectron hit times " << wcsimrootevent->GetCherenkovHitTimes()->GetEntries() << endl;
    //-----------------------

    // Print the number of hits in each PMT.
    outfile << ievt << " " << wcsimrootsuperevent->GetNumberOfEvents() << " ";
    cout << "Clearing array for " << npmts << " pmts ..." << endl;
    for(int ipmt = 0; ipmt < npmts; ipmt++) {
      vpmts[ipmt] = 0;
    }
    for(int ihit = 0; ihit < wcsimrootevent->GetNcherenkovhits(); ihit++) {
      WCSimRootCherenkovHit *chit = wcsimrootevent->GetCherenkovHits()->At(ihit);
      //cout << "Filling array for PMT " << chit->GetTubeID() << endl;
      vpmts[chit->GetTubeID()-1] += chit->GetTotalPe(1); // index 0 = time, index 1 = n_pes
    }
    for(int ipmt = 0; ipmt < npmts; ipmt++) {
      outfile << vpmts[ipmt] << " ";
    }
    outfile << endl;
  }
  outfile.close();

  // Geometry summary.
  cout << "----------------------------------------------------------" << endl;
  cout << "GEOMETRY SUMMARY" << endl;
  cout << "----------------------------------------------------------" << endl;
  cout << "Cylinder radius: " << wcsimrootgeom->GetWCCylRadius() << endl;
  cout << "Cylinder length: " << wcsimrootgeom->GetWCCylLength() << endl;
  cout << "# of PMTs: " << wcsimrootgeom->GetWCNumPMT() << endl;
  cout << "PMT radius: " << wcsimrootgeom->GetWCPMTRadius() << endl;
  cout << "----------------------------------------------------------" << endl;

  // Output PMT information to file.
  cout << "Outputting PMT information to file... " << endl;
  ofstream pmtfile;
  pmtfile.open("nuPRISMShort_mPMT_geom.dat");
  pmtfile << "pmt loc x z y dx dz dy" << endl;
  for(int ipmt = 0; ipmt < npmts; ipmt++) {

    WCSimRootPMT pmt = wcsimrootgeom->GetPMT(ipmt);
    pmtfile << pmt.GetTubeNo()    << " " << pmt.GetCylLoc()    << " "
            << pmt.GetPosition(0) << " " << pmt.GetPosition(1) << " " << pmt.GetPosition(2) << " "
            << pmt.GetOrientation(0) << " " << pmt.GetOrientation(1) << " " << pmt.GetOrientation(2) << endl;
  }
  pmtfile.close();
  cout << "DONE." << endl;

}
