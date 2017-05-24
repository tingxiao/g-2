{
   gROOT->Reset();
   gROOT->SetStyle("Plain");
   gStyle->SetOptStat(0);

   TCanvas *c1 = new TCanvas("c1", "c1", 800, 600);
//   c1->SetMargin(0.13,0.13,0.13,0.13);

/*
   Int_t n = 8;
   Double_t x[n], y[n];
   for (Int_t i=0; i<=n; i++) {
      x[i] = exp(i*0.01+0.03);
      y[i] = -80.0*log(x[i])/7+47.0/35;
   }
   TGraph *gr1 = new TGraph (n, x, y);

   gr1->Draw("AC*");
*/

   TF1 f1("func1","-80.0*log(x)/7+47.0/35",exp(0.03),exp(0.1));
//   f1.SetRange(0.03,5);
   f1.Draw();

//   TF1 f2("func2","0.2",exp(0.1),exp(0.25));
//   f2.Draw("same");
//   TF1 f3("func3","1.2*log(x)-0.1",exp(0.25),exp(0.5));
//   f3.Draw("same");









   c1->SetLogx();
}
