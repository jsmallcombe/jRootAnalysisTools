{
    const Int_t ndim = 5;
    const Int_t nbins = 20;
    const Int_t npoints = 1'000'000;

    // Define binning: 20 bins from 0 to 1 for each dimension
    Int_t bins[ndim];
    Double_t xmin[ndim];
    Double_t xmax[ndim];
    for (Int_t i = 0; i < ndim; ++i) {
        bins[i] = nbins;
        xmin[i] = 0.0;
        xmax[i] = 1.0;
    }

    // Create THnI
    THnI* hist = new THnI("h6d", "<=6D Integer Histogram", ndim, bins, xmin, xmax);

    // Random number generator
    TRandom3 rng(0); // Seeded with 0 for reproducibility

    // Temporary array to hold the coordinates
    Double_t coords[6];

    for (Int_t i = 0; i < npoints; ++i) {
        Double_t r = rng.Uniform(0, 1);

        // Generate different basic functions for each dimension
        coords[0] = r;                 // uniform
        coords[1] = r * r;             // quadratic
        coords[2] = sqrt(r);           // square root
        coords[3] = sin(r * TMath::Pi()/2); // sine-like
        coords[4] = exp(-r);           // exponential decay
        coords[5] = fabs(cos(r * TMath::Pi())); // absolute cosine

        hist->Fill(coords);
    }

    
    new jGatingToolTHnMany(hist);
}
