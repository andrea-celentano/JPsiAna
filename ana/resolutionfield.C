#define N 5
resolutionfield(){
  double B[5]={1.,2./3.,0.5,1./3.,0.25};
  double resJ[5]={14.9,21.8,28.8,43.0,57.0};
  double resP[5]={27.9,38.9,51.1,75.9,100.0};

  
  TGraph *gJ=new TGraph(5,B,resJ);
  TGraph *gP=new TGraph(5,B,resP);

  TCanvas *c1=new TCanvas();
  gJ->SetMarkerStyle(20);gJ->Draw("AP");
  gJ->SetTitle(";B_{0}/B;#sigma_{M} (MeV)");
  TCanvas *c2=new TCanvas();
  gP->SetMarkerStyle(20);gP->Draw("AP");
  gP->SetTitle(";B_{0}/B;#sigma_{MM} (MeV)");





}
