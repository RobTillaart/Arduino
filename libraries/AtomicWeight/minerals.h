#pragma once
//
//    FILE: minerals.h
//  AUTHOR: Rob Tillaart
//    DATE: 2024-08-12
// PURPOSE: very short list of chemical formulae of minerals
//     URL: https://github.com/RobTillaart/AtomicWeight
//


/////////////////////////////////////////////////////////////////////////
//
//  The formulae are based upon Cornelis Klein, Anthony Philpotts book
//  Earth Materials, introduction to Mineralogy and Petrology, chapter 7,
//  chapter 11 and chapter 14.
//  ISBN: 978-1-316-60885-2
//
//  NOT SUPPORTED: ==> formulae commented
//  NOT SUPPORTED: Fe2+ or Fe3+    (potential,   could be ignored!)
//  NOT SUPPORTED: comma operator  (selection,   should be made explicit)
//  NOT SUPPORTED: Fe1-x           (less than 1, should be made explicit)
//  NOT SUPPORTED: 4(FORMULA)      (multiple)  ==> (FORMULA)4 workaround  implement square []?
//  NOT SUPPORTED  .4(H2O)         (hydration) ==> (H2O)4 workaround.     implement square []?
//
//  to be extended,
//
//  DISCLAIMER
//  Formulas might differ to be parse-able by the atomicWeight class.
//

//
//  IGNEOUS ROCK
//
//  7.5
#define ALBITE              "NaAlSi3O8"
#define ANORTHITE           "CaAl2Si2O8"
//  7.6
#define MICROLINE           "KAlSi3O8"              //  Orthoclase
//  7.7
#define QUARTZ              "SiO2"
//  7.8
#define NEPHELINE           "(Na3K)Al4(SiO4)"
#define KALSILITE           "KAlSiO4"
//  7.9
#define LEUCITE             "KAlSi2O6"
#define AEGIRINE            "NaFeSi2O6"             //  7.14
//  7.10
#define SODALITE            "Na4Al3Si3O12Cl"
//  7.11
#define ENSTATITE           "MgSiO3"                //  "(Mg1.0Fe0.0)SiO3"
#define FERROSILITE         "FeSiO3"                //  "(Mg0.5Fe0.5)SiO3"
//  7.12
#define PIGEONITE           "Ca0.25(MgFe)1.75Si2O6"
//  7.13
#define DIOPSIDE            "CaMgSi2O6"
#define WOLLASTONITE        "CaSiO3"
//  7.15
#define TREMOLITE           "Ca2Mg5Si8O22(OH)2"
//  7.16
#define MUSCOVITE           "KAl3Si3O10(OH)2"
//  7.17
#define PHOLOGOPITE         "KMg3(AlSi3O10)(OH)2"
//  7.18
//  #define BIOTITE         "K(Mg,Fe)3(AlSi3O10)(OH)2"
//  7.19
//  #define OLIVINE         "(Mg,Fe)2SiO4"
#define FORSTERITE          "Mg2SiO4"
#define FAYALITE            "Fe2SiO4"
//  7.20
#define ZIRCON              "ZrSiO4"
//  7.21
//  #define TOUMALINE       "(Na,Ca,K)(Fe,Mg,Al,Mn,Li)3(Al,Fe)6(BO3)3(Si6O18)(OH)3(O,OH,F)"
//  #define SCHORL          "(NaFe3Al6(BO3)3(Si6O18)(OH)3(O,OH,F)4"
//  7.22
//  #define ALLANITE        "(Ca,Ce)2(Al,Fe++,Fe+++)3(SiO4)(Si2O7)(OH)"
//          17.6            "(Ca,Ce, La)2(Al,Fe++,Fe+++)3(SiO4)(Si2O7)(OH)"
//  7.23
//  #define MELITITE        "(Ca,Na)2(Mg,Al)(Si,Al)2O7"
#define AKERMANITE          "Ca2MgSi2O7"
//  7.24
#define MAGNETITE           "Fe3O4"
#define ULVOSPINEL          "Fe2TiO4"
#define ILMENITE            "FeTiO3"    //  7.27
#define SPINEL              "MgAl2O4"
//  7.25
#define CHROMITE            "FeCr2O4"
//  7.26
#define HEMATITE            "Fe2O3"
#define CORUNDUM            "Al2O3"
//  7.28
#define RUTILE              "TiO2"
//  7.29
#define URANINITE           "UO2"
//  7.30
#define PYRITE              "FeS2"    //  Polymorph MARCASITE
//  7.31
//  #define PYRRHOTITE      "Fe1-xS"   //  x = 0..0.2
//  7.32
#define CHALCOPYRITE        "CuFeS2"
//  7.33
//  #define APATITE         "Ca5(PO4)3(OH,F,Cl)
#define HYDROXYAPATITE      "Ca5(PO4)3(OH)"


