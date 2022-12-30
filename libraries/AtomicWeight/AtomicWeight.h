#pragma once
//
//    FILE: AtomicWeight.h
//  AUTHOR: Rob Tillaart
//    DATE: 2022-03-09
// VERSION: 0.1.0
// PURPOSE: Arduino library for atomic weights
//     URL: https://github.com/RobTillaart/AtomicWeight


#include "Arduino.h"

#define ATOMIC_WEIGHT_LIB_VERSION         (F("0.1.0"))


/////////////////////////////////////////////////////////////////////////
//
//  list of elements 
//  weight = weight * 222.909
//
struct element
{
  char     name[3];
  uint16_t weight;
}
elements[119] =
{
  {"n",  225},      //  neutronium
  {"H",  225},
  {"He", 892},
  {"Li", 2186},
  {"Be", 2009},
  {"B",  2410},
  {"C",  2677},
  {"N",  3122},
  {"O",  3566},
  {"F",  4235},
  {"Ne", 4498},
  {"Na", 5125},
  {"Mg", 5418},
  {"Al", 6014},
  {"Si", 6261},
  {"P",  6904},
  {"S",  7148},
  {"Cl", 7903},
  {"Ar", 8905},
  {"K",  8715},
  {"Ca", 8934},
  {"Sc", 10021},
  {"Ti", 10670},
  {"V",  11355},
  {"Cr", 11590},
  {"Mn", 12246},
  {"Fe", 12448},
  {"Co", 13137},
  {"Ni", 13083},
  {"Cu", 14165},
  {"Zn", 14580},
  {"Ga", 15542},
  {"Ge", 16192},
  {"As", 16701},
  {"Se", 17601},
  {"Br", 17811},
  {"Kr", 18679},
  {"Rb", 19052},
  {"Sr", 19531},
  {"Y",  19818},
  {"Zr", 20335},
  {"Nb", 20710},
  {"Mo", 21386},
  {"Tc", 21845},
  {"Ru", 22529},
  {"Rh", 22939},
  {"Pd", 23722},
  {"Ag", 24045},
  {"Cd", 25057},
  {"In", 25594},
  {"Sn", 26462},
  {"Sb", 27141},
  {"Te", 28443},
  {"I",  28288},
  {"Xe", 29266},
  {"Cs", 29626},
  {"Ba", 30611},
  {"La", 30963},
  {"Ce", 31233},
  {"Pr", 31410},
  {"Nd", 32152},
  {"Pm", 32322},
  {"Sm", 33517},
  {"Eu", 33874},
  {"Gd", 35052},
  {"Tb", 35426},
  {"Dy", 36223},
  {"Ho", 36764},
  {"Er", 37284},
  {"Tm", 37657},
  {"Yb", 38572},
  {"Lu", 39002},
  {"Hf", 39787},
  {"Ta", 40335},
  {"W",  40980},
  {"Re", 41507},
  {"Os", 42404},
  {"Ir", 42847},
  {"Pt", 43485},
  {"Au", 43906},
  {"Hg", 44713},
  {"Tl", 45559},
  {"Pb", 46187},
  {"Bi", 46584},
  {"Po", 46588},
  {"At", 46811},
  {"Rn", 49486},
  {"Fr", 49709},
  {"Ra", 50377},
  {"Ac", 50600},
  {"Th", 51723},
  {"Pa", 51500},
  {"U",  53059},
  {"Np", 52829},
  {"Pu", 54390},
  {"Am", 54167},
  {"Cm", 55059},
  {"Bk", 55059},
  {"Cf", 55950},
  {"Es", 56173},
  {"Fm", 57288},
  {"Md", 57511},
  {"No", 57733},
  {"Lr", 58402},
  {"Rf", 58179},
  {"Db", 58402},
  {"Sg", 59294},
  {"Bh", 58848},
  {"Hs", 61746},
  {"Mt", 59740},
  {"Ds", 62637},
  {"Rg", 60631},
  {"Cn", 63529},
  {"Nh", 63752},
  {"Fl", 64421},
  {"Mc", 64421},
  {"Lv", 65312},
  {"Ts", 65535},
  {"Og", 65535},
};


/////////////////////////////////////////////////////////////////////////
//
//  IS THIS THE RIGHT FORMAT?
//  or should we build a list of elements
//
class PTOE
{
public:
  PTOE(uint8_t size = 118)      { _size = size; };    //  all by default

  uint8_t size()                { return _size; };

  uint8_t electrons(uint8_t el) { return el; };
  uint8_t neutrons(uint8_t el)  { return round(weight(el) - el); };
  uint8_t protons(uint8_t el)   { return el; };

  float   weight(uint8_t el)    { return elements[el - 1].weight * _weightFactor; };

  char *  name(uint8_t el)      { return elements[el - 1].name; };
  uint8_t find(char * abbrev)
  {
    for (uint8_t i = 0; i < _size; i++)
    {
      if (strcmp(elements[i].name, abbrev) == 0) return i;
    }
    return 255;
  }


  //  DEBUG
  float   weightFactor()        { return _weightFactor; };


private:
  uint8_t     _size;
  const float _weightFactor = 1.0 / 222.909;
};



// -- END OF FILE --

