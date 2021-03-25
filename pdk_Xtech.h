//
// Created by Yuan on 2018/11/8.
//

#ifndef JK_EXTENSION_PDK_DEMO_H
#define JK_EXTENSION_PDK_DEMO_H

#include "IPL_Extension.h"
#include "pdk.h"
#include "technology.h"




DECLARE_NEW_PDK(PDK_Xtech)


    DECLARE_WAVEGUIDES(
            , waveguide1)

    //Declare new component
    DECLARE_NEW_COMPONENT(WG)

        //Declare component parameters
        double WL;

        //Declare component function
        explicit WG(double);
        void layout(int) override;

    END_DECLARE_NEW_COMPONENT(WG)


            //Declare new component
    DECLARE_NEW_COMPONENT(MMI)

        //Declare component parameters

        //Declare component function
        MMI();
        void layout(int) override;

    END_DECLARE_NEW_COMPONENT(MMI)

    //Declare new component
    DECLARE_NEW_COMPONENT(MZI)



        //Declare component function
        MZI();
        void layout(int) override;

    END_DECLARE_NEW_COMPONENT(MZI)

    //Declare new component
    DECLARE_NEW_COMPONENT(STEPPER_1_F)

        //Declare component parameters

        //Declare component function
        STEPPER_1_F();
        void layout(int) override;

    END_DECLARE_NEW_COMPONENT(STEPPER_1_F)
    //Declare new component
    DECLARE_NEW_COMPONENT(STEPPER_1)

        //Declare component parameters

        //Declare component function
        STEPPER_1();
        void layout(int) override;

    END_DECLARE_NEW_COMPONENT(STEPPER_1)

    //Declare new component
    DECLARE_NEW_COMPONENT(STEPPER_2)

        //Declare component parameters

        //Declare component function
        STEPPER_2();
        void layout(int) override;

    END_DECLARE_NEW_COMPONENT(STEPPER_2)

    //Declare new component
    DECLARE_NEW_COMPONENT(RingTyp1)

        //Declare component parameters
        double gap, radius;

        //Declare component function
        explicit RingTyp1(double, double);
        void layout(int) override;

    END_DECLARE_NEW_COMPONENT(RingTyp1)

    //Declare new component
    DECLARE_NEW_COMPONENT(RingTyp2)

        //Declare component parameters
        double gap, radius;

        //Declare component function
        explicit RingTyp2(double, double);
        void layout(int) override;

    END_DECLARE_NEW_COMPONENT(RingTyp1)
