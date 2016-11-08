#ifndef BASIS_H
#define BASIS_H
#include <string>
#include <vector>
#include <complex>
#include <initializer_list>
#include <boost/dynamic_bitset.hpp>

// the startup cost of boost::dynamic_bitset is around 40 Bytes
using DBitSet = boost::dynamic_bitset<>;

// ---------------- fundamental class for basis elements ------------------
// for given number of sites, store the bits for a single orbital
class basis_elem {
    friend void swap(basis_elem &lhs, basis_elem &rhs);
public:
    // default constructor
    basis_elem() = default;
    
    // constructor with total number of sites, and local dimension of Hilbert space
    basis_elem(const int &n_sites, const bool &fermion_, const int &dim_local_);
    
    // constructor from total number of sites and a given name.
    // current choices:
    // "spin-1/2", "spin-1"
    basis_elem(const int &n_sites, const std::string &s);
    
    // copy constructor
    basis_elem(const basis_elem& old);
    
    // move constructor
    basis_elem(basis_elem &&old) noexcept;
    
    // copy assignment constructor and move assignment constructor, using "swap and copy"
    basis_elem& operator=(basis_elem old);
    
    // destructor
    ~basis_elem() {}
    
    int total_sites() const;
    int local_dimension() const { return dim_local; }
    void prt() const;

private:
    short dim_local;
    short bits_per_site;
    bool fermion;
    DBitSet bits;
};

inline void swap(basis_elem &lhs, basis_elem &rhs)
{
    using std::swap;
    swap(lhs.dim_local, rhs.dim_local);
    swap(lhs.bits_per_site, rhs.bits_per_site);
    swap(lhs.fermion, rhs.fermion);
    lhs.bits.swap(rhs.bits);
}


// -------------- class for basis with several orbitals---------------
// for given number of sites, and several orbitals, store the vectors of bits
class mbasis_elem {
    friend void swap(mbasis_elem&, mbasis_elem&);
public:
    // default constructor
    mbasis_elem() = default;
    // construcutor with total number of sites, and name  of each orbital
    mbasis_elem(const int &n_sites, std::initializer_list<std::string> lst);
    
    int total_sites() const;
    
    void test() const;
    
    
private:
    // store an array of basis elements, for multi-orbital site (or unit cell)
    std::vector<basis_elem> mbits;
};

inline void swap(mbasis_elem &lhs, mbasis_elem &rhs)
{
    using std::swap;
    swap(lhs.mbits, rhs.mbits);
}

// -------------- class for wave functions ---------------
// Use with caution, may hurt speed when not used properly
class wavefunction {
    friend void swap(wavefunction&, wavefunction&);
public:
    
    
private:
    // store an array of basis elements, and their corresponding coefficients
    // note: there should not be any dulplicated elements
    std::vector<mbasis_elem> elements;
    std::vector<std::complex<double>> coeffs;
};

inline void swap(wavefunction &lhs, wavefunction &rhs)
{
    using std::swap;
    swap(lhs.elements, rhs.elements);
    swap(lhs.coeffs, rhs.coeffs);
}

#endif