//
//  SEDIMENTARY ROCK
//
//  Page 237
#define JADEITE             "NaAlSi2O6"
//  11.3
#define GOETHITE            "FeO(OH)"
//  11.4
#define KAOLINITE           "Al2Si2O5(OH)4"
//  11.5
#define CALCITE             "CaCO3"
//  11.6
#define ARAGONITE           "CaCO3"  //  same as calcite
//  11.7
#define DOLOMITE            "CaMg(CO3)2"
//  11.8
#define MAGNESITE           "MgCO3"
//  11.9
#define SIDERITE            "FeCO3"
//  11.10
#define RHODOCHROSITE       "MnCO3"
//  11.11
#define HALITE              "NaCl"
//  11.12
#define SYLVITE             "KCl"
//  11.13
#define GYPSUM              "CaSO4"   //  CaSO4*4H20
//  11.14
#define ANHYDRITE           "CaSO4"
//  11.16
#define FLUORAPATITE        "Ca5(PO4)3(F)"


//
//  METAMORPHIC ROCK
//
//  14.2 GARNET
//  soyralspite group
#define PYROPE              "Mg3Al2Si3O12"
#define ALMANDINE           "Fe3Al2Si3O12"
#define SPESSARTINE         "Mn3Al2Si3O12"
//  ugandite group
#define GROSSULAR           "Ca3Al2Si3O12"
#define ANDRADITE           "Ca3Fe2Si3O12"
#define UVAROVITE           "Ca3Cr2Si3O12"
//  14.3
#define ANDALUSITE          "Al2SiO5"
#define MULLITE             "Al2O3(SiO2)2"
//  14.4
#define SILLIMANITE         "Al2SiO5"
//  14.5
#define KYANITE             "Al2SiO5"
//  14.6
//  formula not supported   "Fe3-4Al18Si8O48H2-4"
#define STAUROLITE          "Fe3Al18Si8O48H2"
//  14.7
//  #define DIOPSIDE            "CaMgSi2O6"  7.13
//  14.8
#define ANTHOPHYLLITE       "Mg7Si8O22(OH)2"
//  14.9
#define CUMMINGTONITE       "Fe2Mg5Si8O22(OH)2"
#define GRUNERITE           "Fe7Si8O22(OH)2"
//  14.10
#define TREMOLITE           "Ca2Mg5Si8O22(OH)2"
#define FERROACTINOLITE     "Ca2Fe5Si8O22(OH)2"
//  14.11
#define GLAUCAPHANE         "Na2Mg3Si8O22(OH)2"
//  14.12
//  #define WOLLASTONITE        "CaSiO3"  See 7.13
//  14.13
#define RHODONITE           "MnSiO3"
//  14.14
#define TALC                "Mg3Si4O10(OH)2"
//  14.15
//  not supported formula   "(Mg,Al,Fe)6(Si,Al)4O10(OH)8"
#define CHLORITE            "Mg6(Si3Al)O10(OH)8"
//  14.16
#define ANTIGORITE          "Mg3Si2O5(OH)4"
//  14.17
#define CHRYSOLITE          "Mg3Si2O5(OH)4"
//  14.18
#define GRAPHITE            "C"
//  14.19
#define EPIDOTE             "Ca2FeAl2O(SiO4)(Si2O7)(OH)"
#define CLINOZOISITE        "Ca2Al3O(SiO4)(Si2O7)(OH)"
//  14.20
//  not supported formula   "(Mg,Fe)2Al4Si5O18(H2O)n"
#define CORDEIRITE          "Mg2Al4Si5O18"
//  14.21
//  not supported formula   "Ca19(Al,Mg,Fe)13(Si2O7)4(SiO4)10(O,OH,F)10"
#define VESUVIANITE         "Ca19Mg13(Si2O7)4(SiO4)10(OH)10"
//  14.22
#define TITANITE            "CaTiSiO5"
//  14.23
//  not supported formula   "3CaAl2Si2O8(CaSO4)"
#define SCAPOLITE           "NaAlSi3O8(NaCl)"
//  14.24
#define LAWSONITE           "CaAl2(Si2O7)(OH)2"
//  14.25
#define PUMPELLYITE         "Ca2MgAl2(SiO4)(Si2O7)(OH)2"
//  14.26
//  #define TOPAZ               "Al2SiO4(F)2"
#define TOPAZ               "Al2SiO4(OH)2"
//  14.27
//  #define CORUNDUM            "Al2O3"  See 7.26
//  14.28
#define CHABAZITE           "Ca2Al2Si4O12"


