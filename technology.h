/* Technology header file.
 * 
 * Copyright (c) 2010- Xaveer Leijtens
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

#ifndef _MSK_TECHNOLOGY_INCLUDED_
#define _MSK_TECHNOLOGY_INCLUDED_

/* Mask layer name definitions */
                                 
/* Waveguides */                 
extern const int L_waveguides;   
extern const int L_Waveguides;   
extern const int L_deepetchWG;
extern const int L_DeepetchWG;
extern const int L_substrateetch;
extern const int L_Substrateetch;
extern const int L_polcomp;
extern const int L_Polcomp;
/* Waveguides inversion */
extern const int L_Iwaveguides;
extern const int L_InversionWG;
extern const int L_IdeepetchWG;
extern const int L_InversionDeep;
extern const int L_Isubstrateetch;
extern const int L_InversionSubstr;
extern const int L_Ipolcomp;
extern const int L_InversionPol;
/* Contact openings */
extern const int L_ncontactopen;
extern const int L_Ncontactopen;
extern const int L_pcontactopen;
extern const int L_Pcontactopen;
extern const int L_pncontactopen;
extern const int L_PNcontactopen;
/* Metallization */
extern const int L_nmetal;
extern const int L_Nmetal;
extern const int L_pmetal;
extern const int L_Pmetal;
extern const int L_plating;
extern const int L_Plating;
/* Passivation */
extern const int L_isolation;
extern const int L_Isolation;
extern const int L_polyimide;
extern const int L_Polyimide;
/* Active areas */
extern const int L_active;
extern const int L_Active;
extern const int L_contactlayer;
extern const int L_Contactlayer;
/* Special */
extern const int L_documentation;
extern const int L_Documentation;
extern const int L_scanAutoEBL;
extern const int L_scanManualEBL;
extern const int L_cleavemarks;
extern const int L_Cleavemarks;
/* All */
extern const int L_AllLayers;

#endif /* _MSK_TECHNOLOGY_INCLUDED_ */
