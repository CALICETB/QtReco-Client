#include "QCanvasWidget.h"

#include <QPaintEvent>
#include <QResizeEvent>
#include <QMouseEvent>
#include <QVBoxLayout>
#include <TStyle.h>
#include <TGaxis.h>
#include <vector>

QCanvasWidget::QCanvasWidget(QWidget *parent) :
    QWidget(parent)
{
    this->resize(500, 500);
    TCanvas = new QRootCanvas(this);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(TCanvas);

}

//-----------------------------------------------------------------------------------------------

QCanvasWidget::~QCanvasWidget()
{
  delete TCanvas;
}

//-----------------------------------------------------------------------------------------------

void QCanvasWidget::ReverseXAxis(TH2 *h){
    // Remove the current axis
    h->GetXaxis()->SetLabelOffset(999);
    h->GetXaxis()->SetTickLength(0);

    // Redraw the new axis
    gPad->Update();
    TGaxis *newaxis = new TGaxis(gPad->GetUxmax(),
                                 gPad->GetUymin(),
                                 gPad->GetUxmin(),
                                 gPad->GetUymin(),
                                 h->GetXaxis()->GetXmin(),
                                 h->GetXaxis()->GetXmax(),
                                 510,"-");
    newaxis->SetLabelOffset(-0.03);
    newaxis->Draw();
}

//-----------------------------------------------------------------------------------------------

void QCanvasWidget::changeEvent(QEvent * e)
{
    if (e->type() == QEvent::WindowStateChange)
    {
        QWindowStateChangeEvent * event = static_cast< QWindowStateChangeEvent * >(e);
        if ((event->oldState() & Qt::WindowMaximized) || (event->oldState() & Qt::WindowMinimized) || (event->oldState() == Qt::WindowNoState && this->windowState() == Qt::WindowMaximized))
        {
            TCanvas->getCanvas()->Resize();
            TCanvas->getCanvas()->Update();
        }
    }
}

//-----------------------------------------------------------------------------------------------

