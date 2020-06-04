/* Technology definition: layernumbers and names, default values.
 * 
 * For different technologies, link with a version of this file that
 * describes that particular technology.
 *
 * Copyright (c) 2004-2010 Xaveer Leijtens
 *
 * This file is part of libMask.
 *
 * libMask is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free
 * Software Foundation, either version 3 of the License, or (at your
 * option) any later version.
 *
 * libMask is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with libMask.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "pdk_demo.h"

/* Mask layer number definitions */

/* Waveguides */

const int L_waveguides              =  1;
const int L_Waveguides              =  2;
const int L_deepetchWG              =  3;
const int L_DeepetchWG              =  4;
const int L_substrateetch           =  5;
const int L_Substrateetch           =  6;
const int L_polcomp                 =  7;
const int L_Polcomp                 =  8;
/* Waveguides inversion */
const int L_Iwaveguides             = 11;
const int L_InversionWG             = 12;
const int L_IdeepetchWG             = 13;
const int L_InversionDeep           = 14;
const int L_Isubstrateetch          = 15;
const int L_InversionSubstr         = 16;
const int L_Ipolcomp                = 17;
const int L_InversionPol            = 18;
/* Contact openings */
const int L_ncontactopen            = 21;
const int L_Ncontactopen            = 22;
const int L_pcontactopen            = 23;
const int L_Pcontactopen            = 24;
const int L_pncontactopen           = 25;
const int L_PNcontactopen           = 26;
/* Metallization */
const int L_nmetal                  = 31;
const int L_Nmetal                  = 32;
const int L_pmetal                  = 33;
const int L_Pmetal                  = 34;
const int L_plating                 = 35;
const int L_Plating                 = 36;
/* Passivation */
const int L_isolation               = 41;
const int L_Isolation               = 42;
const int L_polyimide               = 43;
const int L_Polyimide               = 44;
/* Active areas */
const int L_active                  = 51;
const int L_Active                  = 52;
const int L_contactlayer            = 53;
const int L_Contactlayer            = 54;
/* Special */
const int L_documentation           = 59;
const int L_Documentation           = 60;
const int L_scanAutoEBL             = 61;
const int L_scanManualEBL           = 63;
const int L_cleavemarks             = 65;
const int L_Cleavemarks             = 66;

/* All */
const int L_AllLayers               = -1;

/* The values of EPS1 and EPS2 are used in the generation of the curved
 * waveguides (cw, circle, disc, ...).
 * Standard waveguide layers have high accuracy (1 nm) and non-critical
 * layers have low accuracy (100 nm). This saves a lot of space in the
 * generated masks.
 */
#define EPS1 1e-10
#define EPS2 1e-10

