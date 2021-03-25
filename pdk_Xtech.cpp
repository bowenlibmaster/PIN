//
// Created by Yuan on 2018/11/8.
//

#include <IPL_Extension.h>
#include "pdk_Xtech.h"

#include "type_traits"


IMPLEMENT_NEW_PDK(PDK_Xtech)


    DEFINE_WG_STRUCTURES
            {"waveguide1", {5_um, TYPE_O_PORT, {
                        {layernr(L_waveguides), 0.5_um}, {layernr(L_contactlayer),2_um}
                }
                }
            },

            {"M1", {20_um, TYPE_DC_PORT, {
                    {layernr(L_Pmetal), 6_um}
            }
            }
            },

            {"M2", {20_um, TYPE_DC_PORT, {
                    {layernr(L_Nmetal), 6_um}
            }
            }
            }
    END_DEFINE_WG_STRUCTURES
    IMPLEMENT_WAVEGUIDES(, waveguide1);




    MMI::MMI() {
        SimpleComponent = true;
        COMPONENT_INIT();
    }

    void MMI::layout(int l) {
//    DEBUG_SHOW(WG_Structure_List["waveguide1"][0].WG_layer);
        layer(L_waveguides);
        double Length_MMI = 100.174_um, Width_MMI = 9_um;
        double Width_Taper_in = 0.55_um, Width_Taper_out = 2.2_um, Length_Taper = 24.75_um;
        double Pitch_IO = 3_um;
        pointer cp1;
        BLOCK {
            add_O_Port("in1", cp, WG_Structure_List["waveguide1"]);
            BLOCK {
                offset(-Pitch_IO);
                add_O_Port("in2", cp, WG_Structure_List["waveguide1"]);
            }

            mmi_2x2taper(Length_MMI, Width_MMI, Width_Taper_in, Width_Taper_out, Length_Taper, Pitch_IO / 2.0,
                         -Pitch_IO / 2.0, Pitch_IO / 2.0, -Pitch_IO / 2.0, 90_deg);

            cp1 = cp;
            BLOCK {
                add_O_Port("out1", cp, WG_Structure_List["waveguide1"]);
            }

            move(0, Pitch_IO, 0, 0);

            add_O_Port("out2", cp, WG_Structure_List["waveguide1"]);

        }
        BLOCK {
            layer(L_Waveguides);
            mmi_2x2taper(Length_MMI, Width_MMI + 10_um, Width_Taper_in + 10_um, Width_Taper_out + 10_um, Length_Taper,
                         Pitch_IO / 2.0,
                         -Pitch_IO / 2.0, Pitch_IO / 2.0, -Pitch_IO / 2.0, 90_deg);
//            cw(100_um, 45_deg, 10.55_um);
        }
        BLOCK{
            layer(L_Waveguides);
            move(Length_Taper - 5_um, Pitch_IO / 2.0, 0, NOFLIP);
            rect(Length_MMI + 2 * 5_um, Width_MMI + 2 * 5_um, 4, 4);
        }
        cp = cp1;
    }

    MZI::MZI() {
        SimpleComponent = true;
        COMPONENT_INIT();
    }


    void MZI::layout(int l) {
        var mmi1 = NEW(MMI);
        var mmi2 = NEW(MMI);

        mmi1.place().O_PORTS["out1"]
            >> NEW(SINE_BEND, 100_um, -100_um)
            >> NEW(SW, 1_mm)
            >> NEW(SINE_BEND, 100_um, 100_um)
            >> mmi2.O_PORTS["in1"] >> "in2" >> FLIP_Y
            >> NEW(SINE_BEND, 100_um, 100_um)
            >> NEW(SW, 1_mm)
            >> NEW(CONNECTOR_SINE_BEND)
            >> mmi1.O_PORTS["out2"];

        add_O_Port(mmi1.O_PORTS["in1"], "in1");
        add_O_Port(mmi1.O_PORTS["in2"], "in2");
        add_O_Port(mmi2.O_PORTS["out1"], "out1");
        add_O_Port(mmi2.O_PORTS["out2"], "out2");
    }


    RingTyp1::RingTyp1(double gap, double radius): gap(gap), radius(radius){
        SimpleComponent = true;
        COMPONENT_INIT(gap, radius);
    }


    void RingTyp1::layout(int l) {

        //double R = 7_um, gap = 0.15_um, lcoalwg = 0.5_um;
        double R = radius, gap = this->gap, lcoalwg = 0.5_um;
        layer(L_waveguides);

        add_O_Port("in", cp, WG_Structure_List["waveguide1"]);
        sw(2*R,lcoalwg);
        add_O_Port("thru", cp, WG_Structure_List["waveguide1"]);
        move(-2*R,-2*gap-2*lcoalwg-2*R,0,NOFLIP);

        add_O_Port("drop", cp, WG_Structure_List["waveguide1"]);
        sw(2*R,lcoalwg);
        add_O_Port("add", cp, WG_Structure_List["waveguide1"]);

        move(-R,gap+lcoalwg,0,NOFLIP);
        cw(R,-2*M_PI,lcoalwg);

        BLOCK {
            layer(L_substrateetch);
            skip(-1.25*R);
            offset(-R);
            sw(2.5*R, 2.5*R);
        }

    }


    SINE_BEND_EBL::SINE_BEND_EBL(double gap, double radius): gap(gap), radius(radius){
        SimpleComponent = true;
        COMPONENT_INIT(gap, radius);
    }


    void SINE_BEND_EBL::layout(int l) {

        add_O_Port("in", cp, WG_Structure_List["waveguide1"]);

        BLOCK {
            layer(L_contactlayer);
            move(0,0.5*radius,0,NOFLIP);
            sw(1.0*gap,2*abs(radius));

        }
        NEW(SINE_BEND, gap, radius).place();
        add_O_Port("out", cp, WG_Structure_List["waveguide1"]);


    }

    SW_EBL::SW_EBL(double gap): gap(gap){
        SimpleComponent = true;
        COMPONENT_INIT(gap);
    }


    void SW_EBL::layout(int l) {

        add_O_Port("in", cp, WG_Structure_List["waveguide1"]);

        BLOCK {
            layer(L_contactlayer);
            sw(gap,30_um);

        }
        NEW(SW, gap).place();
        add_O_Port("out", cp, WG_Structure_List["waveguide1"]);


    }

    CW_EBL::CW_EBL(double gap, double radius): gap(gap), radius(radius){
        SimpleComponent = true;
        COMPONENT_INIT(gap, radius);
    }


    void CW_EBL::layout(int l) {

        add_O_Port("in", cp, WG_Structure_List["waveguide1"]);

        BLOCK {
            layer(L_contactlayer);

            if(radius>=0) {
                move(0, -gap / 2, 0, NOFLIP);
                sw(2.1 * gap, 2.1 * gap);
            }
            else{
                move(0, gap / 2, 0, NOFLIP);
                sw(2.1 * gap, 2.1 * gap);
            }

        }
        NEW(CW,gap,radius).place();
        add_O_Port("out", cp, WG_Structure_List["waveguide1"]);

    }

    CW_EBL_180::CW_EBL_180(double gap, double radius): gap(gap), radius(radius){
        SimpleComponent = true;
        COMPONENT_INIT(gap, radius);
    }


    void CW_EBL_180::layout(int l) {

        add_O_Port("in", cp, WG_Structure_List["waveguide1"]);

        BLOCK {
            layer(L_contactlayer);

            if(radius>=0) {
                move(0, -gap, 0, NOFLIP);
                sw(2.1 * gap, 3.1 * gap);
            }
            else{
                move(0, gap, 0, NOFLIP);
                sw(2.1 * gap, 3.1 * gap);
            }

        }
        NEW(CW,gap,radius).place();
        add_O_Port("out", cp, WG_Structure_List["waveguide1"]);

    }



    EBL_LOCAL_MARK_TEMP::EBL_LOCAL_MARK_TEMP(double ScanFieldSize, double ArmLength, double Inverse): ScanFieldSize(ScanFieldSize), ArmLength(ArmLength),Inverse(Inverse){
        SimpleComponent = true;
        COMPONENT_INIT(ScanFieldSize, ArmLength,Inverse);
    }


    void EBL_LOCAL_MARK_TEMP::layout(int l) {

        double ArmWidth = 2.0e-6;
        double AutoScanLength = 6.0e-6;
        double AutoScanWidth = 0.5e-6;
        double delta = 2e-6;

        BLOCK {
            layer(L_waveguides);
            add_O_Port("in", cp, WG_Structure_List["waveguide1"]);

            if (Inverse == 0){
                rect(ArmLength, ArmWidth, 5, 5);
                rect(ArmWidth, ArmLength, 5, 5);
            }
            else {  /* inverse mark */
                push_cp();
                move(-0.5 * ArmWidth, 0.5 * ArmWidth, 0, 0);
                rect( (0.5 * (ArmLength - ArmWidth)), (0.5 * (ArmLength - ArmWidth)), 3, 3);
                offset(ArmWidth);
                rect( (0.5 * (ArmLength - ArmWidth)), (0.5 * (ArmLength - ArmWidth)), 9, 9);
                skip(ArmWidth);
                rect( (0.5 * (ArmLength - ArmWidth)), (0.5 * (ArmLength - ArmWidth)), 7, 7);
                offset(-ArmWidth);
                rect( (0.5 * (ArmLength - ArmWidth)), (0.5 * (ArmLength - ArmWidth)), 1, 1);
                pop_cp();

                push_cp();
                skip(-0.5 * ArmLength);
                rect((0.5 * (ScanFieldSize - ArmLength)), ScanFieldSize, 6, 6);
                move(0.5 * ArmLength, 0.5 * ArmLength, 0, 0);
                rect(ScanFieldSize, (0.5 * (ScanFieldSize - ArmLength)), 2, 2);
                move(0, -ArmLength, 0, 0);
                rect(ScanFieldSize, (0.5 * (ScanFieldSize - ArmLength)), 8, 8);
                move(0.5 * ArmLength, 0.5 * ArmLength, 0, 0);
                rect((0.5 * (ScanFieldSize - ArmLength)), ScanFieldSize, 4, 4);
                pop_cp();
            }
            /* Scan fields for automatic alignment */
            layer(L_scanAutoEBL);
            push_cp();
            move(0.25 * ArmLength, 0.5 * AutoScanLength, -RAD(90), NOFLIP);
            if (mode & POLYGON) {
                mode &= ~POLYGON;
                sw(AutoScanLength, AutoScanWidth);
                mode |= POLYGON;
            } else {
                sw(AutoScanLength, AutoScanWidth);   }
            pop_cp();

            push_cp();
            move(-0.5 * AutoScanLength, 0.25 * ArmLength, 0, NOFLIP);
            if (mode & POLYGON) {
                mode &= ~POLYGON;
                sw(AutoScanLength, AutoScanWidth);
                mode |= POLYGON;
            } else {
                sw(AutoScanLength, AutoScanWidth);
            }
            pop_cp();

            /* Scan fields for manual alignment */
            layer(L_scanManualEBL);
            push_cp();
            skip(-0.50 * ScanFieldSize-delta/2);
            sw(ScanFieldSize+delta, ScanFieldSize+delta);
            pop_cp();

        }


    }

    WG::WG(double WL): WL(WL){
        SimpleComponent = true;
        COMPONENT_INIT(WL);
    }

    void WG::layout(int l) {
        double WG_width = 0.5e-6;
        BLOCK

        {
            layer(L_waveguides);
            add_O_Port("in", cp, WG_Structure_List["waveguide1"]);
            sw(100e-6,100e-6);
            add_O_Port("out", cp, WG_Structure_List["waveguide1"]);
        };
    }

    STEPPER_1::STEPPER_1() {
        SimpleComponent = true;
        COMPONENT_INIT();
    }

    void STEPPER_1::layout(int l) {
        BLOCK

        {
            layer(L_waveguides);
            add_O_Port("in", cp, WG_Structure_List["waveguide1"]);
            offset(67.175_um);
            skip(-67.175_um);

        for (int n = 0; n <= 3; n++) {
            triangle(0, sqrt(0.5*1.6_um*1.6_um), sqrt(0.5*1.6_um*1.6_um), 0);
            rotate(-45_deg);
            skip(0.8_um);
            sw(60_um - 1.6_um, 1.6_um);
            skip(0.8_um);
            rotate(RAD(45));
            triangle(0, -sqrt(0.5*1.6_um*1.6_um), -sqrt(0.5*1.6_um*1.6_um), 0);
            rotate(-45_deg);
            skip(35_um);
            rotate(45_deg);
            skip(16_um);
            sw(46_um, 1.6_um);
            skip(-46_um - 16_um);
            rotate(45_deg);
            skip(95_um);
            rotate(-135_deg);
        }
        };
    }

    STEPPER_1_F::STEPPER_1_F() {
        SimpleComponent = true;
        COMPONENT_INIT();
    }

    void STEPPER_1_F::layout(int l) {
        BLOCK

        {
            layer(L_waveguides);
            add_O_Port("in", cp, WG_Structure_List["waveguide1"]);
            offset(67.175_um);
            skip(-67.175_um);

            for (int n = 0; n <= 3; n++) {
                triangle(0, sqrt(0.5*1.6_um*1.6_um), sqrt(0.5*1.6_um*1.6_um), 0);
                rotate(-45_deg);
                skip(0.8_um);
                sw(60_um - 1.6_um, 1.6_um);
                skip(0.8_um);
                rotate(RAD(45));
                triangle(0, -sqrt(0.5*1.6_um*1.6_um), -sqrt(0.5*1.6_um*1.6_um), 0);
                rotate(-45_deg);
                skip(35_um);
                rotate(45_deg);
                skip(16_um);
                sw(46_um, 1.6_um);
                skip(-46_um - 16_um);
                rotate(45_deg);
                skip(95_um);
                rotate(-135_deg);
            }
        };
    }

    STEPPER_2::STEPPER_2() {
        SimpleComponent = true;
        COMPONENT_INIT();
    }

    void STEPPER_2::layout(int l) {
        BLOCK

        {
            layer(L_waveguides);
            add_O_Port("in", cp, WG_Structure_List["waveguide1"]);
            for (int m = 0; m <= 3; m++) {
                push_cp();
                offset(3e-6);
                skip(3e-6);
                for (int n = 0; n <= 4; n++) {
                    rect(6e-6, 57e-6, 7, 9);
                    skip(6e-6);

                }
                pop_cp();
                rotate(RAD(-90));
            }
        };
    }
    GC_AP_9::GC_AP_9(double Pitch, double ff): Pitch(Pitch), ff(ff){
        SimpleComponent = true;
        COMPONENT_INIT(Pitch, ff);
    }


    void GC_AP_9::layout(int l) {

        int num_periods = 20;
        double WG_width = 0.5e-6;
        double width = 12_um, Taper_length = 200_um;
        double mark1 = 20e-6;
        double marker2 = 50e-6, backex = 5e-6+11.678e-6;

        double etched [9] = { 0.678_um, 0.678_um, 0.314_um, 0.112_um, 0.418_um,0.105_um,0.438_um,0.673_um,0.601_um};

        double top [9] = {0.418_um, 0.418_um, 0.435_um, 0.423_um, 0.744_um,0.1_um,0.391_um,0.487_um,0.508_um};

        double topa=0, etcheda=0;
        BLOCK{
            skip(backex);
            for(int n=0;n<9;n=n+1){
                move(top[n],0,0,NOFLIP);
                layer(L_substrateetch);
                sw(etched[n],width);
            }
        };

        layer(L_waveguides);

        for(int n=0;n<9;n=n+1){topa+=top[n];}
        for(int n=0;n<9;n=n+1){etcheda+=etched[n];}
        BLOCK {
            sw(backex, width);
            sw((topa + etcheda), width);
            //add_O_Port("In", cp, WG_Structure_List["waveguide1"]);
            taper_angle(Taper_length, 0, width, WG_width);
            add_O_Port("out", cp, WG_Structure_List["waveguide1"]);
        }



        BLOCK {
            layer(L_contactlayer);
            double offsssee = 50_um;
            skip(-offsssee);
            sw(backex+num_periods * (topa + etcheda)+Taper_length+2*offsssee, 1.5*width);
        }

    }

    GC_IN::GC_IN(double Pitch, double ff): Pitch(Pitch), ff(ff){
        SimpleComponent = true;
        COMPONENT_INIT(Pitch, ff);
    }


    void GC_IN::layout(int l) {

        int num_periods = 20;
        double WG_width = 0.5e-6;

        double top = Pitch*ff ,etched =Pitch*(1-ff), width = 12_um, Taper_length = 200e-6;


        double mark1 = 20e-6;
        double marker2 = 50e-6, backex = 5e-6;

       BLOCK{
        skip(backex);
        for(int n=0;n<num_periods;n=n+1){

            layer(L_substrateetch);
            sw(etched,width);
            move(top,0,0,NOFLIP);
        }
       };

        layer(L_waveguides);

        BLOCK {
            sw(backex, width);
            sw(num_periods * (top + etched), width);
            //add_O_Port("In", cp, WG_Structure_List["waveguide1"]);
            taper_angle(Taper_length, 0, width, WG_width);
            add_O_Port("out", cp, WG_Structure_List["waveguide1"]);
        }



        BLOCK {
            layer(L_contactlayer);
            double offsssee = 50_um;
            skip(-offsssee);
            sw(backex+num_periods * (top + etched)+Taper_length+2*offsssee, 1.5*width);
        }

    }

    GC_IN_sub::GC_IN_sub(double Pitch1, double ff1,double Pitch2, double ff2): Pitch1(Pitch1), ff1(ff1),Pitch2(Pitch2), ff2(ff2){
        SimpleComponent = true;
        COMPONENT_INIT(Pitch1, ff1,Pitch2, ff2);
    }


    void GC_IN_sub::layout(int l) {

        int num_periods = 20;
        double WG_width = 0.5e-6;

        double top = Pitch1*ff1 ,etched =Pitch1*(1-ff1), width = 12_um, Taper_length = 200e-6-3.72e-6;

        double top2 = Pitch2*ff2 ,etched2 =Pitch2*(1-ff2);

        double mark1 = 20e-6;
        double marker2 = 50e-6, backex = 0e-6;

        BLOCK{
            skip(backex);
            for(int n=0;n<num_periods;n=n+1){

                layer(L_substrateetch);
                sw(etched,width);
                move(top,0,0,NOFLIP);
                sw(etched2,width);
                move(top2,0,0,NOFLIP);
            }
        };

        layer(L_waveguides);

        BLOCK {
            sw(backex, width);
            sw(num_periods * (top + etched+top2+etched2), width);
            //add_O_Port("In", cp, WG_Structure_List["waveguide1"]);
            taper_angle(Taper_length, 0, width, WG_width);
            add_O_Port("out", cp, WG_Structure_List["waveguide1"]);
        }



        BLOCK {
            layer(L_contactlayer);
            double offsssee = 50_um;
            skip(-offsssee);
            sw(backex+num_periods * (top + etched)+Taper_length+2*offsssee, 1.5*width);
        }

    }


    DBR_TP1::DBR_TP1(double DBRw, double DBRein,double DBRtop,double DBRetched,int DBRnum_periods): DBRw(DBRw), DBRein(DBRein), DBRtop(DBRtop), DBRetched(DBRetched), DBRnum_periods(DBRnum_periods){
        SimpleComponent = true;
        COMPONENT_INIT(DBRw,DBRein,DBRtop,DBRetched,DBRnum_periods);
    }

    void DBR_TP1::layout(int l) {

        double WG_width = 0.5e-6, Si_trench = 10e-6;
        double Taper_length = 100e-6,etchwidth = 5e-6, w = DBRw;

        push_cp();
        move(Taper_length,0,0,NOFLIP);
        for(int n=0;n<DBRnum_periods;n=n+1){
            move(DBRtop,0,0,NOFLIP);
            push_cp();
            layer(L_substrateetch);
            move(0,(w/2-DBRein)+etchwidth/2,0,NOFLIP);
            sw(DBRetched,etchwidth);
            pop_cp();

            push_cp();
            layer(L_substrateetch);
            move(0,-((w/2-DBRein)+etchwidth/2),0,NOFLIP);
            sw(DBRetched,5e-6);
            pop_cp();
            move(DBRetched,0,0,NOFLIP);
        }
        pop_cp();

        BLOCK {
            layer(L_contactlayer);
            double offsssee = 50_um;
            skip(-offsssee);
            sw(DBRnum_periods*(DBRtop+DBRetched)+2*Taper_length+2*offsssee, 50*WG_width);
        }
        BLOCK {
            layer(L_waveguides);
            add_O_Port("in", cp, WG_Structure_List["waveguide1"]);
            taper_angle(Taper_length, 0, WG_width, w);
            sw(DBRnum_periods * (DBRtop + DBRetched), w);
            taper_angle(Taper_length, 0, w, WG_width);
            add_O_Port("out", cp, WG_Structure_List["waveguide1"]);
        }
    }


    DBR_TP2::DBR_TP2(double DBRw, double DBRein,double DBRtop,double DBRetched,int DBRnum_periods): DBRw(DBRw), DBRein(DBRein), DBRtop(DBRtop), DBRetched(DBRetched), DBRnum_periods(DBRnum_periods){
        SimpleComponent = true;
        COMPONENT_INIT(DBRw,DBRein,DBRtop,DBRetched,DBRnum_periods);
    }

    void DBR_TP2::layout(int l) {

        double WG_width = 0.5e-6, Si_trench = 10e-6;
        double Taper_length = 100e-6,etchwidth = 0.3e-6, w = DBRw;

        push_cp();
        move(Taper_length,0,0,NOFLIP);
        for(int n=0;n<DBRnum_periods;n=n+1){
            move(DBRtop,0,0,NOFLIP);
            push_cp();
            layer(L_waveguides);
            move(0,DBRein,0,NOFLIP);
            sw(DBRetched,etchwidth);
            pop_cp();

            push_cp();
            layer(L_waveguides);
            move(0,-DBRein,0,NOFLIP);
            sw(DBRetched,etchwidth);
            pop_cp();
            move(DBRetched,0,0,NOFLIP);
        }
        pop_cp();

        BLOCK {
            layer(L_contactlayer);
            double offsssee = 50_um;
            skip(-offsssee);
            sw(DBRnum_periods*(DBRtop+DBRetched)+2*Taper_length+2*offsssee, 50*WG_width);
        }
        BLOCK {
            layer(L_waveguides);
            add_O_Port("in", cp, WG_Structure_List["waveguide1"]);
            taper_angle(Taper_length, 0, WG_width, w);
            sw(DBRnum_periods * (DBRtop + DBRetched), w);
            taper_angle(Taper_length, 0, w, WG_width);
            add_O_Port("out", cp, WG_Structure_List["waveguide1"]);
        }
    }


    SGDBR_TP1::SGDBR_TP1(double DBRw, double DBRein,double DBRtop,double DBRetched,double Z0, int DBRnum_periods, int burst): DBRw(DBRw), DBRein(DBRein), DBRtop(DBRtop), DBRetched(DBRetched), Z0(Z0),DBRnum_periods(DBRnum_periods),burst(burst){
        SimpleComponent = true;
        COMPONENT_INIT(DBRw,DBRein,DBRtop,DBRetched,Z0,DBRnum_periods,burst);
    }

    void SGDBR_TP1::layout(int l) {

        double WG_width = 0.5e-6, Si_trench = 10e-6;
        double Taper_length = 100e-6, etchwidth = 5e-6, w = DBRw;

        BLOCK {
            layer(L_contactlayer);
            double offsssee = 50_um;
            skip(-offsssee);
            sw(Taper_length+burst * (Z0 + 1) * DBRnum_periods * (DBRtop + DBRetched)+Taper_length+2*offsssee, 15*WG_width);
        }
        layer(L_waveguides);
        add_O_Port("in", cp, WG_Structure_List["waveguide1"]);
        taper_angle(Taper_length, 0, WG_width, w);

        push_cp();
        sw(burst * (Z0 + 1) * DBRnum_periods * (DBRtop + DBRetched), w);
        pop_cp();


        for (int n = 0; n < burst; n = n + 1) {

            for (int n = 0; n < DBRnum_periods; n = n + 1) {
                move(DBRtop, 0, 0, NOFLIP);
                push_cp();
                layer(L_substrateetch);
                move(0, (w / 2 - DBRein) + etchwidth / 2, 0, NOFLIP);
                sw(DBRetched, etchwidth);
                pop_cp();

                push_cp();
                layer(L_substrateetch);
                move(0, -((w / 2 - DBRein) + etchwidth / 2), 0, NOFLIP);
                sw(DBRetched, 5e-6);
                pop_cp();
                move(DBRetched, 0, 0, NOFLIP);
            }

            layer(L_waveguides);
            move(Z0 * DBRnum_periods * (DBRtop + DBRetched), 0, 0, NOFLIP);
        }
        layer(L_waveguides);
        taper_angle(Taper_length, 0, w, WG_width);
        add_O_Port("out", cp, WG_Structure_List["waveguide1"]);
    }


    GoVS_Tr::GoVS_Tr(double deviceL, double deviceW,double NanoWdith,double nanopitch,double ffn, double nanogap, double thedta): deviceL(deviceL), deviceW(deviceW), NanoWdith(NanoWdith), nanopitch(nanopitch), ffn(ffn), nanogap(nanogap),thedta(thedta){
        SimpleComponent = true;
        COMPONENT_INIT(deviceL, deviceW, NanoWdith, nanopitch, ffn,nanogap);
    }

    void GoVS_Tr::layout(int l) {


        int oderr = NanoWdith/nanopitch;

        double lno = 0, widt = 0, ln1 = 0, dl = 0,overwg = 3_um;

        double laserRidge = 2_um;
        BLOCK{

            dl = deviceL-2*nanogap;
            for(int n=0;n<oderr;n=n+1)
            {
                layer(L_substrateetch);
                ln1 = tan(RAD(thedta))*nanopitch;
                BLOCK{
                    sw(dl,nanopitch*ffn);
                };
                dl = dl+ln1;
                move(0,nanopitch,0,NOFLIP);
            }
        };
        BLOCK{

            layer(L_Iwaveguides);
            move(-nanogap,NanoWdith/2-nanopitch/2,0,NOFLIP);
            sw(deviceL,NanoWdith+nanogap);
            widt = NanoWdith+nanogap;
            lno = tan(RAD(thedta))*widt;
            move(0,-widt/2,0,NOFLIP);
            triangle(lno,widt,0,widt);

        };


        double laserTaper = 0_um, laserout = 2_um, lasertaperout = 2_um, pvia = 2 , nholegap = 1.5_um;
        BLOCK{
            layer(L_deepetchWG);
            move(-nanogap,NanoWdith/2-nanopitch/2,0,NOFLIP);
            sw(deviceL+(NanoWdith/2+nanogap/2)*tan(RAD(thedta))-laserTaper-laserout,laserRidge);
            taper(laserTaper,laserRidge,lasertaperout);
            sw(laserout,lasertaperout);
            lno = tan(RAD(thedta))*lasertaperout;
            move(0,-lasertaperout/2,0,NOFLIP);
            triangle(lno,lasertaperout,0,lasertaperout);
        };


        BLOCK{
            layer(L_Pmetal);
            move(-nanogap,NanoWdith/2-nanopitch/2,0,NOFLIP);
            //sw(deviceL+(NanoWdith/2+nanogap/2)*tan(RAD(thedta))-laserTaper-laserout,laserRidge);
            sw(10_um,laserRidge);

        };



        BLOCK{
            layer(L_pcontactopen);
            move(-nanogap,NanoWdith/2-nanopitch/2,0,NOFLIP);
            sw(deviceL+(NanoWdith/2+nanogap/2)*tan(RAD(thedta))-laserTaper-laserout,laserRidge*pvia);
            taper(laserTaper,laserRidge,lasertaperout);
            sw(laserout,lasertaperout);
            lno = tan(RAD(thedta))*lasertaperout;
            move(0,-lasertaperout/2,0,NOFLIP);
            triangle(lno,lasertaperout,0,lasertaperout);
        }

//////////////////////////////nhole//////////////////////////////////////////////
        BLOCK{
            layer(L_ncontactopen);
            move(-nanogap,NanoWdith/2-nanopitch/2+nholegap+deviceW/4+laserRidge/2,0,NOFLIP);
            sw(deviceL+(NanoWdith/2+nanogap/2)*tan(RAD(thedta))-laserTaper-laserout,deviceW/2);
            taper(laserTaper,laserRidge,lasertaperout);
            sw(laserout,lasertaperout);
//            lno = tan(RAD(thedta))*lasertaperout;
//            move(0,-lasertaperout/2,0,NOFLIP);
//            triangle(lno,lasertaperout,0,lasertaperout);
        };

        BLOCK{
            layer(L_ncontactopen);
            move(-nanogap,NanoWdith/2-nanopitch/2-nholegap-deviceW/4-laserRidge/2,0,NOFLIP);
            sw(deviceL+(NanoWdith/2+nanogap/2)*tan(RAD(thedta))-laserTaper-laserout,deviceW/2);
            taper(laserTaper,laserRidge,lasertaperout);
            sw(laserout,lasertaperout);
//            lno = tan(RAD(thedta))*lasertaperout;
//            move(0,-lasertaperout/2,0,NOFLIP);
//            triangle(lno,lasertaperout,0,lasertaperout);
        };

//////////////////////////////nhole//////////////////////////////////////////////

//////////////////////////////nvia//////////////////////////////////////////////
        BLOCK{
            layer(L_Ncontactopen);
            move(-nanogap,NanoWdith/2-nanopitch/2+nholegap+laserRidge/2+(deviceW-laserRidge-2*nholegap)/4,0,NOFLIP);
            sw(deviceL+(NanoWdith/2+nanogap/2)*tan(RAD(thedta))-laserTaper-laserout,(deviceW-laserRidge-2*nholegap)/2);
            taper(laserTaper,laserRidge,lasertaperout);
            sw(laserout,lasertaperout);
//            lno = tan(RAD(thedta))*lasertaperout;
//            move(0,-lasertaperout/2,0,NOFLIP);
//            triangle(lno,lasertaperout,0,lasertaperout);
        }

//        //////////////////////////////nvia//////////////////////////////////////////////
//        BLOCK{
//            layer(L_Ncontactopen);
//            move(-nanogap,NanoWdith/2-nanopitch/2-nholegap-laserRidge/2-(deviceW-laserRidge-2*nholegap)/4,0,NOFLIP);
//            sw(deviceL+(NanoWdith/2+nanogap/2)*tan(RAD(thedta))-laserTaper-laserout,(deviceW-laserRidge-2*nholegap)/2);
//            taper(laserTaper,laserRidge,lasertaperout);
//            sw(laserout,lasertaperout);
//            lno = tan(RAD(thedta))*lasertaperout;
//            move(0,-lasertaperout/2,0,NOFLIP);
//            triangle(lno,lasertaperout,0,lasertaperout);
//        }


        double sitaper = 100_um, siIn = 100e-6, siwg = 0.5e-6, bufferin = 2_um;
        BLOCK{
            layer(L_IdeepetchWG);
            move(deviceL+(NanoWdith/2+nanogap/2)*tan(RAD(thedta))-nanogap,NanoWdith/2-nanopitch/2,RAD(-0),NOFLIP);
            move(lno,lasertaperout/2,0,NOFLIP);
            triangle(0, -lasertaperout,-lno,-lasertaperout);
            move(0,-lasertaperout/2,0,NOFLIP);
            sw(bufferin,lasertaperout);
            taper(sitaper,lasertaperout,siwg);
            sw(sitaper,siwg);
        };

    }

    PhaseSi::PhaseSi(double PhaseLength, double heatergap, double heaterwidth): PhaseLength(PhaseLength), heatergap(heatergap), heaterwidth(heaterwidth){
        SimpleComponent = true;
        COMPONENT_INIT(PhaseLength, heatergap, heaterwidth);
    }


    void PhaseSi::layout(int l) {
        double localwg = 0.5_um, EtaperL = 10_um, padL  = 100_um;
        add_O_Port("in", cp, WG_Structure_List["waveguide1"]);
        BLOCK{
        NEW(SW,PhaseLength).place();
            add_O_Port("out", cp, WG_Structure_List["waveguide1"]);
        };

        ///up
        BLOCK {///To metal
            layer(L_Pmetal);
            move(0, heatergap + heaterwidth / 2, RAD(0), NOFLIP);

            BLOCK {///To metal
                sw(PhaseLength, heaterwidth);
                cw((heaterwidth + 2 * heatergap) / 2, -M_PI / 2, heaterwidth);
                BLOCK {
                    BLOCK {
                        taper_angle(EtaperL, RAD(0), heaterwidth, padL);
                        sw(padL, padL);
                    };

                    BLOCK {
                        layer(L_pmetal);
                        taper_angle(EtaperL, RAD(0), heaterwidth, padL);
                        sw(padL, padL);
                    }
                }

                BLOCK {
                    layer(L_pmetal);
                    taper_angle(EtaperL, RAD(0), heaterwidth, padL);
                    sw(padL, padL);
                }
            }
            move(0, 0, RAD(180), NOFLIP);
            cw((heaterwidth + 2 * heatergap) / 2, -M_PI, heaterwidth);

        }

        ///down
        BLOCK {///To metal
            layer(L_Pmetal);
            move(0, -heatergap - heaterwidth / 2, RAD(0), NOFLIP);

            BLOCK {
                sw(PhaseLength, heaterwidth);
                cw((heaterwidth + 2 * heatergap) / 2, M_PI / 2, heaterwidth);
                BLOCK {
                    taper_angle(EtaperL, RAD(0), heaterwidth, padL);
                    sw(padL, padL);
                }

                BLOCK {
                    layer(L_pmetal);
                    taper_angle(EtaperL, RAD(0), heaterwidth, padL);
                    sw(padL, padL);
                }
            }
            move(0, 0, RAD(180), NOFLIP);
            cw((heaterwidth + 2 * heatergap) / 2, -M_PI / 2, heaterwidth);
            BLOCK {
                taper_angle(EtaperL, RAD(0), heaterwidth, padL);
                sw(padL, padL);
            }
            BLOCK {
                layer(L_pmetal);
                taper_angle(EtaperL, RAD(0), heaterwidth, padL);
                sw(padL, padL);
            }


        }
    }


    RingTyp2::RingTyp2(double gap, double radius): gap(gap), radius(radius){
        SimpleComponent = true;
        COMPONENT_INIT(gap, radius);
    }


    void RingTyp2::layout(int l) {

        double R = radius, gap = this->gap, lcoalwg = 0.5_um ,HeaterRing = 2_um;

        double HeaterRatio = 0.6, temp = (1-HeaterRatio)*2*M_PI/4;
        int turning = 6;
        double OverStep = 10_um, EtaperL = 30_um, padL = 100_um, overlapHeater = 1_um,nonheatersession = 6;
        layer(L_waveguides);

        add_O_Port("in", cp, WG_Structure_List["waveguide1"]);
        sw(2*R,lcoalwg);
        add_O_Port("thru", cp, WG_Structure_List["waveguide1"]);
        move(-2*R,-2*gap-2*lcoalwg-2*R,0,NOFLIP);

        add_O_Port("drop", cp, WG_Structure_List["waveguide1"]);
        sw(2*R,lcoalwg);
        add_O_Port("add", cp, WG_Structure_List["waveguide1"]);

        move(-R,gap+lcoalwg,0,NOFLIP);


        BLOCK {

            cw(R, -2 * M_PI, lcoalwg);
        }

        BLOCK {
            layer(L_contactlayer);
            skip(-1.25*R);
            offset(-R);
            sw(2.5*R, 2.5*R);
        }

        ///To metal
        layer(L_Pmetal);

        BLOCK {
            move(R * sin(temp), R - R * cos(temp), temp, NOFLIP);
            ///Heater
            push_layer();
             cw(R, -HeaterRatio / 2 * 2 * M_PI, HeaterRing);
            pop_layer();
            move(-overlapHeater, 0, 0, NOFLIP);
            ////
            BLOCK {
                cw(R / turning, M_PI / 2 - temp, nonheatersession * lcoalwg);
                sw(OverStep, nonheatersession * lcoalwg);
                sw(padL, padL);
            }
            BLOCK {
                layer(L_pmetal);
                cw(R / turning, M_PI / 2 - temp, nonheatersession * lcoalwg);
                sw(OverStep, nonheatersession * lcoalwg);
                sw(padL, padL);
            }
        }

        ///down right pads
        BLOCK {
            move(R * sin(temp), R - R * cos(temp), temp, NOFLIP);
            move(0, 0, -RAD(180), NOFLIP);
            move(-overlapHeater, 0, 0, NOFLIP);
            BLOCK {
                cw(R / turning, -M_PI / 2 + temp, nonheatersession * lcoalwg);
                sw(OverStep, nonheatersession * lcoalwg);
                taper_angle(EtaperL, RAD(-70), nonheatersession * lcoalwg, padL);
                sw(padL, padL);
            }
            BLOCK {
                layer(L_pmetal);
                cw(R / turning, -M_PI / 2 + temp, nonheatersession * lcoalwg);
                sw(OverStep, nonheatersession * lcoalwg);
                taper_angle(EtaperL, RAD(-70), nonheatersession * lcoalwg, padL);
                sw(padL, padL);
            }
        }


        BLOCK {
            move(0, 0, -RAD(180), NOFLIP);
            move(R * sin(temp), -R + R * cos(temp), -temp, FLIP);

            ///Heater
            push_layer();
            cw(R, -HeaterRatio / 2 * 2 * M_PI, HeaterRing);
            pop_layer();
            move(-overlapHeater, 0, 0, NOFLIP);
            BLOCK {
                cw(R / turning, M_PI / 2 - temp, nonheatersession * lcoalwg);
                sw(OverStep, nonheatersession * lcoalwg);
                sw(padL, padL);
            }
            BLOCK {
                layer(L_pmetal);
                cw(R / turning, M_PI / 2 - temp, nonheatersession * lcoalwg);
                sw(OverStep, nonheatersession * lcoalwg);
                sw(padL, padL);
            }
        }

        ///down left pads
        BLOCK {
            move(-R * sin(temp), R - R * cos(temp), -temp, NOFLIP);
                move(0, 0, RAD(0), NOFLIP);
            move(-overlapHeater, 0, 0, NOFLIP);

            BLOCK {
                cw(R / turning, M_PI / 2 - temp, nonheatersession * lcoalwg);
                sw(OverStep, nonheatersession * lcoalwg);
                taper_angle(EtaperL, RAD(70), nonheatersession * lcoalwg, padL);
                sw(padL, padL);
            }

            BLOCK {
                layer(L_pmetal);
                cw(R / turning, M_PI / 2 - temp, nonheatersession * lcoalwg);
                sw(OverStep, nonheatersession * lcoalwg);
                taper_angle(EtaperL, RAD(70), nonheatersession * lcoalwg, padL);
                sw(padL, padL);
            }


            }





    }


    TuableDBRTP1::TuableDBRTP1(double heatergap, double heaterwidth,double DBRw, double DBRein,double DBRtop,double DBRetched,int DBRnum_periods, int side): heatergap(heatergap), heaterwidth(heaterwidth),DBRw(DBRw), DBRein(DBRein), DBRtop(DBRtop), DBRetched(DBRetched), DBRnum_periods(DBRnum_periods),side(side){
        SimpleComponent = true;
        COMPONENT_INIT(heatergap,heaterwidth,DBRw,DBRein,DBRtop,DBRetched,DBRnum_periods,side);
    }

    void TuableDBRTP1::layout(int l) {
        double localwg = 0.5_um, EtaperL = 10_um, padL  = 100_um;
        double WG_width = 0.5e-6, Si_trench = 10e-6;
        double Taper_length = 100e-6,etchwidth = 5e-6, w = DBRw;
        double PhaseLength =  (DBRtop+DBRetched)*DBRnum_periods;

        BLOCK {
            move(Taper_length, 0, 0, NOFLIP);
            for (int n = 0; n < DBRnum_periods; n = n + 1) {
                move(DBRtop, 0, 0, NOFLIP);
                BLOCK {
                    layer(L_substrateetch);
                    move(0, (w / 2 - DBRein) + etchwidth / 2, 0, NOFLIP);
                    sw(DBRetched, etchwidth);
                }
                BLOCK {
                    layer(L_substrateetch);
                    move(0, -((w / 2 - DBRein) + etchwidth / 2), 0, NOFLIP);
                    sw(DBRetched, 5e-6);
                }
                move(DBRetched, 0, 0, NOFLIP);
            }
        }

        BLOCK {
            move(Taper_length, 0, 0, NOFLIP);
            BLOCK {///To metal
                layer(L_Pmetal);
                move(0, heatergap + heaterwidth / 2, RAD(0), NOFLIP);

                BLOCK {///To metal
                    sw(PhaseLength, heaterwidth);
                    cw((heaterwidth + 2 * heatergap) / 2, -M_PI / 2, heaterwidth);

                    BLOCK {
                        taper_angle(EtaperL, RAD(0), heaterwidth, padL);
                        sw(padL, padL);
                    };

                    BLOCK {
                        layer(L_pmetal);
                        taper_angle(EtaperL, RAD(0), heaterwidth, padL);
                        sw(padL, padL);
                    };
                }
                move(0, 0, RAD(180), NOFLIP);
                cw((heaterwidth + 2 * heatergap) / 2, -M_PI, heaterwidth);

            }

            ///down
            BLOCK {///To metal
                layer(L_Pmetal);
                move(0, -heatergap - heaterwidth / 2, RAD(0), NOFLIP);

                BLOCK {
                    sw(PhaseLength, heaterwidth);
                    cw((heaterwidth + 2 * heatergap) / 2, M_PI / 2, heaterwidth);

                    BLOCK {
                        taper_angle(EtaperL, RAD(0), heaterwidth, padL);
                        sw(padL, padL);
                    }

                    BLOCK {
                        layer(L_pmetal);
                        taper_angle(EtaperL, RAD(0), heaterwidth, padL);
                        sw(padL, padL);
                    }
                }


                move(0, 0, RAD(180), NOFLIP);

                    if (side) {
                    cw((heaterwidth + 2 * heatergap) / 2, -M_PI / 2, heaterwidth);
                    BLOCK {
                        taper_angle(EtaperL, RAD(0), heaterwidth, padL);
                        sw(padL, padL);
                    }

                    BLOCK {
                        layer(L_pmetal);
                        taper_angle(EtaperL, RAD(0), heaterwidth, padL);
                        sw(padL, padL);
                    }
                }
            }
        }
        BLOCK {
            layer(L_contactlayer);
            double offsssee = 50_um;
            skip(-offsssee);
            sw(DBRnum_periods*(DBRtop+DBRetched)+2*Taper_length+2*offsssee,50*WG_width);
        }
        BLOCK {
            layer(L_waveguides);
            add_O_Port("in", cp, WG_Structure_List["waveguide1"]);
            taper_angle(Taper_length, 0, WG_width, w);
            sw(DBRnum_periods * (DBRtop + DBRetched), w);
            taper_angle(Taper_length, 0, w, WG_width);
            add_O_Port("out", cp, WG_Structure_List["waveguide1"]);
        }
    }


    TuableSGDBRTP1::TuableSGDBRTP1(double heatergap, double heaterwidth,double DBRw, double DBRein,double DBRtop,double DBRetched,double Z0,int DBRnum_periods, int burst, int side): heatergap(heatergap), heaterwidth(heaterwidth),DBRw(DBRw), DBRein(DBRein), DBRtop(DBRtop), DBRetched(DBRetched), Z0(Z0), DBRnum_periods(DBRnum_periods), burst(burst),side(side){
        SimpleComponent = true;
        COMPONENT_INIT(heatergap,heaterwidth,DBRw,DBRein,DBRtop,DBRetched,DBRnum_periods,side);
    }

    void TuableSGDBRTP1::layout(int l) {
        double localwg = 0.5_um, EtaperL = 50_um, padL  = 100_um;
        double WG_width = 0.5e-6, Si_trench = 10e-6;
        double Taper_length = 20e-6,etchwidth = 5e-6, w = DBRw;
        double PhaseLength =  burst * (Z0 + 1) * DBRnum_periods * (DBRtop + DBRetched);


        BLOCK {
            layer(L_contactlayer);
            double offsssee = 50_um;
            skip(-offsssee);
            sw(Taper_length+burst * (Z0 + 1) * DBRnum_periods * (DBRtop + DBRetched)+Taper_length+2*offsssee, 50*WG_width);
        }

        layer(L_waveguides);
        add_O_Port("in", cp, WG_Structure_List["waveguide1"]);
        taper_angle(Taper_length, 0, WG_width, w);

        BLOCK {
            sw(burst * (Z0 + 1) * DBRnum_periods * (DBRtop + DBRetched), w);
        }

        BLOCK {
            for (int n = 0; n < burst; n = n + 1) {

                for (int n = 0; n < DBRnum_periods; n = n + 1) {
                    move(DBRtop, 0, 0, NOFLIP);
                    BLOCK{
                        layer(L_substrateetch);
                        move(0, (w / 2 - DBRein) + etchwidth / 2, 0, NOFLIP);
                        sw(DBRetched, etchwidth);
                    }

                    BLOCK{
                        layer(L_substrateetch);
                        move(0, -((w / 2 - DBRein) + etchwidth / 2), 0, NOFLIP);
                        sw(DBRetched, 5e-6);
                    }
                move(DBRetched, 0, 0, NOFLIP);
            }

            layer(L_waveguides);
            move(Z0 * DBRnum_periods * (DBRtop + DBRetched), 0, 0, NOFLIP);

            }
            taper_angle(Taper_length, 0, w, WG_width);
            add_O_Port("out", cp, WG_Structure_List["waveguide1"]);
        }

        BLOCK {
            BLOCK {///To metal
                layer(L_Pmetal);
                move(0, heatergap + heaterwidth / 2, RAD(0), NOFLIP);

                BLOCK {///To metal
                    sw(PhaseLength, heaterwidth);
                    cw((heaterwidth + 2 * heatergap) / 2, -M_PI / 2, heaterwidth);

                    BLOCK {
                        taper_angle(EtaperL, RAD(0), heaterwidth, padL);
                        sw(padL, padL);
                    };

                    BLOCK {
                        layer(L_pmetal);
                        taper_angle(EtaperL, RAD(0), heaterwidth, padL);
                        sw(padL, padL);
                    };
                }
                move(0, 0, RAD(180), NOFLIP);
                cw((heaterwidth + 2 * heatergap) / 2, -M_PI, heaterwidth);

            }

            ///down
            BLOCK {///To metal
                layer(L_Pmetal);
                move(0, -heatergap - heaterwidth / 2, RAD(0), NOFLIP);

                BLOCK {
                    sw(PhaseLength, heaterwidth);
                    cw((heaterwidth + 2 * heatergap) / 2, M_PI / 2, heaterwidth);

                    BLOCK {
                        taper_angle(EtaperL, RAD(0), heaterwidth, padL);
                        sw(padL, padL);
                    }

                    BLOCK {
                        layer(L_pmetal);
                        taper_angle(EtaperL, RAD(0), heaterwidth, padL);
                        sw(padL, padL);
                    }
                }


                move(0, 0, RAD(180), NOFLIP);

                if (side) {
                    cw((heaterwidth + 2 * heatergap) / 2, -M_PI / 2, heaterwidth);
                    BLOCK {
                        taper_angle(EtaperL, RAD(0), heaterwidth, padL);
                        sw(padL, padL);
                    }

                    BLOCK {
                        layer(L_pmetal);
                        taper_angle(EtaperL, RAD(0), heaterwidth, padL);
                        sw(padL, padL);
                    }
                }
            }
        }

        }

    ComponentBase & CONNECTOR_SINE_BEND_EBEAM::Connector_Component(PortBase &portBase1, PortBase &portBase2) {
        BLOCK{
            layer(L_contactlayer);
            offset(SIGN((portBase2 - portBase1).y) * 100_um / 2);
            rect((portBase2 - portBase1).x, SIGN((portBase2 - portBase1).y) * 100_um + (portBase2 - portBase1).y, 1, 1);
        };
        return CONNECTOR_SINE_BEND::Connector_Component(portBase1, portBase2);
    }


    MMI1by2::MMI1by2(double mmiL, double mmiW, double Sept, double mmiTpL, double taperW): mmiL(mmiL), mmiW(mmiW), Sept(Sept), mmiTpL(mmiTpL), taperW(taperW){
        SimpleComponent = true;
        COMPONENT_INIT (mmiL, mmiW, Sept, mmiTpL, taperW);
    }


    void MMI1by2::layout(int l) {
        double wg = 0.5_um;


        BLOCK {
            layer(L_contactlayer);
            double offsssee = 20_um;
            skip(-offsssee);
            sw(2*mmiTpL+mmiL+2*offsssee, 5*mmiW);
        }

        add_O_Port("in", cp, WG_Structure_List["waveguide1"]);
        taper(mmiTpL,wg,taperW);
        sw(mmiL,mmiW);

        BLOCK{
            move(0, Sept/2, 0,NOFLIP);
            taper(mmiTpL,taperW,wg);
            add_O_Port("out0", cp, WG_Structure_List["waveguide1"]);

        };

        BLOCK{
            move(0, -Sept/2, 0,NOFLIP);
            taper(mmiTpL,taperW,wg);
            add_O_Port("out1", cp, WG_Structure_List["waveguide1"]);

        };

    }


    MMI2by2::MMI2by2(double mmiL, double mmiW, double Sept, double mmiTpL, double taperW): mmiL(mmiL), mmiW(mmiW), Sept(Sept), mmiTpL(mmiTpL), taperW(taperW){
        SimpleComponent = true;
        COMPONENT_INIT (mmiL, mmiW, Sept, mmiTpL, taperW);
    }


    void MMI2by2::layout(int l) {
        double wg = 0.5_um;


        BLOCK {
            layer(L_contactlayer);
            double offsssee = 20_um;
            skip(-offsssee);
            sw(2*mmiTpL+mmiL+2*offsssee, 5*mmiW);
        }


        BLOCK {
            move(0, -Sept/2, 0,NOFLIP);
            add_O_Port("in0", cp, WG_Structure_List["waveguide1"]);
            taper(mmiTpL,wg,taperW);
        }
        BLOCK {
            move(0, Sept / 2, 0, NOFLIP);
            add_O_Port("in1", cp, WG_Structure_List["waveguide1"]);
            taper(mmiTpL, wg, taperW);
        }
        move(mmiTpL, 0, 0, NOFLIP);
        sw(mmiL,mmiW);

        BLOCK{
            move(0, Sept/2, 0,NOFLIP);
            taper(mmiTpL,taperW,wg);
            add_O_Port("out0", cp, WG_Structure_List["waveguide1"]);

        };

        BLOCK{
            move(0, -Sept/2, 0,NOFLIP);
            taper(mmiTpL,taperW,wg);
            add_O_Port("out1", cp, WG_Structure_List["waveguide1"]);

        };

    }


    SAG_APD::SAG_APD(double deviceL, double deviceW, double gapLL, double gapWW): deviceL(deviceL), deviceW(deviceW), gapLL(gapLL), gapWW(gapWW){
        SimpleComponent = true;
        COMPONENT_INIT (deviceL, deviceW,gapLL,gapWW);
    }


    void SAG_APD::layout(int l) {
        double ration = deviceL/deviceW+2.0,viagap = 0.0_um, metalgap = 0.5e-6, ppadl = 0.3;

        BLOCK{
            sw(deviceL,deviceW);

        };

        BLOCK{
            ////nhole
            layer(L_ncontactopen);
            double NholeEtch = 1.2;
            move(deviceL/2-deviceW/2,0,0,NOFLIP);
            sw(1.2*deviceL-deviceW/2,deviceW*NholeEtch);
        };


        BLOCK{
            ////nvia
            layer(L_Ncontactopen);
            double Nhvia =0.9;
            move(-0,0,0,NOFLIP);
            sw(deviceL/ration-viagap,deviceW*Nhvia);
        };


        BLOCK{
            ////nviaM1
            layer(L_Nmetal);
            double nviaM1 =0.85;
            move(-0,0,0,NOFLIP);
            sw((deviceL/ration-viagap)*nviaM1,deviceW*nviaM1);
        };



        BLOCK{
            ////nmetal
            layer(L_nmetal);
            double Nmetal =1.1;
            move(-deviceL*ppadl+deviceL/ration-viagap+metalgap,0,0,NOFLIP);
            sw(deviceL*ppadl,gapWW);
        };

        BLOCK{

            ////pvia
            layer(L_pcontactopen);
            double pholeEtch = 0.9;
            move(deviceL-deviceL/ration,0,0,NOFLIP);
            sw(deviceL/ration,deviceW*pholeEtch);
        };

        BLOCK{

            ////pviaM2
            layer(L_Pmetal);
            double pviaM2 = 0.85;
            move(deviceL-deviceL/ration,0,0,NOFLIP);
            sw(deviceL/ration,deviceW*pviaM2);
        };

        BLOCK{
            ////pmetal
            layer(L_pmetal);
            double Pmetal =1.1;
            move(deviceL-deviceW/2-metalgap,(gapWW-deviceW)/2-(gapWW-deviceL*ppadl-deviceW)/4,0,NOFLIP);
            sw(deviceL*ppadl,gapWW-(gapWW-deviceL*ppadl-deviceW)/2);
            //sw(deviceL*ppadl,deviceW*Pmetal);
            move(-deviceL*ppadl,gapWW/2-(gapWW-deviceW)/2+(gapWW-deviceL*ppadl-deviceW)/4, RAD(180), NOFLIP);
            sw(gapLL-deviceL*ppadl,deviceL*ppadl);
        };

    }



    TRIANGLE::TRIANGLE(double r): r(r){
        SimpleComponent = true;
        COMPONENT_INIT (r);
    }

    void TRIANGLE::layout(int l) {

        add_O_Port("in", cp, WG_Structure_List["waveguide1"]);
        double angle01 = 54, ixx = 0,iyy = 0, angle02 = 72;
        ixx = r*tan(RAD(angle01))/2;
        iyy = r*tan(RAD(angle02))/2;
        layer(L_waveguides);
        taper(ixx,0,r);
        taper(iyy,r,0);

    }

    TRIANGLE_a::TRIANGLE_a(double r,double angle01, double angle02): r(r),angle01(angle01),angle02(angle02){
        SimpleComponent = true;
        COMPONENT_INIT (r,angle01,angle02);
    }

    void TRIANGLE_a::layout(int l) {

        add_O_Port("in", cp, WG_Structure_List["waveguide1"]);
        double ixx = 0,iyy = 0;
        ixx = r*tan(RAD(angle01))/2;
       // iyy = r*tan(RAD(angle02))/2;
        layer(L_waveguides);
        taper(ixx,0,r);
      //  taper(iyy,r,0);

    }


    Hex::Hex(double r): r(r){
        SimpleComponent = true;
        COMPONENT_INIT (r);
    }

    void Hex::layout(int l) {

        add_O_Port("in", cp, WG_Structure_List["waveguide1"]);
        NEW(TRIANGLE_a,r,60,72).place();
        move(0,0,RAD(60),NOFLIP);
        NEW(TRIANGLE_a,r,60,72).place();
        move(0,0,RAD(60),NOFLIP);
        NEW(TRIANGLE_a,r,60,72).place();
        move(0,0,RAD(60),NOFLIP);
        NEW(TRIANGLE_a,r,60,72).place();
        move(0,0,RAD(60),NOFLIP);
        NEW(TRIANGLE_a,r,60,72).place();
        move(0,0,RAD(60),NOFLIP);
        NEW(TRIANGLE_a,r,60,72).place();

    }


    Snow::Snow(double arm, double width, double gapp): arm(arm),width(width),gapp(gapp){
        SimpleComponent = true;
        COMPONENT_INIT (arm,width,gapp);
    }

    void Snow::layout(int l) {

        add_O_Port("in", cp, WG_Structure_List["waveguide1"]);
        BLOCK{
            move(-arm-gapp/2,0,0,NOFLIP);
            sw(arm,width);
            skip(gapp);
            sw(arm,width);
        };

        move(0,0,RAD(60),NOFLIP);

        BLOCK{
            move(-arm-gapp/2,0,0,NOFLIP);
            sw(arm,width);
            skip(gapp);
            sw(arm,width);
        };

        move(0,0,RAD(60),NOFLIP);

        BLOCK{
            move(-arm-gapp/2,0,0,NOFLIP);
            sw(arm,width);
            skip(gapp);
            sw(arm,width);
        };

    }




    CHINA::CHINA(double baseR): baseR(baseR){
        SimpleComponent = true;
        COMPONENT_INIT (baseR);
    }

    void CHINA::layout(int l) {

        double gridd = (tan(RAD(54))+tan(RAD(72)))*0.5*baseR, rotata = 0,edge = 0.5_um;
        BLOCK{

            move(0,0,RAD(18),NOFLIP);
            NEW(TRIANGLE,baseR*3).place();

        };
        BLOCK{
            move(0,0,RAD(90),NOFLIP);
            NEW(TRIANGLE,baseR*3).place();
        };
        BLOCK{
            move(0,0,RAD(162),NOFLIP);

            NEW(TRIANGLE,baseR*3).place();

            BLOCK {
                layer(L_Pmetal);
                move(0, 0, RAD(18), NOFLIP);
                move(-25*gridd, 5*gridd, RAD(0), NOFLIP);
                sw(30*gridd,20*gridd);
            }

            BLOCK {
                layer(L_pmetal);
                move(0, 0, RAD(18), NOFLIP);
                move(-25*gridd-edge, 5*gridd, RAD(0), NOFLIP);

                add_O_Port("in0", cp, WG_Structure_List["waveguide1"]);
                sw(30*gridd+2*edge,20*gridd+2*edge);
                add_O_Port("out", cp, WG_Structure_List["waveguide1"]);
            }


            BLOCK {
                move(0, 0, RAD(48.96375), NOFLIP);
                move(-4.8395 * gridd, 0, RAD(0), NOFLIP);

                BLOCK {
                    move(0, 0, RAD(rotata), NOFLIP);
                    NEW(TRIANGLE, baseR).place();
                };
                BLOCK {
                    move(0, 0, RAD(rotata + 72), NOFLIP);
                    NEW(TRIANGLE, baseR).place();
                };
                BLOCK {
                    move(0, 0, RAD(rotata + 72 * 2), NOFLIP);
                    NEW(TRIANGLE, baseR).place();
                };
                BLOCK {
                    move(0, 0, RAD(rotata + 72 * 3), NOFLIP);
                    NEW(TRIANGLE, baseR).place();
                };
                BLOCK {
                    move(0, 0, RAD(rotata + 72 * 4), NOFLIP);
                    NEW(TRIANGLE, baseR).place();
                };
            }


            BLOCK {
                move(0, 0, RAD(26.130), NOFLIP);
                move(-6.071 * gridd, 0, RAD(0), NOFLIP);

                BLOCK {
                    move(0, 0, RAD(rotata), NOFLIP);
                    NEW(TRIANGLE, baseR).place();
                };
                BLOCK {
                    move(0, 0, RAD(rotata + 72), NOFLIP);
                    NEW(TRIANGLE, baseR).place();
                };
                BLOCK {
                    move(0, 0, RAD(rotata + 72 * 2), NOFLIP);
                    NEW(TRIANGLE, baseR).place();
                };
                BLOCK {
                    move(0, 0, RAD(rotata + 72 * 3), NOFLIP);
                    NEW(TRIANGLE, baseR).place();
                };
                BLOCK {
                    move(0, 0, RAD(rotata + 72 * 4), NOFLIP);
                    NEW(TRIANGLE, baseR).place();
                };
            }


            BLOCK {
                move(0, 0, RAD(2.054604), NOFLIP);
                move(-6.48 * gridd, 0, RAD(0), NOFLIP);

                BLOCK {
                    move(0, 0, RAD(rotata), NOFLIP);
                    NEW(TRIANGLE, baseR).place();
                };
                BLOCK {
                    move(0, 0, RAD(rotata + 72), NOFLIP);
                    NEW(TRIANGLE, baseR).place();
                };
                BLOCK {
                    move(0, 0, RAD(rotata + 72 * 2), NOFLIP);
                    NEW(TRIANGLE, baseR).place();
                };
                BLOCK {
                    move(0, 0, RAD(rotata + 72 * 3), NOFLIP);
                    NEW(TRIANGLE, baseR).place();
                };
                BLOCK {
                    move(0, 0, RAD(rotata + 72 * 4), NOFLIP);
                    NEW(TRIANGLE, baseR).place();
                };
            }


            BLOCK {
                move(0, 0, RAD(-20.65980825), NOFLIP);
                move(-5.4031 * gridd, 0, RAD(0), NOFLIP);

                BLOCK {
                    move(0, 0, RAD(rotata), NOFLIP);
                    NEW(TRIANGLE, baseR).place();
                };
                BLOCK {
                    move(0, 0, RAD(rotata + 72), NOFLIP);
                    NEW(TRIANGLE, baseR).place();
                };
                BLOCK {
                    move(0, 0, RAD(rotata + 72 * 2), NOFLIP);
                    NEW(TRIANGLE, baseR).place();
                };
                BLOCK {
                    move(0, 0, RAD(rotata + 72 * 3), NOFLIP);
                    NEW(TRIANGLE, baseR).place();
                };
                BLOCK {
                    move(0, 0, RAD(rotata + 72 * 4), NOFLIP);
                    NEW(TRIANGLE, baseR).place();
                };
            }

        };
        BLOCK{
            move(0,0,RAD(234),NOFLIP);
            NEW(TRIANGLE,baseR*3).place();
        };
        BLOCK{
            move(0,0,RAD(306),NOFLIP);
            NEW(TRIANGLE,baseR*3).place();
        };

    }


    SAG_FP::SAG_FP(double deviceL, double deviceW, double nanogap, double laserRidge,double contrrolangle): deviceL(deviceL),deviceW(deviceW),nanogap(nanogap),laserRidge(laserRidge),contrrolangle(contrrolangle){
        SimpleComponent = true;
        COMPONENT_INIT (deviceL, deviceW,nanogap,laserRidge,contrrolangle);
    }

    void SAG_FP::layout(int l) {

        double ridgeshift = 0,laserTaper = 0_um, laserout = 2_um, lasertaperout = 2_um, pcontact = 0.6, pvia =0.7, nholegap = 1_um, nviagap = 0.15_um;
        double padwidth = 40_um, padgap = 15_um, nmetalmiddle = 30_um, nmetalmiddlegap = 3_um, thedta = 20,lno = 0;


        BLOCK{
            add_O_Port("in0", cp, WG_Structure_List["waveguide1"]);
            layer(L_waveguides);
            move(0,0,0,NOFLIP);
            sw(deviceL,deviceW);
            add_O_Port("out0", cp, WG_Structure_List["waveguide1"]);

            if(contrrolangle){
        lno = tan(RAD(thedta))*deviceW;
        move(0,-deviceW/2,0,NOFLIP);
        triangle(lno,deviceW,0,deviceW);

            }

        };
        BLOCK{


            layer(L_deepetchWG);
            move(-nanogap,ridgeshift,0,NOFLIP);
            sw(deviceL+2*nanogap,laserRidge);

//        sw(deviceL+(deviceW)*tan(RAD(thedta))-laserTaper-laserout,laserRidge);
//        taper(laserTaper,laserRidge,lasertaperout);
//        sw(laserout,lasertaperout);
//        lno = tan(RAD(thedta))*lasertaperout;
//        move(0,-lasertaperout/2,0,NOFLIP);
//        triangle(lno,lasertaperout,0,lasertaperout);
        };

//////////////////////////////pcontact//////////////////////////////////////////////

        BLOCK{
            layer(L_pmetal);
            move(-nanogap,ridgeshift,0,NOFLIP);
            sw(deviceL+2*nanogap,laserRidge*pvia);

        };


        BLOCK{
            layer(L_pcontactopen);
            move(-nanogap,ridgeshift,0,NOFLIP);
            sw(deviceL/8*2+nanogap,laserRidge*pcontact);
            move(deviceL/8*4,0,0,NOFLIP);
            sw(deviceL/8*2+nanogap,laserRidge*pcontact);
        };

//
//
//////////////////////////////nhole//////////////////////////////////////////////
        BLOCK{

            BLOCK{
                layer(L_ncontactopen);
                move(0,deviceW/4+laserRidge/2+nholegap,0,NOFLIP);
                sw(deviceL,deviceW/2);
            };
//        sw(deviceL+(deviceW)*tan(RAD(thedta))-laserTaper-laserout,deviceW/2);
//        taper(laserTaper,laserRidge,lasertaperout);
//        sw(laserout,lasertaperout);
//        lno = tan(RAD(thedta))*lasertaperout;
//        move(0,-lasertaperout/2,0,NOFLIP);
//        triangle(lno,lasertaperout,0,lasertaperout);
        };


        //////////////////////////////nhole//////////////////////////////////////////////
        BLOCK{
            layer(L_ncontactopen);
            move(0,-deviceW/4-laserRidge/2-nholegap,0,NOFLIP);
            sw(deviceL,deviceW/2);
//        sw(deviceL+(deviceW)*tan(RAD(thedta))-laserTaper-laserout,deviceW/2);
//        taper(laserTaper,laserRidge,lasertaperout);
//        sw(laserout,lasertaperout);
//            lno = tan(RAD(thedta))*lasertaperout;
//            move(0,-lasertaperout/2,0,NOFLIP);
//            triangle(lno,lasertaperout,0,lasertaperout);
        };

        //////////////////////////////ncontact//////////////////////////////////////////////
        BLOCK{
            layer(L_nmetal);
            move(0,deviceW/4+laserRidge/2+nholegap,0,NOFLIP);
            sw(deviceL,deviceW/2);
//        sw(deviceL+(deviceW)*tan(RAD(thedta))-laserTaper-laserout,deviceW/2);
//        taper(laserTaper,laserRidge,lasertaperout);
//        sw(laserout,lasertaperout);
//        lno = tan(RAD(thedta))*lasertaperout;
//        move(0,-lasertaperout/2,0,NOFLIP);
//        triangle(lno,lasertaperout,0,lasertaperout);
        };


        //////////////////////////////ncontact//////////////////////////////////////////////
        BLOCK{
            layer(L_nmetal);
            move(0,-deviceW/4-laserRidge/2-nholegap,0,NOFLIP);
            sw(deviceL,deviceW/2);
//        sw(deviceL+(deviceW)*tan(RAD(thedta))-laserTaper-laserout,deviceW/2);
//        taper(laserTaper,laserRidge,lasertaperout);
//        sw(laserout,lasertaperout);
//            lno = tan(RAD(thedta))*lasertaperout;
//            move(0,-lasertaperout/2,0,NOFLIP);
//            triangle(lno,lasertaperout,0,lasertaperout);
        };
//
//    BLOCK{
//        layer(L_ncontactopen);
//        move(-nanogap,NanoWdith/2-nanopitch/2-nholegap-deviceW/4-laserRidge/2,0,NOFLIP);
//        sw(deviceL+(deviceW)*tan(RAD(thedta))-laserTaper-laserout,deviceW/2);
//        taper(laserTaper,laserRidge,lasertaperout);
//        sw(laserout,lasertaperout);
////            lno = tan(RAD(thedta))*lasertaperout;
////            move(0,-lasertaperout/2,0,NOFLIP);
////            triangle(lno,lasertaperout,0,lasertaperout);
//    };
//
//
//////////////////////////////nvia//////////////////////////////////////////////
        BLOCK{
            BLOCK{
                layer(L_Pmetal);
                move(deviceL/8*3-nmetalmiddlegap,0,0,NOFLIP);
                sw(deviceL/4+nmetalmiddlegap*2,nmetalmiddle);

            };

            layer(L_Ncontactopen);
            move(deviceL/8*3,deviceW/4+laserRidge/2+nholegap+nviagap,0,NOFLIP);
            sw(deviceL/4,deviceW/2);


//        taper(laserTaper,laserRidge,lasertaperout);
//        sw(laserout,lasertaperout);
//        lno = tan(RAD(thedta))*lasertaperout;
//        move(0,-lasertaperout/2,0,NOFLIP);
//        triangle(lno,lasertaperout,0,lasertaperout);
        }

//////////////////////////////nvia//////////////////////////////////////////////
        BLOCK{
            layer(L_Ncontactopen);
            move(-0,-deviceW/4-laserRidge/2-nholegap-nviagap,0,NOFLIP);
            sw(deviceL,deviceW/2);
//            taper(laserTaper,laserRidge,lasertaperout);
//            sw(laserout,lasertaperout);
//            lno = tan(RAD(thedta))*lasertaperout;
//            move(0,-lasertaperout/2,0,NOFLIP);
//            triangle(lno,lasertaperout,0,lasertaperout);
        }


//////////////////////////////Pad metal//////////////////////////////////////////////
        BLOCK{
            layer(L_Pmetal);
            move(-0,-nholegap-nviagap-padwidth/2-laserRidge/2,0,NOFLIP);
            sw(deviceL,padwidth);
//            taper(laserTaper,laserRidge,lasertaperout);
//            sw(laserout,lasertaperout);
//            lno = tan(RAD(thedta))*lasertaperout;
//            move(0,-lasertaperout/2,0,NOFLIP);
//            triangle(lno,lasertaperout,0,lasertaperout);
        }

//////////////////////////////Pad metal//////////////////////////////////////////////
        BLOCK {
            layer(L_Pmetal);
            move(0, padwidth / 2-laserRidge/2 , 0, NOFLIP);
            sw(deviceL * 3 / 8-padgap, padwidth);
            move(0, padgap, 0, NOFLIP);
            sw(deviceL * 2 / 8 + 2 * padgap, padwidth - 2 * padgap);

            move(0, -padgap , 0, NOFLIP);
            sw(deviceL * 3 / 8-padgap, padwidth);
//            taper(laserTaper,laserRidge,lasertaperout);
//            sw(laserout,lasertaperout);
//            lno = tan(RAD(thedta))*lasertaperout;
//            move(0,-lasertaperout/2,0,NOFLIP);
//            triangle(lno,lasertaperout,0,lasertaperout);
        }

    }

    APD_single::APD_single(double cirw, double P_pad, double nholew, double nholerate,double nviarate, double ncover, double ncoverL): cirw(cirw),P_pad(P_pad),nholew(nholew),nholerate(nholerate),nviarate(nviarate),ncover(ncover),ncoverL(ncoverL){
        SimpleComponent = true;
        COMPONENT_INIT (cirw,P_pad, nholew, nholerate,nviarate, ncover,ncoverL);
    }

    void APD_single::layout(int l) {

        BLOCK{

            disc(cirw);

        };

        BLOCK {
            layer(L_polcomp);
            disc(cirw-P_pad);
        }

        BLOCK {
            layer(L_ncontactopen);
            move(0,2*sin(RAD(45))*nholerate*cirw,RAD(-45),NOFLIP);
            skip(nholerate*cirw);
            disc(nholew/2);
            cw(nholerate*cirw, RAD(270),nholew);
            disc(nholew/2);
        }

        BLOCK {

            double  narrncontact = 0.8;
            layer(L_nmetal);
            move(0,2*sin(RAD(45))*nholerate*cirw,RAD(-45),NOFLIP);
            skip(nholerate*cirw);
            disc(narrncontact*nholew/2);
            cw(nholerate*cirw, RAD(270),nholew*narrncontact);
            disc(nholew*narrncontact/2);
        }

        BLOCK {
            layer(L_Ncontactopen);
            move(0,2*sin(RAD(45))*nholerate*cirw,RAD(-45),NOFLIP);
            skip(nholerate*cirw);
            disc(nholew/2*nviarate);
            cw(nholerate*cirw, RAD(270),nholew*nviarate);
            disc(nholew/2*nviarate);
        }


        BLOCK {
            layer(L_Pmetal);
            circle(P_pad,cirw-P_pad/2);
        }

        BLOCK {
            layer(L_Pmetal);
            move(0,0,RAD(90),NOFLIP);
            sw(5*cirw,2*cirw);
            disc(50_um);
        }


        BLOCK {

            nviarate = 1.5;
            layer(L_Pmetal);
            move(0,2*sin(RAD(45))*nholerate*cirw,RAD(-45),NOFLIP);
            skip(nholerate*cirw);
            disc(nholew/2*nviarate);
            cw(nholerate*cirw, RAD(270),nholew*nviarate);
            disc(nholew/2*nviarate);
        }


    }


    PD_pixel::PD_pixel(double cirw, double cirr): cirw(cirw),cirr(cirr){
        SimpleComponent = true;
        COMPONENT_INIT (cirw,cirr);
    }

    void PD_pixel::layout(int l) {

        add_O_Port("in", cp, WG_Structure_List["waveguide1"]);

        BLOCK{

            layer(L_Pcontactopen);
            disc(cirw);

        };
        BLOCK{

            layer(L_pcontactopen);
            disc(cirw);

        };

        BLOCK{
            double wetetchgap = -1_um;
            layer(L_Polcomp);
            disc(cirw-wetetchgap);

        };
        BLOCK{

            layer(L_ncontactopen);
            circle(1.5*cirw,cirr);

        };

        BLOCK{
            double shrinkn = 0.85;
            layer(L_nmetal);
            circle(shrinkn*cirw,cirr);

        };

        BLOCK{
            double shrinkn = 0.8;
            layer(L_Ncontactopen);
            circle(shrinkn*cirw,cirr);

        };


        BLOCK{
            double shrinkn = 0.9;
            layer(L_Pmetal);
            circle(shrinkn*cirw,cirr/shrinkn);

        };

        BLOCK{

            layer(L_Pmetal);
            disc(cirw);

        };
    }


END_IMPLEMENT_NEW_PDK(PDK_Xtech)