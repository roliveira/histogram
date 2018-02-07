
#include "catch.hpp"
#include "histogram.hpp"
#include <iostream>

TEST_CASE("Auxiliary methods", "[methods]") {
    
    int n = 10;

    SECTION("linspace") {
        double vmin = 0.0;
        double vmax = 1.0;
        double h    = (vmax - vmin) / static_cast<double>(n);

        std::vector<double> data = { 
            0.0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9
        };

        std::vector<double> values = linspace(vmin, vmax, n);

        REQUIRE( values.size() == n                );
        REQUIRE( values[0]     == Approx(vmin)     );
        REQUIRE( values[n - 1] == Approx(vmax - h) );

        for (size_t i = 0; i < n; ++i)
            REQUIRE( values[i] == Approx(data[i]) );

    }

    SECTION("logspace") {
        double vmin = 1E-5;
        double vmax = 1E+5;
        double h    = std::pow(10, (std::log10(vmax) - std::log10(vmin)) / static_cast<double>(n));

        std::vector<double> data = { 
            1E-5, 1E-4, 1E-3, 1E-2, 1E-1, 1E+0, 1E+1, 1E+2, 1E+3, 1E+4
        };

        std::vector<double> values = logspace(vmin, vmax, n);

        REQUIRE( values.size() == n                );
        REQUIRE( values[0]     == Approx(vmin)     );
        REQUIRE( values[n - 1] == Approx(vmax / h) );

        for (size_t i = 0; i < n; ++i)
            REQUIRE( values[i] == Approx(data[i]) );

    }

}

