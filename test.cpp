//
//

#include "IPL_Extension.h"
#include <string>
#include <vector>
#include <utility>


//#define GDS_FILENAME "mask_example.gds"
//#define MASK_NAME "JK_Extension"

#include "pdk_Xtech.h"

LOAD_PDK(PDK_Xtech);


void mask(int);

/* DO NOT MODIFY */
int main(int argc, char **argv) {
    setfont((char *)"caps.plf");
    msk_init();
    msk_add_sublayout(MASK_NAME, mask);
    msk_export(GDS_FILENAME);
    update_KLayout((char *)"KLayout 0.24.10");
}




void mask(int i) {

    double DieL =5000_um, DieW = 5000_um;
    double shiftx = 200_um, shifty = 90_um, stepperfine = 200e-6;

    BLOCK {
        skip(-DieL / 2);
        layer(L_Cleavemarks);
        sw(DieL, DieW);
    };
    BLOCK {
        org(-DieL / 2 + shiftx, DieW / 2 - shifty, 0, 0);
        NEW(STEPPER_1).place();
        skip(stepperfine);
        NEW(STEPPER_2).place();
        skip(stepperfine);
        NEW(EBL_LOCAL_MARK_TEMP, 100_um, 100_um, 1).place();

        org(-DieL / 2 + 4 * shiftx, DieW / 2 - shifty, 0, 0);
        NEW(STEPPER_1).place();
        skip(stepperfine);
        NEW(STEPPER_2).place();
        skip(stepperfine);
        NEW(EBL_LOCAL_MARK_TEMP, 100_um, 100_um, 0).place();

        org(DieL / 2 - shiftx, DieW / 2 - shifty, 0, 0);
        NEW(STEPPER_1).place();
        skip(-stepperfine);
        NEW(STEPPER_2).place();
        skip(-stepperfine);
        NEW(EBL_LOCAL_MARK_TEMP, 100_um, 100_um, 1).place();

        org(DieL / 2 - 4 * shiftx, DieW / 2 - shifty, 0, 0);
        NEW(STEPPER_1).place();
        skip(-stepperfine);
        NEW(STEPPER_2).place();
        skip(-stepperfine);
        NEW(EBL_LOCAL_MARK_TEMP, 100_um, 100_um, 0).place();

        org(-DieL / 2 + shiftx, -DieW / 2 + shifty, 0, 0);
        NEW(STEPPER_1).place();
        skip(stepperfine);
        NEW(STEPPER_2).place();
        skip(stepperfine);
        NEW(EBL_LOCAL_MARK_TEMP, 100_um, 100_um, 1).place();

        org(-DieL / 2 + 4 * shiftx, -DieW / 2 + shifty, 0, 0);
        NEW(STEPPER_1).place();
        skip(stepperfine);
        NEW(STEPPER_2).place();
        skip(stepperfine);
        NEW(EBL_LOCAL_MARK_TEMP, 100_um, 100_um, 0).place();

        org(DieL / 2 - shiftx, -DieW / 2 + shifty, 0, 0);
        NEW(STEPPER_1).place();
        skip(-stepperfine);
        NEW(STEPPER_2).place();
        skip(-stepperfine);
        NEW(EBL_LOCAL_MARK_TEMP, 100_um, 100_um, 1).place();

        org(DieL / 2 - 4 * shiftx, -DieW / 2 + shifty, 0, 0);
        NEW(STEPPER_1).place();
        skip(-stepperfine);
        NEW(STEPPER_2).place();
        skip(-stepperfine);
        NEW(EBL_LOCAL_MARK_TEMP, 100_um, 100_um, 0).place();

    };


    double Ystart = DieW/2, xstart = -DieL/2, xshift  = 600e-6, ydelta = -700e-6;
    double tempXorg = -5477.0_um, tempYorg =-300.00000_um;
    int fdevpointer = 1;
    double deviceL = 125_um, deviceW = 7_um, xalign = 10_um;
    //DBR mirror intilization
    double DBRTaperLength = 30e-6, DBRw =  1e-6 , DBRtop =  0.123e-6, DBRetched =0.123e-6, DBRnum_periods = 300, DBRein =  0.1e-6, DBRst = 200e-6;
    double NanoWdith = 10e-6, nanopitch = 0e-6, ffn = 0.666666666666666666, nanogap  =1e-6;
    int oderr = NanoWdith/nanopitch;
    double pt2 = 0.17_um,ff2 = 0.4, pt1 = 1.187_um,ff1=0.59;

    double R = 52_um, gap = 0.17_um, lcoalwg = 0.5_um;
    double HeaterRatio = 0.6, temp = (1-HeaterRatio)*2*M_PI/4;
    int turning = 6;
    double OverStep = 10_um, EtaperL = 30_um, padL = 100_um, overlapHeater = 1_um,nonheatersession = 6;
    double thedta = 20, tempteta = 0, lno = 0, widt = 0, ln1 = 0, dl = 0,overwg = 3_um, DeviceShift = 200e-6, DeviceXorg = -DieL / 2 + shiftx;
    double laserRidge = 3_um, ridgeshift = -0_um;

    double contrrolangle = 0;
    double cirw = 10_um,cirr = 40_um, rr = 105_um, arm = 10_um, width = 1_um,gapp = 5_um;
    double P_pad = 10_um, nholew = 40_um, nholerate  = 4,nviarate = 0.8, ncover = 3, ncoverL = 8;
    double YdeviceGap = 275_um,YdeviceGap2 = 165_um;
    int everyrow1 = 6,everyrow2 = 10,everyrow = 1;

    ///////////////////////////device intinalzition///////////////////////////
        deviceL = 125_um;
        deviceW = 3.5_um;
        laserRidge = 3_um;
        nanogap = 0;
    ///////////////////////////device intinalzition///////////////////////////

    for(int i = 0;i<everyrow2;i++)

    {
        if ( i % 2 == 1 )
        {
            contrrolangle = 1;
                    }

    org(DeviceXorg, -DieW / 2 + 3*shifty+YdeviceGap2*i, 0, NOFLIP);
    move(0,0,0,FLIP);
        NEW(SAG_FP,deviceL,deviceW,nanogap,laserRidge,contrrolangle).place().O_PORTS["out0"]
                >>NEW(SAG_FP,deviceL,deviceW,nanogap,laserRidge,contrrolangle)
                >>NEW(SAG_FP,deviceL,deviceW,nanogap,laserRidge,contrrolangle)
                >>NEW(SAG_FP,deviceL,deviceW,nanogap,laserRidge,contrrolangle)
                >>NEW(SAG_FP,deviceL,deviceW,nanogap,laserRidge,contrrolangle)
                >>NEW(SAG_FP,deviceL,deviceW,nanogap,laserRidge,contrrolangle)
                >>NEW(SAG_FP,deviceL,deviceW,nanogap,laserRidge,contrrolangle)
                >>NEW(SAG_FP,deviceL,deviceW,nanogap,laserRidge,contrrolangle)
                >>NEW(SAG_FP,deviceL,deviceW,nanogap,laserRidge,contrrolangle)
                >>NEW(SAG_FP,deviceL,deviceW,nanogap,laserRidge,contrrolangle)
                >>NEW(SAG_FP,deviceL,deviceW,nanogap,laserRidge,contrrolangle)
                >>NEW(SAG_FP,deviceL,deviceW,3_um,laserRidge,contrrolangle);


        contrrolangle = 0;
    }

    ///////////////////////////device intinalzition///////////////////////////
        deviceL = 125_um;
        deviceW = 25_um;
        laserRidge = 3_um;
        nanogap = 0;
    ///////////////////////////device intinalzition///////////////////////////
    
        for(int i = 0;i<everyrow1;i++){

            if ( i % 2 == 0 )
            {
                contrrolangle = 1;
            }

            org(DeviceXorg, -DieW / 2 + 3*shifty+YdeviceGap*i+YdeviceGap2*everyrow2, 0, FLIP);
            NEW(SAG_FP,deviceL,deviceW,nanogap,laserRidge,contrrolangle).place().O_PORTS["out0"]
                    >>NEW(SAG_FP,deviceL,deviceW,nanogap,laserRidge,contrrolangle)
                    >>NEW(SAG_FP,deviceL,deviceW,nanogap,laserRidge,contrrolangle)
                    >>NEW(SAG_FP,deviceL,deviceW,nanogap,laserRidge,contrrolangle)
                    >>NEW(SAG_FP,deviceL,deviceW,nanogap,laserRidge,contrrolangle)
                    >>NEW(SAG_FP,deviceL,deviceW,nanogap,laserRidge,contrrolangle)
                    >>NEW(SAG_FP,deviceL,deviceW,nanogap,laserRidge,contrrolangle)
                    >>NEW(SAG_FP,deviceL,deviceW,nanogap,laserRidge,contrrolangle)
                    >>NEW(SAG_FP,deviceL,deviceW,nanogap,laserRidge,contrrolangle)
                    >>NEW(SAG_FP,deviceL,deviceW,nanogap,laserRidge,contrrolangle)
                    >>NEW(SAG_FP,deviceL,deviceW,nanogap,laserRidge,contrrolangle)
                    >>NEW(SAG_FP,deviceL,deviceW,3_um,laserRidge,contrrolangle);
        }



    ////////////////////////////////////////////////////////
    DeviceXorg = DeviceXorg+2000_um;
    ////////////////////////////////////////////////////////

///////////////////////////device intinalzition///////////////////////////
        deviceL = 125_um;
        deviceW = 15_um;
        laserRidge = 3_um;
        nanogap = 0;
///////////////////////////device intinalzition///////////////////////////

    for(int i = 0;i<everyrow2;i++){


        if ( i % 2 == 1 )
        {
            contrrolangle = 1;
        }


        org(DeviceXorg, -DieW / 2 + 3*shifty+YdeviceGap2*i, 0, FLIP);
        NEW(SAG_FP,deviceL,deviceW,nanogap,laserRidge,contrrolangle).place().O_PORTS["out0"]
                >>NEW(SAG_FP,deviceL,deviceW,nanogap,laserRidge,contrrolangle)
                >>NEW(SAG_FP,deviceL,deviceW,nanogap,laserRidge,contrrolangle)
                >>NEW(SAG_FP,deviceL,deviceW,3_um,laserRidge,contrrolangle);

       contrrolangle = 0;

    }


///////////////////////////device intinalzition///////////////////////////
        deviceL = 125_um;
        deviceW = 25_um;
        laserRidge = 3_um;
        nanogap = 0;
///////////////////////////device intinalzition///////////////////////////

    for(int i = 0;i<everyrow1;i++){

        if ( i % 2 == 1 )
        {
            contrrolangle = 1;
        }

        org(DeviceXorg, -DieW / 2 + 3*shifty+YdeviceGap*i+YdeviceGap2*everyrow2, 0, FLIP);
        NEW(SAG_FP,deviceL,deviceW,nanogap,laserRidge,contrrolangle).place().O_PORTS["out0"]
                >>NEW(SAG_FP,deviceL,deviceW,nanogap,laserRidge,contrrolangle)
                >>NEW(SAG_FP,deviceL,deviceW,nanogap,laserRidge,contrrolangle)
                >>NEW(SAG_FP,deviceL,deviceW,3_um,laserRidge,contrrolangle);
        contrrolangle = 0;

    }


    ////////////////////////////////////////////////////////
    DeviceXorg = DeviceXorg+700_um;
    ////////////////////////////////////////////////////////

///////////////////////////device intinalzition///////////////////////////
        deviceL = 125_um;
        deviceW = 15_um;
        laserRidge = 3_um;
        nanogap = 0;
///////////////////////////device intinalzition///////////////////////////

    for(int i = 0;i<everyrow2;i++){

        if ( i % 2 == 1 )
        {
            contrrolangle = 1;
        }

        org(DeviceXorg, -DieW / 2 + 3*shifty+YdeviceGap2*i, 0, FLIP);
        NEW(SAG_FP,deviceL,deviceW,nanogap,laserRidge,contrrolangle).place().O_PORTS["out0"]
                >>NEW(SAG_FP,deviceL,deviceW,nanogap,laserRidge,contrrolangle)
                >>NEW(SAG_FP,deviceL,deviceW,nanogap,laserRidge,contrrolangle)
                >>NEW(SAG_FP,deviceL,deviceW,3_um,laserRidge,contrrolangle);
        contrrolangle = 0;


    }


///////////////////////////device intinalzition///////////////////////////
        deviceL = 125_um;
        deviceW = 25_um;
        laserRidge = 3_um;
        nanogap = 0;
///////////////////////////device intinalzition///////////////////////////

    for(int i = 0;i<everyrow1;i++){

        if ( i % 2 == 1 )
        {
            contrrolangle = 1;
        }

        org(DeviceXorg, -DieW / 2 + 3*shifty+YdeviceGap*i+YdeviceGap2*everyrow2, 0, FLIP);
        NEW(SAG_FP,deviceL,deviceW,nanogap,laserRidge,contrrolangle).place().O_PORTS["out0"]
                >>NEW(SAG_FP,deviceL,deviceW,nanogap,laserRidge,contrrolangle)
                >>NEW(SAG_FP,deviceL,deviceW,nanogap,laserRidge,contrrolangle)
                >>NEW(SAG_FP,deviceL,deviceW,3_um,laserRidge,contrrolangle);
        contrrolangle = 0;

    }


    ////////////////////////////////////////////////////////
    DeviceXorg = DeviceXorg+700_um;
    ////////////////////////////////////////////////////////

///////////////////////////device intinalzition///////////////////////////
         deviceL = 125_um;
        deviceW = 15_um;
        laserRidge = 3_um;
        nanogap = 0;
///////////////////////////device intinalzition///////////////////////////

    for(int i = 0;i<everyrow2;i++){

        if ( i % 2 == 1 )
        {
            contrrolangle = 1;
        }

        org(DeviceXorg, -DieW / 2 + 3*shifty+YdeviceGap2*i, 0, FLIP);
        NEW(SAG_FP,deviceL,deviceW,nanogap,laserRidge,contrrolangle).place().O_PORTS["out0"]
                >>NEW(SAG_FP,deviceL,deviceW,nanogap,laserRidge,contrrolangle)
                >>NEW(SAG_FP,deviceL,deviceW,nanogap,laserRidge,contrrolangle)
                >>NEW(SAG_FP,deviceL,deviceW,nanogap,laserRidge,contrrolangle)
                >>NEW(SAG_FP,deviceL,deviceW,nanogap,laserRidge,contrrolangle)
                >>NEW(SAG_FP,deviceL,deviceW,nanogap,laserRidge,contrrolangle)
                >>NEW(SAG_FP,deviceL,deviceW,nanogap,laserRidge,contrrolangle)
                >>NEW(SAG_FP,deviceL,deviceW,3_um,laserRidge,contrrolangle);
        contrrolangle = 0;

    }


///////////////////////////device intinalzition///////////////////////////
        deviceL = 125_um;
        deviceW = 25_um;
        laserRidge = 3_um;
        nanogap = 0;
///////////////////////////device intinalzition///////////////////////////

    for(int i = 0;i<everyrow1;i++){

        if ( i % 2 == 1 )
        {
            contrrolangle = 1;
        }

        org(DeviceXorg, -DieW / 2 + 3*shifty+YdeviceGap*i+YdeviceGap2*everyrow2, 0, FLIP);
        NEW(SAG_FP,deviceL,deviceW,nanogap,laserRidge,contrrolangle).place().O_PORTS["out0"]
                >>NEW(SAG_FP,deviceL,deviceW,nanogap,laserRidge,contrrolangle)
                >>NEW(SAG_FP,deviceL,deviceW,nanogap,laserRidge,contrrolangle)
                >>NEW(SAG_FP,deviceL,deviceW,nanogap,laserRidge,contrrolangle)
                >>NEW(SAG_FP,deviceL,deviceW,nanogap,laserRidge,contrrolangle)
                >>NEW(SAG_FP,deviceL,deviceW,nanogap,laserRidge,contrrolangle)
                >>NEW(SAG_FP,deviceL,deviceW,nanogap,laserRidge,contrrolangle)
                >>NEW(SAG_FP,deviceL,deviceW,3_um,laserRidge,contrrolangle);
        contrrolangle = 0;

    }


  
    ////////////////////////////////////////////////////////
    DeviceXorg = DeviceXorg+1100_um;
    ////////////////////////////////////////////////////////

///////////////////////////device intinalzition///////////////////////////
        deviceL = 125_um;
        deviceW = 15_um;
        laserRidge = 3_um;
        nanogap = 0;
///////////////////////////device intinalzition///////////////////////////

    for(int i = 0;i<everyrow2;i++){

        if ( i % 2 == 1 )
        {
            contrrolangle = 1;
        }


        org(DeviceXorg, -DieW / 2 + 3*shifty+YdeviceGap2*i, 0, FLIP);
        NEW(SAG_FP,deviceL,deviceW,nanogap,laserRidge,contrrolangle).place().O_PORTS["out0"]
                >>NEW(SAG_FP,deviceL,deviceW,nanogap,laserRidge,contrrolangle)
                >>NEW(SAG_FP,deviceL,deviceW,nanogap,laserRidge,contrrolangle)
                >>NEW(SAG_FP,deviceL,deviceW,nanogap,laserRidge,contrrolangle)
                >>NEW(SAG_FP,deviceL,deviceW,nanogap,laserRidge,contrrolangle)
                >>NEW(SAG_FP,deviceL,deviceW,nanogap,laserRidge,contrrolangle)
                >>NEW(SAG_FP,deviceL,deviceW,nanogap,laserRidge,contrrolangle)
                >>NEW(SAG_FP,deviceL,deviceW,3_um,laserRidge,contrrolangle);
        contrrolangle = 0;

    }


///////////////////////////device intinalzition///////////////////////////
        deviceL = 125_um;
        deviceW = 25_um;
        laserRidge = 3_um;
        nanogap = 0;
///////////////////////////device intinalzition///////////////////////////

    for(int i = 0;i<everyrow1;i++){

        if ( i % 2 == 1 )
        {
            contrrolangle = 1;
        }

        org(DeviceXorg, -DieW / 2 + 3*shifty+YdeviceGap*i+YdeviceGap2*everyrow2, 0, FLIP);
        NEW(SAG_FP,deviceL,deviceW,nanogap,laserRidge,contrrolangle).place().O_PORTS["out0"]
                >>NEW(SAG_FP,deviceL,deviceW,nanogap,laserRidge,contrrolangle)
                >>NEW(SAG_FP,deviceL,deviceW,nanogap,laserRidge,contrrolangle)
                >>NEW(SAG_FP,deviceL,deviceW,nanogap,laserRidge,contrrolangle)
                >>NEW(SAG_FP,deviceL,deviceW,nanogap,laserRidge,contrrolangle)
                >>NEW(SAG_FP,deviceL,deviceW,nanogap,laserRidge,contrrolangle)
                >>NEW(SAG_FP,deviceL,deviceW,nanogap,laserRidge,contrrolangle)
                >>NEW(SAG_FP,deviceL,deviceW,3_um,laserRidge,contrrolangle);
        contrrolangle = 0;

    }

    ////////////////////////////////////////////////////////
    DeviceXorg = DeviceXorg+1050_um;
    ////////////////////////////////////////////////////////

///////////////////////////device intinalzition///////////////////////////
        deviceL = 125_um;
        deviceW = 15_um;
        laserRidge = 3_um;
        nanogap = 0;
///////////////////////////device intinalzition///////////////////////////

    for(int i = 0;i<everyrow2;i++){
        if ( i % 2 == 1 )
        {
            contrrolangle = 1;
        }
        org(DeviceXorg, -DieW / 2 + 3*shifty+YdeviceGap2*i, 0, FLIP);
        NEW(SAG_FP,deviceL,deviceW,nanogap,laserRidge,contrrolangle).place().O_PORTS["out0"]
                >>NEW(SAG_FP,deviceL,deviceW,nanogap,laserRidge,contrrolangle)
                >>NEW(SAG_FP,deviceL,deviceW,nanogap,laserRidge,contrrolangle)
                >>NEW(SAG_FP,deviceL,deviceW,nanogap,laserRidge,contrrolangle)
                >>NEW(SAG_FP,deviceL,deviceW,nanogap,laserRidge,contrrolangle)
                >>NEW(SAG_FP,deviceL,deviceW,3_um,laserRidge,contrrolangle);
        contrrolangle = 0;

    }


///////////////////////////device intinalzition///////////////////////////
        deviceL = 125_um;
        deviceW = 25_um;
        laserRidge = 3_um;
        nanogap = 0;
///////////////////////////device intinalzition///////////////////////////

    for(int i = 0;i<everyrow1;i++){

        if ( i % 2 == 1 )
        {
            contrrolangle = 1;
        }

        org(DeviceXorg, -DieW / 2 + 3*shifty+YdeviceGap*i+YdeviceGap2*everyrow2, 0, FLIP);
        NEW(SAG_FP,deviceL,deviceW,nanogap,laserRidge,contrrolangle).place().O_PORTS["out0"]
                >>NEW(SAG_FP,deviceL,deviceW,nanogap,laserRidge,contrrolangle)
                >>NEW(SAG_FP,deviceL,deviceW,nanogap,laserRidge,contrrolangle)
                >>NEW(SAG_FP,deviceL,deviceW,nanogap,laserRidge,contrrolangle)
                >>NEW(SAG_FP,deviceL,deviceW,nanogap,laserRidge,contrrolangle)
                >>NEW(SAG_FP,deviceL,deviceW,3_um,laserRidge,contrrolangle);
        contrrolangle = 0;

    }




    ////////////////////////////////////////////////////////
    DeviceXorg = DeviceXorg+800_um;
    ////////////////////////////////////////////////////////

///////////////////////////device intinalzition///////////////////////////
        deviceL = 125_um;
        deviceW = 15_um;
        laserRidge = 3_um;
        nanogap = 0;
///////////////////////////device intinalzition///////////////////////////

    for(int i = 0;i<everyrow2;i++){

        if ( i % 2 == 1 )
        {
            contrrolangle = 1;
        }

        org(DeviceXorg, -DieW / 2 + 3*shifty+YdeviceGap2*i, 0, FLIP);
        NEW(SAG_FP,deviceL,deviceW,nanogap,laserRidge,contrrolangle).place().O_PORTS["out0"]
                >>NEW(SAG_FP,deviceL,deviceW,3_um,laserRidge,contrrolangle);
        contrrolangle = 0;


    }


///////////////////////////device intinalzition///////////////////////////
        deviceL = 125_um;
        deviceW = 25_um;
        laserRidge = 3_um;
        nanogap = 0;
///////////////////////////device intinalzition///////////////////////////

    for(int i = 0;i<everyrow1;i++){


        org(DeviceXorg, -DieW / 2 + 3*shifty+YdeviceGap*i+YdeviceGap2*everyrow2, 0, FLIP);
        NEW(SAG_FP,deviceL,deviceW,nanogap,laserRidge,contrrolangle).place().O_PORTS["out0"]
                >>NEW(SAG_FP,deviceL,deviceW,3_um,laserRidge,contrrolangle);
        contrrolangle = 0;


    }


    BLOCK{
        org(-DieL / 2, -2.75*shifty , 0, FLIP);
        deviceW = 100_um;
        contrrolangle = 0;
        NEW(SAG_FP,deviceL,deviceW,nanogap,laserRidge,contrrolangle).place().O_PORTS["out0"]
                >>NEW(SAG_FP,deviceL,deviceW,nanogap,laserRidge,contrrolangle)
                >>NEW(SAG_FP,deviceL,deviceW,nanogap,laserRidge,contrrolangle)
                >>NEW(SAG_FP,deviceL,deviceW,nanogap,laserRidge,contrrolangle)
                >>NEW(SAG_FP,deviceL,deviceW,nanogap,laserRidge,contrrolangle)
                >>NEW(SAG_FP,deviceL,deviceW,nanogap,laserRidge,contrrolangle)
                >>NEW(SAG_FP,deviceL,deviceW,nanogap,laserRidge,contrrolangle)
                >>NEW(SAG_FP,deviceL,deviceW,3_um,laserRidge,contrrolangle);
    }

        BLOCK{
        org(-DieL / 2, DieW -5.25*shifty , 0, FLIP);
        deviceW = 100_um;
        contrrolangle = 0;
        NEW(SAG_FP,deviceL,deviceW,nanogap,laserRidge,contrrolangle).place().O_PORTS["out0"]
                >>NEW(SAG_FP,deviceL,deviceW,nanogap,laserRidge,contrrolangle)
                >>NEW(SAG_FP,deviceL,deviceW,nanogap,laserRidge,contrrolangle)
                >>NEW(SAG_FP,deviceL,deviceW,nanogap,laserRidge,contrrolangle)
                >>NEW(SAG_FP,deviceL,deviceW,nanogap,laserRidge,contrrolangle)
                >>NEW(SAG_FP,deviceL,deviceW,nanogap,laserRidge,contrrolangle)
                >>NEW(SAG_FP,deviceL,deviceW,nanogap,laserRidge,contrrolangle)
                >>NEW(SAG_FP,deviceL,deviceW,3_um,laserRidge,contrrolangle);
    }

}