void QCanvasWidget::Draw(TList *m_list)
{
    emit log("DEBUG", "Drawing Canvas");
    TCanvas->getCanvas()->Clear();
    /*if(strcmp(m_list->GetName(), "T0_Correlation") == 0)
    {
    	const int list_size = m_list->GetSize();
        TCanvas->getCanvas()->DivideSquare(list_size, 0.01, 0.01);
        std::vector<TH2*> h2D(list_size);

        TIter next(m_list);
        TObject *obj;
        int index = 0;

        while((obj = (TObject*)next()))
        {
            if(obj->InheritsFrom(TH2::Class()))
            {
                TCanvas->getCanvas()->cd(index+1);
                h2D[index] = (TH2*)obj;
                if(h2D[index]->GetEntries() > 0)
                    h2D[index]->Draw();
                TCanvas->getCanvas()->Update();
                TCanvas->getCanvas()->Modified();
            }
            index++;
        }
    }
    if(strcmp(m_list->GetName(), "T0_Difference") == 0)
    {
    	const int list_size = m_list->GetSize();
        TCanvas->getCanvas()->DivideSquare(list_size, 0.01, 0.01);
        std::vector<TH1*> h1D(list_size);
        TIter next(m_list);
        TObject *obj;
        int index = 0;

        while((obj = (TObject*)next()))
        {
            if(obj->InheritsFrom(TH1::Class()))
            {
                TCanvas->getCanvas()->cd(index+1);
                h1D[index] = (TH1*)obj;
                if(h1D[index]->GetEntries() > 0)
                    h1D[index]->Draw();
                TCanvas->getCanvas()->Update();
                TCanvas->getCanvas()->Modified();
            }
            index++;
        }
    }
    if(strcmp(m_list->GetName(), "T0_Sum") == 0)
    {
    	const int list_size = m_list->GetSize();
        TCanvas->getCanvas()->DivideSquare(list_size, 0.01, 0.01);
        std::vector<TH2*> h2D(list_size);
        TIter next(m_list);
        TObject *obj;
        int index = 0;

        while((obj = (TObject*)next()))
        {
            if(obj->InheritsFrom(TH2::Class()))
            {
                TCanvas->getCanvas()->cd(index+1);
                h2D[index] = (TH2*)obj;
                if(h2D[index]->GetEntries() > 0)
                    h2D[index]->Draw();
                TCanvas->getCanvas()->Update();
                TCanvas->getCanvas()->Modified();
            }
            index++;
        }
	}*/
    if(strcmp(m_list->GetName(), "NHits_Profile") == 0)
    {
    	const int list_size = m_list->GetSize();
        TCanvas->getCanvas()->DivideSquare(list_size, 0.01, 0.01);
        //TProfile *Prof025;
        TProfile *Prof050;
        TIter next(m_list);
        TObject *obj;
        int index = 0;

        while((obj = (TObject*)next()))
        {
	  /*if(strcmp(obj->GetName(), "NProf_0.25MIP") == 0)
            {
                TCanvas->getCanvas()->cd(index+1);
                Prof025 = (TProfile*)obj;
                Prof025->Draw();
                TCanvas->getCanvas()->Update();
                TCanvas->getCanvas()->Modified();
                index++;
		}*/
            if(strcmp(obj->GetName(), "NProf_0.50MIP") == 0)
            {
                TCanvas->getCanvas()->cd(index+1);
                Prof050 = (TProfile*)obj;
                Prof050->Draw();
                TCanvas->getCanvas()->Update();
                TCanvas->getCanvas()->Modified();
                index++;
            }
        }
    }
    if(strcmp(m_list->GetName(), "NHits_Layer") == 0)
    {
    	const int list_size = m_list->GetSize();
        TCanvas->getCanvas()->DivideSquare(list_size, 0.01, 0.01);
        std::vector<TH1*> hNhits(list_size);
        TIter next(m_list);
        TObject *obj;
        int index = 0;

        while((obj = (TObject*)next()))
        {
            if(obj->InheritsFrom(TH1::Class()))
            {
                TCanvas->getCanvas()->cd(index+1);
                gPad->SetLogy();
                hNhits[index] = (TH1*)obj;
                if(hNhits[index]->GetEntries() > 0)
                    hNhits[index]->Draw();
                TCanvas->getCanvas()->Update();
                TCanvas->getCanvas()->Modified();
                index++;
            }
        }
    }
 if(strcmp(m_list->GetName(), "nHits_Per_Event") == 0)
    {
    	const int list_size = m_list->GetSize();
        TCanvas->getCanvas()->DivideSquare(list_size, 0.01, 0.01);
        std::vector<TH1*> hNhits(list_size);
        TIter next(m_list);
        TObject *obj;
        int index = 0;

        while((obj = (TObject*)next()))
        {
            if(obj->InheritsFrom(TH1::Class()))
            {
                TCanvas->getCanvas()->cd(index+1);
                gPad->SetLogy();
                hNhits[index] = (TH1*)obj;
                if(hNhits[index]->GetEntries() > 0)
                    hNhits[index]->Draw();
                TCanvas->getCanvas()->Update();
                TCanvas->getCanvas()->Modified();
                index++;
            }
        }
    }
 if(strcmp(m_list->GetName(), "MemoryCells") == 0)
    {
    	const int list_size = m_list->GetSize();
        TCanvas->getCanvas()->DivideSquare(list_size, 0.01, 0.01);
        std::vector<TH1*> hNhits(list_size);
        TIter next(m_list);
        TObject *obj;
        int index = 0;

        while((obj = (TObject*)next()))
        {
            if(obj->InheritsFrom(TH1::Class()))
            {
                TCanvas->getCanvas()->cd(index+1);
                gPad->SetLogy();
                hNhits[index] = (TH1*)obj;
                if(hNhits[index]->GetEntries() > 0)
                    hNhits[index]->Draw();
                TCanvas->getCanvas()->Update();
                TCanvas->getCanvas()->Modified();
                index++;
            }
        }
    }
    if(strcmp(m_list->GetName(), "Energy_Sum") == 0)
    {
    	const int list_size = m_list->GetSize();
        TCanvas->getCanvas()->DivideSquare(list_size, 0.01, 0.01);
        std::vector<TH1*> h1D(list_size);
        TIter next(m_list);
        TObject *obj;
        int index = 0;

        while((obj = (TObject*)next()))
        {
            if(obj->InheritsFrom(TH1::Class()))
            {
                TCanvas->getCanvas()->cd(index+1);
                h1D[index] = (TH1*)obj;
                if(h1D[index]->GetEntries() > 0)
		  {
		    h1D[index]->SetFillColor(kBlue);
		    h1D[index]->SetFillStyle(3002);
		    //h1D[index]->Set
                    h1D[index]->Draw();
		  }
                TCanvas->getCanvas()->Update();
                TCanvas->getCanvas()->Modified();
            }
            index++;
        }
    }
    /*if(strcmp(m_list->GetName(), "EnergyPerLayer") == 0)
    {
    	const int list_size = m_list->GetSize();
        TCanvas->getCanvas()->DivideSquare(list_size, 0.01, 0.01);
        std::vector<TH1*> h1D(list_size);
        TIter next(m_list);
        TObject *obj;
        int index = 0;

        while((obj = (TObject*)next()))
        {
            if(obj->InheritsFrom(TH1::Class()))
            {
                TCanvas->getCanvas()->cd(index+1);
                h1D[index] = (TH1*)obj;
                if(h1D[index]->GetEntries() > 0)
		  {
		    h1D[index]->SetFillColor(kBlue);
		    h1D[index]->SetFillStyle(3002);
                    h1D[index]->Draw();
		  }
                TCanvas->getCanvas()->Update();
                TCanvas->getCanvas()->Modified();
            }
            index++;
        }
    }*/
    if(strcmp(m_list->GetName(), "Shower") == 0)
    {
    	const int list_size = m_list->GetSize();
        TCanvas->getCanvas()->DivideSquare(list_size, 0.01, 0.01);
        std::vector<TH1*> h1D(list_size);
        std::vector<TH2*> h2D(list_size);
        TIter next(m_list);
        TObject *obj;
        int index = 0;

        while((obj = (TObject*)next()))
        {
            if(obj->InheritsFrom(TH1::Class()))
            {
                TCanvas->getCanvas()->cd(index+1);
                h1D[index] = (TH1*)obj;
                if(h1D[index]->GetEntries() > 0)
		  {
		    h1D[index]->SetFillColor(kBlue);
		    h1D[index]->SetFillStyle(3002);
                    h1D[index]->Draw();
		  }
                TCanvas->getCanvas()->Update();
                TCanvas->getCanvas()->Modified();
            }
            if(obj->InheritsFrom(TH2::Class()))
            {
                TCanvas->getCanvas()->cd(index+1);
                h2D[index] = (TH2*)obj;
                if(h2D[index]->GetEntries() > 0)
                    h2D[index]->Draw("COLZ");
                TCanvas->getCanvas()->Update();
                TCanvas->getCanvas()->Modified();
            }
            index++;
        }
    }
if(strcmp(m_list->GetName(), "EnergyLayer") == 0)
    {
    	const int list_size = m_list->GetSize();
        TCanvas->getCanvas()->DivideSquare(list_size, 0.01, 0.01);
        std::vector<TH1*> h1D(list_size);
        TIter next(m_list);
        TObject *obj;
        int index = 0;

        while((obj = (TObject*)next()))
        {
            if(obj->InheritsFrom(TH1::Class()))
            {
                TCanvas->getCanvas()->cd(index+1);
                h1D[index] = (TH1*)obj;
                if(h1D[index]->GetEntries() > 0)
		  {
		    h1D[index]->SetFillColor(kBlue);
		    h1D[index]->SetFillStyle(3002);
                    h1D[index]->Draw();
		  }
                TCanvas->getCanvas()->Update();
                TCanvas->getCanvas()->Modified();
            }
            index++;
        }
    }
    if(strcmp(m_list->GetName(), "EnergyPerChannel") == 0)
    {

    	const int list_size = m_list->GetSize();
        TCanvas->getCanvas()->DivideSquare(list_size, 0.01, 0.01);
        std::vector<TH1*> EChannel(list_size);
        TIter next(m_list);
        TObject *obj;
        int index = 0;

        while((obj = (TObject*)next()))
        {
            if(obj->InheritsFrom(TH1::Class()))
            {
                TCanvas->getCanvas()->cd(index+1);
                gPad->SetLogy();
                EChannel[index] = (TH1*)obj;
                if(EChannel[index]->GetEntries() > 0) EChannel[index]->Draw();
                TCanvas->getCanvas()->Update();
                TCanvas->getCanvas()->Modified();
                index++;
            }
        }
    }
    if(strcmp(m_list->GetName(), "HitMap") == 0)
    {
    	const int list_size = m_list->GetSize();
        TCanvas->getCanvas()->DivideSquare(list_size, 0.01, 0.01);
        std::vector<TH2*> h2D(list_size);
        TIter next(m_list);
        TObject *obj;
        int index = 0;

        while((obj = (TObject*)next()))
        {
            if(obj->InheritsFrom(TH2::Class()))
            {
                TCanvas->getCanvas()->cd(index+1);
                h2D[index] = (TH2*)obj;
                if(h2D[index]->GetEntries() > 0)
		  {
		    //gPad->SetLogz();
                    h2D[index]->Draw("colz");
                    h2D[index]->SetContour(99);
		    this->ReverseXAxis(h2D[index]);
		  }
                TCanvas->getCanvas()->Update();
                TCanvas->getCanvas()->Modified();
            }
            index++;
        }
    }
    if(strcmp(m_list->GetName(), "HitMap_Energy") == 0)
    {
    	const int list_size = m_list->GetSize();
        TCanvas->getCanvas()->DivideSquare(list_size, 0.01, 0.01);
        std::vector<TH2*> h2D(list_size);
        TIter next(m_list);
        TObject *obj;
        int index = 0;

        while((obj = (TObject*)next()))
        {
            if(obj->InheritsFrom(TH2::Class()))
            {
                TCanvas->getCanvas()->cd(index+1);
                h2D[index] = (TH2*)obj;
                if(h2D[index]->GetEntries() > 0)
		  {
		    //gPad->SetLogz();
                    h2D[index]->Draw("colz");
                    h2D[index]->SetContour(99);
		    this->ReverseXAxis(h2D[index]);
		  }
                TCanvas->getCanvas()->Update();
                TCanvas->getCanvas()->Modified();
            }
            index++;
        }
    }
    if(strcmp(m_list->GetName(), "HitMap_Log") == 0)
    {
    	const int list_size = m_list->GetSize();
        TCanvas->getCanvas()->DivideSquare(list_size, 0.01, 0.01);
        std::vector<TH2*> h2D(list_size);
        TIter next(m_list);
        TObject *obj;
        int index = 0;

        while((obj = (TObject*)next()))
        {
            if(obj->InheritsFrom(TH2::Class()))
            {
                TCanvas->getCanvas()->cd(index+1);
                h2D[index] = (TH2*)obj;
                if(h2D[index]->GetEntries() > 0)
		  {
		    gPad->SetLogz();	    
                    h2D[index]->Draw("colz");
                    h2D[index]->SetMinimum(1);
                    h2D[index]->SetContour(99);
		    this->ReverseXAxis(h2D[index]);
		  }
                TCanvas->getCanvas()->Update();
                TCanvas->getCanvas()->Modified();
            }
            index++;
        }
    }
    if(strcmp(m_list->GetName(), "RMSPerChannel") == 0)
    {
    	const int list_size = m_list->GetSize();
        TCanvas->getCanvas()->DivideSquare(list_size, 0.01, 0.01);
        std::vector<TGraph*> graph(list_size);
        TIter next(m_list);
        TObject *obj;
        int index = 0;
        //TMultiGraph *multi = new TMultiGraph();
        while((obj = (TObject*)next()))
        {
            if(obj->InheritsFrom(TGraph::Class()))
            {
	      //TGraph[index] = (TGraphErrors*)obj;
	      //multi->Add(TGraph[index]); 
             
	      TCanvas->getCanvas()->cd(index+1);
	      //gPad->SetLogy();
	      graph[index] = (TGraph*)obj;
	      graph[index]->SetMarkerSize(0.3);
	      graph[index]->Draw("AP");
	      TCanvas->getCanvas()->Update();
	      TCanvas->getCanvas()->Modified();
	      index++;
            }
            //index++;
        }
        /*TCanvas->getCanvas()->cd();
        multi->Draw("AP");
        //multi->GetXaxis()->SetTitle("Channel Number");
        //multi->GetYaxis()->SetTitle("RMS [MIP]");
        TCanvas->getCanvas()->Update();
        TCanvas->getCanvas()->Modified();*/
    }
    /*if(strcmp(m_list->GetName(), "Temperature") == 0)
    {
    	const int list_size = m_list->GetSize();

        TCanvas->getCanvas()->DivideSquare(list_size, 0.01, 0.01);

        std::vector<TGraphErrors*> TGraph(list_size);
        TIter next(m_list);
        TObject *obj;
        int index = 0;

        TMultiGraph *multi = new TMultiGraph();

        while((obj = (TObject*)next()))
        {
            if(obj->InheritsFrom(TGraphErrors::Class()))
            {
                TGraph[index] = (TGraphErrors*)obj;
                multi->Add(TGraph[index]);
            }
            index++;
        }

        TCanvas->getCanvas()->cd();
        multi->Draw("AP");
        multi->GetXaxis()->SetTitle("Measure in a Run");
        multi->GetYaxis()->SetTitle("Temperature [degrees]");
        multi->GetYaxis()->SetRangeUser(20., 70.);
        TCanvas->getCanvas()->Update();
        TCanvas->getCanvas()->Modified();
	}*/
if(strcmp(m_list->GetName(), "nHitscogZ") == 0)
    {
    	const int list_size = m_list->GetSize();
        TCanvas->getCanvas()->DivideSquare(list_size, 0.01, 0.01);
        std::vector<TH2*> h2D(list_size);
        TIter next(m_list);
        TObject *obj;
        int index = 0;

        while((obj = (TObject*)next()))
        {
            if(obj->InheritsFrom(TH2::Class()))
            {
                TCanvas->getCanvas()->cd(index+1);
                h2D[index] = (TH2*)obj;
                if(h2D[index]->GetEntries() > 0)
		  {
                    h2D[index]->Draw("COLZ");
		    h2D[index]->SetContour(99);
		  }
                TCanvas->getCanvas()->Update();
                TCanvas->getCanvas()->Modified();
            }
            index++;
        }
    }
    if(strcmp(m_list->GetName(), "Hit_Time") == 0)
    {
    	const int list_size = m_list->GetSize();
        TCanvas->getCanvas()->DivideSquare(list_size, 0.01, 0.01);
        std::vector<TH1*> h1D(list_size);
        TIter next(m_list);
        TObject *obj;
        int index = 0;

        while((obj = (TObject*)next()))
        {
            if(obj->InheritsFrom(TH1::Class()))
            {
                TCanvas->getCanvas()->cd(index+1);
                h1D[index] = (TH1*)obj;
                if(h1D[index]->GetEntries() > 0)
		  {
		    h1D[index]->SetFillColor(kBlue);
		    h1D[index]->SetFillStyle(3002);
                    h1D[index]->Draw();
		  }
                TCanvas->getCanvas()->Update();
                TCanvas->getCanvas()->Modified();
            }
            index++;
        }
	}
}
