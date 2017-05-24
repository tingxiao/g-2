{
  gROOT->Reset();
  gROOT->SetStyle("Plain");

  TFile f("test.root");
  f.cd("DumpDecayTreeProc");
  h1->Draw();
  c1->Print("babayaga.ps(");

  h2->Draw();
  c1->Print("babayaga.ps");

  h3->Draw();
  c1->Print("babayaga.ps");

  h4->Draw();
  c1->Print("babayaga.ps");

  h5->Draw();
  c1->Print("babayaga.ps");

  h6->Draw();
  c1->Print("babayaga.ps");

  h7->Draw();
  c1->Print("babayaga.ps");

  h8->Draw();
  c1->Print("babayaga.ps");

  h9->Draw();
  c1->Print("babayaga.ps");

  h10->Draw();
  c1->Print("babayaga.ps");

  h11->Draw();
  c1->Print("babayaga.ps");

  h12->Draw();
  c1->Print("babayaga.ps");

  h13->Draw();
  c1->Print("babayaga.ps");

  h14->Draw();
  c1->Print("babayaga.ps");

  h15->Draw();
  c1->Print("babayaga.ps");

  h16->Draw();
  c1->Print("babayaga.ps)");

}