//Declare new component
    DECLARE_NEW_COMPONENT(EBL_LOCAL_MARK_TEMP)

        //Declare component parameters
        double ScanFieldSize, ArmLength, Inverse;

        //Declare component function
        explicit EBL_LOCAL_MARK_TEMP(double, double, double);
        void layout(int) override;

    END_DECLARE_NEW_COMPONENT(EBL_LOCAL_MARK_TEMP)


    //Declare new component
    DECLARE_NEW_COMPONENT(GC_IN)

        //Declare component parameters
        double Pitch, ff;

        //Declare component function
        explicit GC_IN(double, double);
        void layout(int) override;

    END_DECLARE_NEW_COMPONENT(GC_IN)

    //Declare new component
    DECLARE_NEW_COMPONENT(GC_AP_9)

        //Declare component parameters
        double Pitch, ff;

        //Declare component function
        explicit GC_AP_9(double, double);
        void layout(int) override;

    END_DECLARE_NEW_COMPONENT(GC_AP_9)
    //Declare new component
    DECLARE_NEW_COMPONENT(GC_IN_sub)

        //Declare component parameters
        double Pitch1, ff1,Pitch2, ff2;

        //Declare component function
        explicit GC_IN_sub(double, double,double, double);
        void layout(int) override;

    END_DECLARE_NEW_COMPONENT(GC_IN_sub)

    //Declare new component
    DECLARE_NEW_COMPONENT(DBR_TP1)

        //Declare component parameters
        double DBRw, DBRein,DBRtop,DBRetched;
        int DBRnum_periods;
        //Declare component function
        explicit DBR_TP1(double,double,double,double,int);
        void layout(int) override;

    END_DECLARE_NEW_COMPONENT(DBR_TP1)


    //Declare new component
    DECLARE_NEW_COMPONENT(DBR_TP2)

        //Declare component parameters
        double DBRw, DBRein,DBRtop,DBRetched;
        int DBRnum_periods;
        //Declare component function
        explicit DBR_TP2(double,double,double,double,int);
        void layout(int) override;

    END_DECLARE_NEW_COMPONENT(DBR_TP2)

    //Declare new component
    DECLARE_NEW_COMPONENT(SGDBR_TP1)

        //Declare component parameters
        double DBRw, DBRein,DBRtop,DBRetched,Z0;
        int DBRnum_periods,burst;
        //Declare component function
        explicit SGDBR_TP1(double,double,double,double,double,int,int);
        void layout(int) override;

    END_DECLARE_NEW_COMPONENT(SGDBR_TP1)


    //Declare new component
    DECLARE_NEW_COMPONENT(SINE_BEND_EBL)

        //Declare component parameters
        double gap, radius;
        //Declare component function
        explicit SINE_BEND_EBL(double,double);
        void layout(int) override;

    END_DECLARE_NEW_COMPONENT(SINE_BEND_EBL)



    //Declare new component
    DECLARE_NEW_COMPONENT(CW_EBL)

        //Declare component parameters
        double gap, radius;
        //Declare component function
        explicit CW_EBL(double,double);
        void layout(int) override;

    END_DECLARE_NEW_COMPONENT(CW_EBL)

    //Declare new component
    DECLARE_NEW_COMPONENT(CW_EBL_180)

        //Declare component parameters
        double gap, radius;
        //Declare component function
        explicit CW_EBL_180(double,double);
        void layout(int) override;

    END_DECLARE_NEW_COMPONENT(CW_EBL_180)


    //Declare new component
    DECLARE_NEW_COMPONENT(SW_EBL)

        //Declare component parameters
        double gap;
        //Declare component function
        explicit SW_EBL(double);
        void layout(int) override;

    END_DECLARE_NEW_COMPONENT(SW_EBL)

    //Declare new component
    DECLARE_NEW_COMPONENT(GoVS_Tr)

        //Declare component parameters
        double deviceL, deviceW, NanoWdith, nanopitch, ffn, nanogap,thedta;
        //Declare component function
        explicit GoVS_Tr(double,double,double,double,double,double,double);
        void layout(int) override;

    END_DECLARE_NEW_COMPONENT(GoVS_Tr)

    //Declare new component
    DECLARE_NEW_COMPONENT(PhaseSi)

        //Declare component parameters
        double PhaseLength, heatergap, heaterwidth;
        //Declare component function
        explicit PhaseSi(double,double,double);

        void layout(int) override;

    END_DECLARE_NEW_COMPONENT(PhaseSi)

    //Declare new component
    DECLARE_NEW_COMPONENT(TuableDBRTP1)

        //Declare component parameters
        double heatergap,heaterwidth,DBRw, DBRein,DBRtop,DBRetched;
        int DBRnum_periods,side;
        //Declare component function
        explicit TuableDBRTP1(double,double,double,double,double,double,int,int);

        void layout(int) override;

    END_DECLARE_NEW_COMPONENT(TuableDBRTP1)


    //Declare new component
    DECLARE_NEW_COMPONENT(TuableSGDBRTP1)

        //Declare component parameters
        double heatergap,heaterwidth,DBRw, DBRein,DBRtop,DBRetched,Z0;
        int DBRnum_periods,burst,side;
        //Declare component function
        explicit TuableSGDBRTP1(double,double,double,double,double,double,double,int,int,int);

        void layout(int) override;

    END_DECLARE_NEW_COMPONENT(TuableSGDBRTP1)


    DECLARE_NEW_COMPONENT(CONNECTOR_SINE_BEND_EBEAM, CONNECTOR_SINE_BEND)
        ComponentBase & Connector_Component(PortBase &, PortBase &) override;
    END_DECLARE_NEW_COMPONENT(CONNECTOR_SINE_BEND_EBEAM)


    //Declare new component
    DECLARE_NEW_COMPONENT(MMI1by2)

        //Declare component parameters
        double mmiL, mmiW, Sept, mmiTpL, taperW;
        //Declare component function
        explicit MMI1by2(double,double,double,double,double);

        void layout(int) override;

    END_DECLARE_NEW_COMPONENT(MMI1by2)

    //Declare new component
    DECLARE_NEW_COMPONENT(MMI2by2)

        //Declare component parameters
        double mmiL, mmiW, Sept, mmiTpL, taperW;
        //Declare component function
        explicit MMI2by2(double,double,double,double,double);

        void layout(int) override;

    END_DECLARE_NEW_COMPONENT(MMI2by2)

    //Declare new component
    DECLARE_NEW_COMPONENT(TRIANGLE)

        //Declare component parameters
        double r;
        //Declare component function
        explicit TRIANGLE(double);

        void layout(int) override;

    END_DECLARE_NEW_COMPONENT(TRIANGLE)

    //Declare new component
    DECLARE_NEW_COMPONENT(TRIANGLE_a)

        //Declare component parameters
        double r,angle01,angle02;
        //Declare component function
        explicit TRIANGLE_a(double,double,double);

        void layout(int) override;

    END_DECLARE_NEW_COMPONENT(TRIANGLE_a)

    //Declare new component
    DECLARE_NEW_COMPONENT(Snow)

        //Declare component parameters
        double arm,width,gapp;
        //Declare component function
        explicit Snow(double,double,double);

        void layout(int) override;

    END_DECLARE_NEW_COMPONENT(Snow)

    //Declare new component
    DECLARE_NEW_COMPONENT(Hex)

        //Declare component parameters
        double r;
        //Declare component function
        explicit Hex(double);

        void layout(int) override;

    END_DECLARE_NEW_COMPONENT(Hex)


    //Declare new component
    DECLARE_NEW_COMPONENT(CHINA)

        //Declare component parameters
        double baseR;
        //Declare component function
        explicit CHINA(double);

        void layout(int) override;

    END_DECLARE_NEW_COMPONENT(CHINA)