TEST_CASE("Create histogram class", "[constructor]") {
    
    bool   lflag = false;

    double vmin  = 0.0;
    double vmax  = 1.0;
    double hbins = 0.1;
    int    nbins = 10;

    std::vector<double> data = { 
        0.77224265,  0.40005010,  0.32294286,  0.37215259,  0.52253506,
        0.51849661,  0.52321738,  0.33406892,  0.56848072,  0.45981289,
        0.25060121,  0.55626617,  0.44365542,  0.42098459,  0.31590726,
        0.78523822,  0.64264556,  0.20051599,  0.52761566,  0.27834114,
        0.63475520,  0.49318732,  0.25481758,  0.63489004,  0.16059695,
        0.68458851,  0.53463049,  0.37353250,  0.26859117,  0.57683818,
        0.20652595,  0.20183588,  0.40907951,  0.35659716,  0.64084558,
        0.25516410,  0.57176050,  0.50683466,  0.37256747,  0.22676771,
        0.34043411,  0.48712379,  0.75479221,  0.43643150,  0.39197303,
        0.64682561,  0.43922042,  0.42657827,  0.61983484,  0.55934382 
    };

    std::vector<double> bins  = { 0.0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0 };
    std::vector<int   > count = {   0,   1,   9,   9,  10,  11,   7,   3,   0,   0      };


    SECTION("empty") {
        REQUIRE_NOTHROW( Histogram() );
    }

    SECTION("vmin, vmax and number of bins") {
        REQUIRE_NOTHROW( Histogram(vmin, vmax, nbins, lflag) );

        Histogram hist = Histogram(vmin, vmax, nbins, lflag);
        
        REQUIRE( hist.GetBinsNum()           == nbins + 1 );
        REQUIRE( hist.GetBins().size()       == nbins + 1 );
        REQUIRE( hist.GetCounts().size()     == nbins     );
        REQUIRE( Approx(hist.GetBinsWidth()) == hbins     );
        REQUIRE( Approx(hist.GetVMin())      == vmin      );
        REQUIRE( Approx(hist.GetVMax())      == vmax      );

        for (size_t i = 0; i < nbins + 1; ++i)
            REQUIRE( hist.GetBins(i) == Approx(bins[i]) );

        for (size_t i = 0; i < nbins; ++i)
            REQUIRE( hist.GetCounts(i) == 0 );
    }

    SECTION("vmin, vmax and size of bins") {
        REQUIRE_NOTHROW( Histogram(vmin, vmax, hbins, lflag) );

        Histogram hist = Histogram(vmin, vmax, hbins, lflag);

        REQUIRE( hist.GetBinsNum()           == nbins + 1 );
        REQUIRE( hist.GetBins().size()       == nbins + 1 );
        REQUIRE( hist.GetCounts().size()     == nbins     );
        REQUIRE( Approx(hist.GetBinsWidth()) == hbins     );
        REQUIRE( Approx(hist.GetVMin())      == vmin      );
        REQUIRE( Approx(hist.GetVMax())      == vmax      );

        for (size_t i = 0; i < nbins + 1; ++i)
            REQUIRE( hist.GetBins(i) == Approx(bins[i]) );

        for (size_t i = 0; i < nbins; ++i)
            REQUIRE( hist.GetCounts(i) == 0 );
    }

    SECTION("pre-calculated bins") {
        REQUIRE_NOTHROW( Histogram(bins) );

        Histogram hist = Histogram(bins);

        REQUIRE( hist.GetBinsNum()           == nbins + 1 );
        REQUIRE( hist.GetBins().size()       == nbins + 1 );
        REQUIRE( hist.GetCounts().size()     == nbins     );
        REQUIRE( Approx(hist.GetBinsWidth()) == hbins     );
        REQUIRE( Approx(hist.GetVMin())      == vmin      );
        REQUIRE( Approx(hist.GetVMax())      == vmax      );

        for (size_t i = 0; i < nbins + 1; ++i)
            REQUIRE( hist.GetBins(i) == Approx(bins[i]) );

        for (size_t i = 0; i < nbins; ++i)
            REQUIRE( hist.GetCounts(i) == 0 );
    }

    SECTION("input values and pre-calculated bins") {
        REQUIRE_NOTHROW( Histogram(data, bins) );

        Histogram hist = Histogram(data, bins);

        REQUIRE( hist.GetBinsNum()           == nbins + 1 );
        REQUIRE( hist.GetBins().size()       == nbins + 1 );
        REQUIRE( hist.GetCounts().size()     == nbins     );
        REQUIRE( Approx(hist.GetBinsWidth()) == hbins     );
        REQUIRE( Approx(hist.GetVMin())      == vmin      );
        REQUIRE( Approx(hist.GetVMax())      == vmax      );

        for (size_t i = 0; i < nbins + 1; ++i)
            REQUIRE( hist.GetBins(i) == Approx(bins[i]) );

        for (size_t i = 0; i < nbins; ++i)
            CHECK( hist.GetCounts(i) == count[i] );
    }

    SECTION("input values and vmin, vmax and number of bins") {
        REQUIRE_NOTHROW( Histogram(data, vmin, vmax, nbins, lflag) );

        Histogram hist = Histogram(data, vmin, vmax, nbins, lflag);

        REQUIRE( hist.GetBinsNum()           == nbins + 1 );
        REQUIRE( hist.GetBins().size()       == nbins + 1 );
        REQUIRE( hist.GetCounts().size()     == nbins     );
        REQUIRE( Approx(hist.GetBinsWidth()) == hbins     );
        REQUIRE( Approx(hist.GetVMin())      == vmin      );
        REQUIRE( Approx(hist.GetVMax())      == vmax      );

        for (size_t i = 0; i < nbins + 1; ++i)
            REQUIRE( hist.GetBins(i) == Approx(bins[i]) );

        for (size_t i = 0; i < nbins; ++i)
            REQUIRE( hist.GetCounts(i) == count[i] );
    }

    SECTION("input values and vmin, vmax and size of bins") {
        REQUIRE_NOTHROW( Histogram(data, vmin, vmax, hbins, lflag) );

        Histogram hist = Histogram(data, vmin, vmax, hbins, lflag);

        REQUIRE( hist.GetBinsNum()           == nbins + 1 );
        REQUIRE( hist.GetBins().size()       == nbins + 1 );
        REQUIRE( hist.GetCounts().size()     == nbins     );
        REQUIRE( Approx(hist.GetBinsWidth()) == hbins     );
        REQUIRE( Approx(hist.GetVMin())      == vmin      );
        REQUIRE( Approx(hist.GetVMax())      == vmax      );

        for (size_t i = 0; i < nbins + 1; ++i)
            REQUIRE( hist.GetBins(i) == Approx(bins[i]) );

        for (size_t i = 0; i < nbins; ++i)
            REQUIRE( hist.GetCounts(i) == count[i] );
    }

}

TEST_CASE("Logarithmic spaced bins", "[logarithm]") {

}

TEST_CASE("Non-equal sized bins", "[non-equal]") {

}

TEST_CASE("Writting histogram distribution", "[output]") {

}

TEST_CASE("Reading histogram distribution", "[input]") {

}

TEST_CASE("Find index of bin", "[index]") {
    
}
