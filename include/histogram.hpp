#ifndef HISTOGRAM_H_
#define HISTOGRAM_H_


#include <vector>
#include <numeric>
#include <fstream>
#include <algorithm>
#include <cmath>


class Histogram {
private:
    bool   log;

    int    bins_num;
    double bins_width;

    double vmin;
    double vmax;

    std::vector<double> bins;
    std::vector<int   > counts;

public:

    // Constructor

    Histogram(void);

    Histogram(double _vmin, double _vmax, int    _bins_num,   bool _log);
    Histogram(double _vmin, double _vmax, double _bins_width, bool _log);

    Histogram(std::vector<double> _bins);
    Histogram(std::vector<double> _values, std::vector<double> _bins);

    Histogram(std::vector<double> _values, double _vmin, double _vmax, int    _bins_num,   bool _log);
    Histogram(std::vector<double> _values, double _vmin, double _vmax, double _bins_width, bool _log);

    // Setters

    void SetValue    (double _value     );
    void SetVMin     (double _vmin      );
    void SetVMax     (double _vmax      );
    void SetBinsWidth(double _bins_width);
    void SetBinsNum  (int    _bins_num  );
    void SetLog      (bool   _flag      );

    void SetValues(std::vector<double> _values);
    void SetBins  (std::vector<double> _bins  );
    void SetCounts(std::vector<int   > _counts);

    // Getters

    double GetVMin     (void);
    double GetVMax     (void);
    double GetBinsWidth(void);
    int    GetBinsNum  (void);
    bool   GetLog      (void);

    std::vector<double> GetBins  (void);
    std::vector<int   > GetCounts(void);

    // Methods
    
    int FindIndex(double _value);
    
    std::vector<double> Linspace(void);
    std::vector<double> Logspace(void);

    // I/O

    void WriteToFile(const char *fname);

};

//
// Constructors
//

inline Histogram::Histogram(void) {
}

inline Histogram::Histogram(double _vmin, double _vmax, int _bins_num, bool _log) :
    log(_log), vmin(_vmin), vmax(_vmax), bins_num(_bins_num),
    bins_width(std::abs(_vmax - _vmin) / static_cast<double>(_bins_num)),
    bins(Linspace()), counts(std::vector<int>(_bins_num, 0)) {
}

inline Histogram::Histogram(double _vmin, double _vmax, double _bins_width, bool _log) :
    log(_log), vmin(_vmin), vmax(_vmax), bins_width(_bins_width), 
    bins_num(static_cast<int>(std::abs(_vmax - _vmin) / _bins_width)),
    bins(Linspace()), counts(std::vector<int>(bins_num, 0)) {
}

inline Histogram::Histogram(std::vector<double> _bins) :
    bins(_bins), counts(std::vector<int>(_bins.size(), 0)) {
    
    if (!std::is_sorted(bins.begin(), bins.end())) std::sort(bins.begin(), bins.end());
    
    vmin = *bins.begin();
    vmax = *bins.end();

    bins_num   = bins.size();
    bins_width = bins[1] - bins[0];
}

inline Histogram::Histogram(std::vector<double> _values, std::vector<double> _bins) : 
    Histogram(_bins) {
    SetValues(_values);
}

inline Histogram::Histogram(std::vector<double> _values, double _vmin, double _vmax, int _bins_num, bool _log) : 
    Histogram(_vmin, _vmax, _bins_num, _log) {
    SetValues(_values);
}

inline Histogram::Histogram(std::vector<double> _values, double _vmin, double _vmax, double _bins_width, bool _log) : 
    Histogram(_vmin, _vmax, _bins_width, _log) {
    SetValues(_values);
}

//
// Setters
//

inline void Histogram::SetLog(bool _flag) {
    log = _flag;
}

inline void Histogram::SetValue(double _value) {
    counts[FindIndex(_value)]++;
}

inline void Histogram::SetValues(std::vector<double> _values) {
    for (double i : _values) counts[FindIndex(i)]++;
}

//
// Getters
//

inline bool Histogram::GetLog(void) {
    return log;
}

//
// Methods
//

inline int Histogram::FindIndex(double _value) {
    if      (_value <  vmin) return 0;
    else if (_value >= vmax) return bins_num-1;
    else                     return std::lower_bound(bins.begin(), bins.end(), _value) - bins.begin();
}

//
// I/O
//

inline void Histogram::WriteToFile(const char *fname) {
    std::ofstream ofs(fname, std::ofstream::out);
    
    ofs << "bins,counts" << std::endl;
    
    for (int i = 0; i < bins_num; ++i) {
        ofs << bins[i] << "," << counts[i] << std::endl;
    }

    ofs.close();
}

inline std::vector<double> Histogram::Linspace(void) {
    std::vector<double> out(bins_num);

    for (int i = 0; i < bins_num; ++i) 
        out[i] = vmin + static_cast<double>(i)*bins_width;

    return out;
}

inline std::vector<double> Histogram::Logspace(void) {
    std::vector<double> out(bins_num);

    for (int i = 0; i < bins_num; ++i)
        out[i] = std::pow(10, std::log10(vmin) + static_cast<double>(i)*bins_width);

    return out;
}


#endif  // HISTOGRAM_H_