//    //Declare new component
//    DECLARE_NEW_COMPONENT(Subtrench)
//
//        //Declare component parameters
//        double baseR;
//        //Declare component function
//        explicit CHINA(double);
//
//        void layout(int) override;
//
//    END_DECLARE_NEW_COMPONENT(Subtrench)





    //Declare new component
    DECLARE_NEW_COMPONENT(SAG_APD)

        //Declare component parameters
        double deviceL, deviceW,gapLL,gapWW;
        //Declare component function
        explicit SAG_APD(double,double,double,double);
        void layout(int) override;

    END_DECLARE_NEW_COMPONENT(SAG_APD)

    //Declare new component
    DECLARE_NEW_COMPONENT(SAG_FP)

        //Declare component parameters
        double deviceL,deviceW,nanogap,laserRidge,contrrolangle;
        //Declare component function
        explicit SAG_FP(double,double,double,double,double);
        void layout(int) override;

    END_DECLARE_NEW_COMPONENT(SAG_FP)

    //Declare new component
    DECLARE_NEW_COMPONENT(APD_single)

        //Declare component parameters
        double cirw,P_pad, nholew, nholerate,nviarate, ncover,ncoverL;
        //Declare component function
        explicit APD_single(double,double,double,double,double,double,double);
        void layout(int) override;

    END_DECLARE_NEW_COMPONENT(APD_single)


    //Declare new component
    DECLARE_NEW_COMPONENT(PD_pixel)

        //Declare component parameters
        double cirw,cirr;
        //Declare component function
        explicit PD_pixel(double,double);
        void layout(int) override;

    END_DECLARE_NEW_COMPONENT(PD_pixel)



END_DECLARE_NEW_PDK(PDK_Xtech)

#endif //JK_EXTENSION_PDK_DEMO_H