struct layer layers[] = {
/* Waveguide */
  {L_waveguides   , "waveguides",   AQUA,    VISIBLE, EPS1}, /* Fine   */
  {L_Waveguides   , "Waveguides",   AQUA,    VISIBLE, EPS2}, /* Coarse */
  {L_deepetchWG   , "deepetchWG",   WHITE,   VISIBLE, EPS1}, /* Fine   */
  {L_DeepetchWG   , "DeepetchWG",   WHITE,   VISIBLE, EPS2}, /* Coarse */
  {L_substrateetch, "substrateetch",BLUE,    VISIBLE, EPS2}, /* Fine   */
  {L_Substrateetch, "Substrateetch",BLUE,    VISIBLE, EPS2}, /* Coarse */
  {L_polcomp      , "polcomp"      ,DK_GREEN,VISIBLE, EPS2}, /* Fine   */
  {L_Polcomp      , "Polcomp"      ,DK_GREEN,VISIBLE, EPS2}, /* Coarse */
/* Waveguide Inversion */
  {L_Iwaveguides    ,"Iwaveguides",    BLUE,    VISIBLE, EPS1}, /* WG  */
  {L_InversionWG    ,"InversionWG",    PINK,    VISIBLE, EPS2}, /* Inv */
  {L_IdeepetchWG    ,"IdeepetchWG",    AQUA,    VISIBLE, EPS1}, /* WG  */
  {L_InversionDeep  ,"InversionDeep",  WHITE,   VISIBLE, EPS2}, /* Inv */
  {L_Isubstrateetch ,"Isubstrateetch", DK_BLUE, VISIBLE, EPS2}, /* Sub */
  {L_InversionSubstr,"InversionSubstr",YELLOW,  VISIBLE, EPS2}, /* Inv */
  {L_Ipolcomp       ,"Ipolcomp"      , DK_GREEN,VISIBLE, EPS2}, /* Pol */
  {L_InversionPol   ,"InversionPol"   ,ORANGE,  VISIBLE, EPS2}, /* Inv */
/* contact openings */
  {L_ncontactopen ,"ncontactopen",  MAGENTA, VISIBLE, EPS2}, /* Fine   */
  {L_Ncontactopen ,"Ncontactopen",  MAGENTA, VISIBLE, EPS2}, /* Coarse */
  {L_pcontactopen ,"pcontactopen",  MAUVE,   VISIBLE, EPS2}, /* Fine   */
  {L_Pcontactopen ,"Pcontactopen",  MAUVE,   VISIBLE, EPS2}, /* Coarse */
  {L_pncontactopen,"pncontactopen", PURPLE,  VISIBLE, EPS2}, /* Fine   */
  {L_PNcontactopen,"PNcontactopen", PURPLE,  VISIBLE, EPS2}, /* Coarse */
/* Metallization */
  {L_nmetal       ,"nmetal",        YELLOW,  VISIBLE, EPS2}, /* Fine   */
  {L_Nmetal       ,"Nmetal",        YELLOW,  VISIBLE, EPS2}, /* Coarse */
  {L_pmetal       ,"pmetal",        ORANGE,  VISIBLE, EPS2}, /* Fine   */
  {L_Pmetal       ,"Pmetal",        ORANGE,  VISIBLE, EPS2}, /* Coarse */
  {L_plating      ,"plating",       BROWN,   VISIBLE, EPS2}, /* Fine   */
  {L_Plating      ,"Plating",       BROWN,   VISIBLE, EPS2}, /* Coarse */
/* Passivation */
  {L_isolation    ,"isolation",     GREEN,   VISIBLE, EPS2}, /* Fine   */
  {L_Isolation    ,"Isolation",     GREEN,   VISIBLE, EPS2}, /* Coarse */
  {L_polyimide    ,"polyimide",     PINK,    VISIBLE, EPS2}, /* Fine   */
  {L_Polyimide    ,"Polyimide",     PINK,    VISIBLE, EPS2}, /* Coarse */
/* Active areas */
  {L_active       ,"active",        BLACK,   VISIBLE, EPS2}, /* Fine   */
  {L_Active       ,"Active",        BLACK,   VISIBLE, EPS2}, /* Coarse */
  {L_contactlayer ,"contactlayer",  RED,     VISIBLE, EPS2}, /* Fine   */
  {L_Contactlayer ,"Contactlayer",  RED,     VISIBLE, EPS2}, /* Coarse */
/* Special */
  {L_documentation,"documentation", CYAN,    VISIBLE, EPS2},
  {L_Documentation,"Documentation", RED,     VISIBLE, EPS2},
  {L_scanAutoEBL  ,"scanAutoEBL",   BLUE,    VISIBLE, EPS2}, /* Fine   */
  {L_scanManualEBL,"scanManualEBL", RED,     VISIBLE, EPS2}, /* Fine   */
  {L_cleavemarks  ,"cleavemarks",   TAN,     VISIBLE, EPS2}, /* Fine   */
  {L_Cleavemarks  ,"Cleavemarks",   TAN,     VISIBLE, EPS2}, /* Coarse */
  END_LAYERS
};
