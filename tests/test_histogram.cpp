
#include "catch.hpp"
#include "histogram.hpp"

TEST_CASE("Create histogram class", "[constructor]") {
    
    bool   lflag = false;

    double vmin  = 0.0;
    double vmax  = 1.0;
    double hbins = 0.1;
    int    ibins = 10;
    int    nbins = ibins + 1;

    std::vector<double> data  = { 0.0 };
    std::vector<double> bins  = { 0.0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0 };
    std::vector<int   > count = { 1 };

    SECTION("empty") {
        REQUIRE_NOTHROW( Histogram() );
    }

    SECTION("vmin, vmax and number of bins") {
        REQUIRE_NOTHROW( Histogram(vmin, vmax, ibins, lflag) );

        Histogram hist = Histogram(vmin, vmax, ibins, lflag);
        
        REQUIRE(        hist.GetBinsNum()    == nbins );
        REQUIRE( Approx(hist.GetBinsWidth()) == hbins );
        REQUIRE( Approx(hist.GetVMin())      == vmin  );
        REQUIRE( Approx(hist.GetVMax())      == vmax  );

        REQUIRE( hist.GetBins().size() == nbins );

        for (size_t i = 0; i < hist.GetBinsNum(); ++i)
            REQUIRE( hist.GetBins(i) == Approx(bins[i]) );

        REQUIRE( hist.GetCounts().size() == ibins );

        for (size_t i = 0; i < ibins; ++i)
            REQUIRE( hist.GetCounts(i) == 0 );
    }

    SECTION("vmin, vmax and size of bins") {
        REQUIRE_NOTHROW( Histogram(vmin, vmax, hbins, lflag) );

        Histogram hist = Histogram(vmin, vmax, hbins, lflag);

        REQUIRE(        hist.GetBinsNum()    == nbins );
        REQUIRE( Approx(hist.GetBinsWidth()) == hbins );
        REQUIRE( Approx(hist.GetVMin())      == vmin  );
        REQUIRE( Approx(hist.GetVMax())      == vmax  );

        REQUIRE( hist.GetBins().size() == nbins );

        for (size_t i = 0; i < hist.GetBinsNum(); ++i)
            REQUIRE( hist.GetBins(i) == Approx(bins[i]) );

        REQUIRE( hist.GetCounts().size() == ibins );

        for (size_t i = 0; i < ibins; ++i)
            REQUIRE( hist.GetCounts(i) == 0 );
    }

    SECTION("pre-calculated bins") {
        REQUIRE_NOTHROW( Histogram(bins) );

        Histogram hist = Histogram(bins);

        REQUIRE(        hist.GetBinsNum()    == nbins );
        REQUIRE( Approx(hist.GetBinsWidth()) == hbins );
        REQUIRE( Approx(hist.GetVMin())      == vmin  );
        REQUIRE( Approx(hist.GetVMax())      == vmax  );

        REQUIRE( hist.GetBins().size() == nbins );

        for (size_t i = 0; i < hist.GetBinsNum(); ++i)
            REQUIRE( hist.GetBins(i) == Approx(bins[i]) );

        REQUIRE( hist.GetCounts().size() == ibins );

        for (size_t i = 0; i < ibins; ++i)
            REQUIRE( hist.GetCounts(i) == 0 );
    }

    SECTION("input values and pre-calculated bins") {
        REQUIRE_NOTHROW( Histogram(data, bins) );

        Histogram hist = Histogram(data, bins);

        REQUIRE(        hist.GetBinsNum()    == nbins );
        REQUIRE( Approx(hist.GetBinsWidth()) == hbins );
        REQUIRE( Approx(hist.GetVMin())      == vmin  );
        REQUIRE( Approx(hist.GetVMax())      == vmax  );

        REQUIRE( hist.GetBins().size() == nbins );

        for (size_t i = 0; i < hist.GetBinsNum(); ++i)
            REQUIRE( hist.GetBins(i) == Approx(bins[i]) );

        REQUIRE( hist.GetCounts().size() == ibins );

        for (size_t i = 0; i < ibins; ++i)
            REQUIRE( hist.GetCounts(i) == count[i] );
    }

    SECTION("input values and vmin, vmax and number of bins") {
        REQUIRE_NOTHROW( Histogram(data, vmin, vmax, ibins, lflag) );

        Histogram hist = Histogram(data, vmin, vmax, ibins, lflag);

        REQUIRE(        hist.GetBinsNum()    == nbins );
        REQUIRE( Approx(hist.GetBinsWidth()) == hbins );
        REQUIRE( Approx(hist.GetVMin())      == vmin  );
        REQUIRE( Approx(hist.GetVMax())      == vmax  );

        REQUIRE( hist.GetBins().size() == nbins );

        for (size_t i = 0; i < hist.GetBinsNum(); ++i)
            REQUIRE( hist.GetBins(i) == Approx(bins[i]) );

        REQUIRE( hist.GetCounts().size() == ibins );

        for (size_t i = 0; i < ibins; ++i)
            REQUIRE( hist.GetCounts(i) == count[i] );
    }

    SECTION("input values and vmin, vmax and size of bins") {
        REQUIRE_NOTHROW( Histogram(data, vmin, vmax, hbins, lflag) );

        Histogram hist = Histogram(data, vmin, vmax, hbins, lflag);

        REQUIRE(        hist.GetBinsNum()    == nbins );
        REQUIRE( Approx(hist.GetBinsWidth()) == hbins );
        REQUIRE( Approx(hist.GetVMin())      == vmin  );
        REQUIRE( Approx(hist.GetVMax())      == vmax  );

        REQUIRE( hist.GetBins().size() == nbins  );

        for (size_t i = 0; i < hist.GetBinsNum(); ++i)
            REQUIRE( hist.GetBins(i) == Approx(bins[i]) );

        REQUIRE( hist.GetCounts().size() == ibins );

        for (size_t i = 0; i < ibins; ++i)
            REQUIRE( hist.GetCounts(i) == count[i] );
    }

}
