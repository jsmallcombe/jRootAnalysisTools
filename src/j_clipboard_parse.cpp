#include "j_clipboard_parse.h"

//////// Declarations /////////////

struct ClipboardBufferVectors{
    vector< vector< string > > St;
    vector< vector< double > > Db;
    int W,H;// Minimum dimenstions of Db;
    int MW;// Width longest row of Db;
};
int CopyBufferToVectors(ClipboardBufferVectors &CPY,bool clip=true);
bool ManualStringNumberTest(string s);
bool Transpose(ClipboardBufferVectors &clip);

// Attempt to pass a ClipboardBufferVectors to a ROOT class
// Following a few assumed rules 
TH1* TryCBV2Hist(ClipboardBufferVectors &clip);
TMultiGraph* TryCBV2GraphHeaders(ClipboardBufferVectors &clip);
TGraph* TryCBV2Graph(ClipboardBufferVectors &clip);


///////// Definitions ///////////////

int CopyBufferToVectors(ClipboardBufferVectors &CPY,bool clip){
    stringstream ss;
    
    // Status = 0 if ss sucesfully filled with clipboard data
    int status=ReadX11CopyBufferAsText(ss,clip);
    if(status){return status;}
    
    string line;
    int W=0;
    int MW=0;
    while(getline(ss,line)){
        vector< string > StringVecRow;
        vector< double > DoubleVecRow;
        
        // Replace all commas so data is white space delimited 
        std::replace(line.begin(),line.end(),',', ' '); 
        
        // Some copied text from chrome included weird whitespace that wasnt whitespace
        // Manually whitespace and negative ascii charaters
        int i=0;
        for(auto c:line){
            if((int)c<0)line[i]=' ';
            i++;
        }
        
        stringstream ssline;
        ssline<<line;
        string entry;
        int s=0;
        while(ssline>>entry){
            if(ManualStringNumberTest(entry)){
                stringstream ssentry;
                ssentry<<entry;
                double DEntry;
                ssentry>>DEntry;
                DoubleVecRow.push_back(DEntry);
                s++;
            }else{
                StringVecRow.push_back(entry);
            }
        }
        
        // Only add rows containing data
        if(StringVecRow.size()) CPY.St.push_back(StringVecRow);
        if(s){
            CPY.Db.push_back(DoubleVecRow);
            if(s<W||W==0)W=s;
            if(s>MW)MW=s;
            // Record the narrowest non-zero row
        }
    }
    
    CPY.H=(signed)CPY.Db.size(); 
    CPY.W=W;
    CPY.MW=MW;
    
    // CPY now contains a double type matrix HxW
    // Some rows will have more than W but non less
    //
    // All strings have also been saved,
    // but matrix size is not constrained to match doubles
    // If values are missing, relative positions are lost

    return 0; // Zero for good data in CPY
}

// There is probably a more robust library for doing this.
bool ManualStringNumberTest(string s){
    vector<char> pass={'.','-','+','(',')','E','e'};
    for(char c : s) {
        if(!isdigit(c)){
            bool except=false;
            for (auto p : pass){
                if(c==p){
                    except=true;
                    break;
                }
            }
            if(!except)return false;
        }
    }
    return true;
}

bool Transpose(ClipboardBufferVectors &clip){
    if(clip.W<=clip.H)return false;
    
    vector< vector< double > > tmp(clip.W,vector< double >(clip.H,0));
    
    // You lose anything that is outside the minimum rectangle
    // And for now we dont bother with text
    for(int i=0;i<clip.W;i++){
        for(int j=0;j<clip.H;j++){
            tmp[i][j]=clip.Db[j][i];
        }
    }
    clip.Db=tmp;
    int w=clip.W;
    clip.W=clip.H;
    clip.H=w;
    clip.MW=w;
    
    return true;  
}


static unsigned int clipbuff_hist_iterator=0;
TH1* TryCBV2Hist(ClipboardBufferVectors &clip){
    if(clip.W<1)return 0; // If no data return;
    if(clip.W<2&&clip.H<20)return 0; // If only one column i.e. no binning specified
                                    // If few rows probably not histogram
    int H=clip.H;
    int W=clip.W;
    double binsep=1;
    int N=H;
    double r1=0;
    double r2=H+1;
    
    if(W>1){ // If X data provided
        
        // Empty bins may be skipped in the data
        // so a single gap between entries may not give true bin size
        // Itterate through all
        bool validbin=true;
        double gap=0;
        for(int i=0;i<H-1;i++){
            double g=clip.Db[i+1][0]-clip.Db[i][0];
            if(g<=0){
                // If data are not in ascending X order, assume not hist data
                validbin=false;
                break;
            }
            if(gap==0)gap=g;
            if(g<gap)gap=g;
        }
        // gap should now be bin size unless NO sequential bin data provided
        
        if(validbin){
            for(int i=0;i<H-1;i++){
                double g=abs(clip.Db[i+1][0]-clip.Db[i][0]);
                double m=g/gap;
                double f=m-round(m);
                
                if(abs(f)>1E-6){//Check all gaps are integer number of bin steps
                    validbin=false;
                    break;
                }
            }
        }
        
        if(!validbin) return 0;
        binsep=gap;
        
        double zero=clip.Db[0][0];
        if((zero-round(zero))<1E-6){
            // Assume X values are bin lower edge
            r1=zero;
            r2=clip.Db[H-1][0]+binsep;
        }else{
            //Assume X values are bin centroid
            r1=zero-binsep*0.5;
            r2=clip.Db[H-1][0]+binsep*0.5;
        }
        
        N=round((r2-r1)/binsep);        
    }

    stringstream ss;
    ss<<"COPYBUFFHIST"<<clipbuff_hist_iterator;
    TH1D* ret=new TH1D(ss.str().c_str(),"COPYBUFFHIST",N,r1,r2);
    
    // Finally load all values and errors if there is a third columb
    for(int i=0;i<H;i++){
        if(W==1){
            ret->SetBinContent(i,clip.Db[i][0]);
        }else{
            int b=ret->GetXaxis()->FindBin(clip.Db[i][0]);
            ret->SetBinContent(b,clip.Db[i][1]);
            if(W>2){
                ret->SetBinError(b,clip.Db[i][2]);
            }
        }
    }
    return ret;
}