//
//  METAMORPHISM (chap 15)
//
//  15.7  fig 15.25
#define PERICLASE           "MgO"
#define MONTICELLITE        "CaMgSiO4"
#define MERWINITE           "Ca3MgSi2O8"
#define LARNITE             "Ca2SiO4"
#define SPURRITE            "Ca4Si2O8(CaCO3)"
#define TILLEYITE           "Ca3Si2O7(CaCO3)2"
#define RANKINITE           "Ca3Si2O7"

//  15.9
#define PHLOGOPITE          "KMg3AlSi3O10(OH)2"
#define ANNIITE             "KFe3AlSi3O10(OH)2"


//
//  ECONOMIC MINERALS (chap 16)
//
//  16.0
#define ACANTHITE           "Ag2S"
#define PROUSTITE           "Ag3AsS3"
#define PYRARGTRITE         "Ag3SbS3"

//  16.6
#define GALENA              "PbS"
//  16.7
#define SPHALERITE          "ZnS"
//  16.8
#define BORNITE             "CuFeS4"
//  16.9
#define CHALCOCITE          "Cu2S"
//  16.10
#define MARCASITE           "FeS2"    //  Polymorph PYRITE
//  16.11
#define MOLYBDENITE         "MoS2"
#define BROCHANTHITE        "Cu4SO4(OH)6"
//  16.12
#define ARSENOPYRITE        "FeAsS"
//  16.13
#define BAUXITE             "AlO(OH)"   // variations.
#define DIASPORE            "AlO(OH)"
#define GIBBSITE            "Al(OH)2"
#define BOEHMITE            "AlO(OH)"
//  16.14
#define FLUORITE            "CaF2"
//  16.15
#define BARITE              "BaSO4"
#define CELESTITE           "SrSO4"
//  16.16
#define SPODUMENE           "LiAlSi2O6"
#define KUNZITE             "LiAlSi2O6"
//  16.17
//  #define LEPIDOLITE      "K(Li,Al)2-3(AlSi3O10)(OH,F)2"   // variations.
//  16.18
#define RUBY                "Al2O3"     // CORUMDUM
#define SAPPHIRE            "Al2O3"     // CORUMDUM
// #define TOPAZ.           "Al2Si4(F,OH)2"
#define BERYL               "Be3Al2SI6O18"
#define EMERALD             "Be3Al2SI6O18"
#define HELIODOR            "Be3Al2SI6O18"
#define AQUAMARINE          "Be3Al2SI6O18"
#define JADE                "NaAlSi2O6"   //  JADEITE
#define TURQOISE            "CuAl8(PO4)(OH)8(H20)5"   //  Cu may be replaced by Fe
//  page 494
#define CALAVERITE          "AuTe2"

//
//  RARE EARTH ELEMENTS (chap 17)
//
//  17.6 Rare earth elements
//  #define BASTNASITE      "(ce,La)CO3F"     // variations.
//  #define MONAZITE        "(La,Ce,Nd)PO4"   // variations.
#define XENOTIME            "YPO4"
//  #define ALLANITE        "(Ca,Ce, La)2(Al,Fe++,Fe+++)3(SiO4)(Si2O7)(OH)"  //  see 7.22
//  17.7  Zeolites
//  #define CHABAZITE  see 14.28
#define NATROLITE           "Na2Al2Si3O10(H2O)5"
//  #define HEULANDITE      "(Na,Ca)2-3Al3(Al,Si)2Si13O36(H2O)12"
#define STILBITE           "NaCa2Al5Si13O365(H2O)14"   //  specific variation of HEULANDITE


//
//  OTHER (chap 18)
//
//  TODO


//  -- END OF FILE --