TGraph* TryCBV2Graph(ClipboardBufferVectors &clip){
	if(clip.H<2)return 0;// Need some data
    
    // If some (or all)  have >2 columns assume erros are provided 
	TGraph *g=0;
    bool errs=(clip.MW>2&&clip.W>1);
	if(errs){
		g=(TGraph*) new TGraphErrors();
	}else{
		g=(TGraph*) new TGraph();
	}
    
    for(auto& V:clip.Db){
		if(clip.W==1){
            // 1 or more row has only 1 values
            // So assume providing Y values only
			g->SetPoint(g->GetN(),g->GetN(),V[0]);
		}
		if(clip.W>1){
			g->SetPoint(g->GetN(),V[0],V[1]);
		}
		if(errs){
			double dx=0,dy=0;
			if(V.size()==3){
				dy=V[2];
			}else if(V.size()>4){
				dx=V[2];
				dy=V[3];
			}
			// No virtual in TGraph for SetPointError so have to cast back up
			((TGraphErrors*)g)->SetPointError(g->GetN()-1,dx,dy);
		}
	}
	// Note, while some rows may have enough data to be considered erros
	// We only consider erros if ALL rows have at leasy X Y data
	// i.e. we do not consider error inputs possible for Y data only inputs
	
	// Default quicksort by X parameter
	g->Sort();
	return g;
};

TMultiGraph* TryCBV2GraphHeaders(ClipboardBufferVectors &clip){
	if(clip.H<2)return 0;// Need some data
    if(clip.St.size()!=clip.Db.size())return 0;
    // If there is one string per row, assume labels

    // Construct list of labels
	vector< string > grp;
    for(auto& a:clip.St){
		bool unique=true;
        for(auto& g:grp){
            if(a[0].compare(g)==0){
                unique=false;
                break;
            }
        }
		if(unique){
			grp.push_back(a[0]);
		}
	}
    
    // If there are not groups, then return
    int G=grp.size();
    if(G<2||G==clip.H)return 0;
    
    // Make one graph for each group
    vector< TGraph* > coll;

    bool errs=(clip.MW>2&&clip.W>1);// If some (or all) have >2 columns assume erros are provided
    for(int i=0;i<G;i++){
        if(errs){
			coll.push_back(new TGraphErrors());
		}else{
			coll.push_back(new TGraph());
		}
    }
    
    for(int i=0;i<clip.H;i++){
        // Determine which group for this entry
		TGraph *g=0;
		for(int c=0;c<G;c++){
			if(clip.St[i][0].compare(grp[c])==0){
				g=coll[c];
				break;
			}
		}
		
		// Same as TryCBV2Graph
		if(g){
			if(clip.W==1){
				g->SetPoint(g->GetN(),g->GetN(),clip.Db[i][0]);
			}
			if(clip.W>1){
				g->SetPoint(g->GetN(),clip.Db[i][0],clip.Db[i][1]);
			}
			if(errs){
				double dx=0,dy=0;
				if(clip.Db[i].size()==3){
					dy=clip.Db[i][2];
				}else if(clip.Db[i].size()>3){
					dx=clip.Db[i][2];
					dy=clip.Db[i][3];
				}
				((TGraphErrors*)g)->SetPointError(g->GetN()-1,dx,dy);
			}
		}
	}
	
	// Finally build multigraph which takes ownership
	// Set draw options to all be distinct	
	TMultiGraph *ret=new TMultiGraph();
	int col=1;
    for(auto& g: coll){
		g->SetLineColor(col);
		g->SetMarkerColor(col);
		g->SetMarkerStyle(col+19);
		g->Sort();
		ret->Add(g);
		col++;
	}
	
	return ret;
}

TObject* CopyBufferHistOrGraph(bool clip){
    ClipboardBufferVectors CPY;
    int status=CopyBufferToVectors(CPY,clip);
    Transpose(CPY);
    if(status==0){
        // Ordered from most selective input to least
		TMultiGraph* m=TryCBV2GraphHeaders(CPY);
        if(m)return (TObject*)m;
        TH1* h=TryCBV2Hist(CPY);
        if(h)return (TObject*)h;
		TGraph* g=TryCBV2Graph(CPY);
        if(g)return (TObject*)g;
    }
    
    return 0;
}



int DrawFromClipboard(){
    int status=DrawFromClipboard(false);
    if(status) return 2;
    return DrawFromClipboard(true);
}

int DrawFromClipboard(bool clip){
	TObject* ob=CopyBufferHistOrGraph(clip);
	if(ob){
		TClass cl(ob->ClassName());
        
        TCanvas *C1=new TCanvas();
        C1->cd();
		
		if(cl.InheritsFrom("TH1")){
			TH1 *h=(TH1*)ob;
			h->Draw();
            h->SetDirectory(0);
		}
		
		if(cl.InheritsFrom("TMultiGraph")){
			TMultiGraph *m=(TMultiGraph*)ob;
			m->Draw("al");
		}
		
		if(cl.InheritsFrom("TGraph")){
			TGraph *g=(TGraph*)ob;
			g->Draw("al");
		}
        ob->SetBit(kCanDelete);
		
		return 1;
	}
	return 0;
}

    
