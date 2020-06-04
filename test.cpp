//
// Created by Yuan on 2018/12/6.
//

#include "IPL_Extension.h"
#include <string>
#include <vector>
#include <utility>


//#define GDS_FILENAME "mask_example.gds"
//#define MASK_NAME "JK_Extension"

#include "pdk_demo.h"

LOAD_PDK(PDK_DEMO);


void mask(int);

/* DO NOT MODIFY */
int main(int argc, char **argv) {
    setfont((char *)"caps.plf");
    msk_init();
    msk_add_sublayout(MASK_NAME, mask);

    msk_export(GDS_FILENAME);
    update_KLayout((char *)"KLayout 0.24.4");
}

//int w = 0;
//void c_mmi(PortBase &portBase, int n, int m){
//    if(!m){
//        return;
//    }
//    var t= portBase;
//    for (int i = 0; i < n; i++) {
//        var k = NEW(MMI);
//        w ++;
//        t = t
//                >> NEW(EULER_BEND, 360_deg /n)
//                >> k("in2", "out2");
//        c_mmi(k.O_PORTS["out1"].flip_x(), n, m - 1);
//    }
//    t >>NEW (EULER_BEND, 360_deg /n);
//}



/* The MMI design */
void mask(int i) {
    layer(L_waveguides);
    org(4950_um,5000_um,0,NOFLIP);
//    FLIPCP;
//    rotate(-50_deg);
//    show_cp(10_um);
//    pointer cp1 {4940_um, 4990_um, -30_deg, NOFLIP};
//    BLOCK {
//        cp = cp1;
//        show_cp(10_um);
//    }
//    move(diff(cp, cp1));
//    show_cp(10_um);
//    DEBUG_SHOW(cp.x);DEBUG_SHOW(cp.y);DEBUG_SHOW(cp.a);DEBUG_SHOW(cp.flip);
//    cp = {0, 0, 0, NOFLIP};
    BLOCK {
//        sw(100_um, 1_um);
//        SW ss(100_um);
//        ss.place();
//        FLIPCP
//        ss.Connect(MMI().O_PORTS["in2"]);
//BLOCK {
//    layer(3);
//    double Length_MMI = 100.175_um, Width_MMI = 9_um;
//    double Width_Taper_in = 0.55_um, Width_Taper_out = 2.2_um, Length_Taper = 24.75_um;
//    double Pitch_IO = 3_um;
//    cw(100_um, 45_deg, 0.55_um);
//    show_cp(10_um);
//    mmi_2x2taper(Length_MMI, Width_MMI, Width_Taper_in, Width_Taper_out, Length_Taper, Pitch_IO / 2.0,
//                 -Pitch_IO / 2.0, Pitch_IO / 2.0, -Pitch_IO / 2.0, 90_deg);
//    show_cp(10_um);
//    cw(100_um, 90_deg, 0.55_um);
//    show_cp(10_um);
//    mmi_2x2taper(Length_MMI, Width_MMI, Width_Taper_in, Width_Taper_out, Length_Taper, Pitch_IO / 2.0,
//                 -Pitch_IO / 2.0, Pitch_IO / 2.0, -Pitch_IO / 2.0, 90_deg);
//    show_cp(10_um);
//}
//        layer(L_waveguides);
//        for (int i = 0; i < 12; i++) {
//            BLOCK {
//                NEW(SW, 100_um).place();
//                NEW(SW, 100_um).place();
//                NEW(MMI).place();
//                show_cp(10_um);
//            }
//            rotate(360_deg / 12);
//
//        }

//        var CBT = NEW_DEVICE<MMI>();
        var CBT = *(new MMI());
////
//        var CBT2 = NEW(MMI);
////
//        var ss = NEW(SW, 10_um);
//
//        var eb = NEW(CW, 120_deg);

//        eb.place();

//        var ss2 = NEW(SW, 10_um);


//          DEBUG_SHOW(NEW_DEVICE("MMI","1"));
//        MMI dn = MMI();
//        dn.place();
//        var CBT = NEW(MMI(dn));
//        cw(100_um, 45_deg, 0.55_um);
//        show_cp(10_um);
//        BLOCK {
//            DEBUG_SHOW(cp.x);
//            DEBUG_SHOW(cp.y);
//            DEBUG_SHOW(cp.a);
////        euler_curve(100_um, 90_deg, 0.55_um);
//            NEW(EULER_BEND, 90_deg).place();
////        show_cp(10_um);
//            DEBUG_SHOW(cp.x);
//            DEBUG_SHOW(cp.y);
//            DEBUG_SHOW(cp.a);
//            NEW(MMI).place();
//        }
//        BLOCK {
//            DEBUG_SHOW(cp.x);
//            DEBUG_SHOW(cp.y);
//            DEBUG_SHOW(cp.a);
//        euler_curve(100_um, 90_deg, 0.55_um);
////            NEW(EULER_BEND, 90_deg).place();
////        show_cp(10_um);
//            DEBUG_SHOW(cp.x);
//            DEBUG_SHOW(cp.y);
//            DEBUG_SHOW(cp.a);
//            NEW(MMI).place();
//        }
//        move(1_nm, 1_nm, 0, NOFLIP);

//        rotate(30_deg);
        CBT.place();
        var CBT2 = NEW(MMI);
        move(800_um, 250_um, 0, NOFLIP);
        CBT2.place();

//        auto t = decltype(CBT)(CBT);
//        show_cp(10_um);

//        hash(std::to_string(CBT.O_PORTS["in1"]));
//        CBT.O_PORTS["out2"].SetCurrentPosition();
//        CBT.O_PORTS["out2"] >> NEW(MMI) >> NEW(SINE_BEND, CBT2.O_PORTS["in2"]);

//        var t = *(new TERMINATION_PORT<O_PORT>("in", "TERMINATION_O_PORT", cp, nullptr, nullptr, nullptr));

        var s = NEW(SW, 100_um);

        s >> FLIP_X >>NEW(CW, 100_um, 90_deg) >> NEW(SW, 100_um) >> PUSH;

//        t.SetCurrentPosition();

//        t >> CBT.O_PORTS["in1"] >> "out2" >> NEW(MMI).O_PORTS["in2"] >> PUSH >> "out2" >> NEW(CONNECTOR_SINE_BEND) >> CBT2.O_PORTS["in2"] >> POP >> "out1" >> FLIP_X >> NEW(SINE_BEND, 100_um, 100_um) >> NEW(CONNECTOR_SINE_BEND) >> CBT2.O_PORTS["in1"] >> "out1" >>NEW(SW, 10_um) >> NEW(MZI).O_PORTS["in1"] >> "out1" >> NEW(EULER_BEND, 50_um, 180_deg) >> s >> POP >> NEW(SINE_BEND, 100_um, 100_um);



    CBT.O_PORTS["out2"]
        >> NEW(MMI).O_PORTS["in2"] >> PUSH >> "out2"
        >> NEW(CONNECTOR_SINE_BEND)
        >> CBT2.O_PORTS["in2"] >> POP >> "out1" >> FLIP_X
        >> NEW(SINE_BEND, 100_um, 100_um);
        // >> NEW(CONNECTOR_SINE_BEND) >> CBT2.O_PORTS["in1"] >> "out1" >>NEW(SW, 10_um) >> NEW(MZI).O_PORTS["in1"] >> "out1" >> NEW(EULER_BEND, 50_um, 180_deg) >> s >> POP >> NEW(SINE_BEND, 100_um, 100_um);





//        CBT.O_PORTS["out1"].SetCurrentPosition();
//        CBT.O_PORTS["out2"] >> NEW(MMI) >> NEW(SINE_BEND, CBT2.O_PORTS["in2"]);
//        CBT.O_PORTS["out1"] >> NEW(CONNECTOR_SINE_BEND) >> CBT2.O_PORTS["in1"];
//        DEBUG_SHOW(hash(CBT.O_PORTS["out2"]));
//        show_cp(10_um);
//        offset(3_um);
//        DEBUG_SHOW(cp.x);
//        DEBUG_SHOW(cp.y);
//        DEBUG_SHOW(cp.a);
//        cw(100_um, 45_deg, 0.55_um);

//        double Length_MMI = 100.175_um, Width_MMI = 9_um;
//        double Width_Taper_in = 0.55_um, Width_Taper_out = 2.2_um, Length_Taper = 24.75_um;
//        double Pitch_IO = 3_um;
//        mmi_2x2taper(Length_MMI, Width_MMI, Width_Taper_in, Width_Taper_out, Length_Taper, Pitch_IO / 2.0,
//                     -Pitch_IO / 2.0, Pitch_IO / 2.0, -Pitch_IO / 2.0, 90_deg);
//        cw(100_um, 45_deg, 0.55_um);


//        CBT.O_PORTS["out1"].SetCurrentPosition();
//        show_cp(10_um);
//        cw(100_um, 90_deg, 0.55_um);
//        show_cp(10_um);
//        CBT2.place();
//        show_cp(10_um);
//        CBT.O_PORTS["out1"] >> ss;
//        show_cp(10_um);
//        taper(20_um, 0.55_um, 2_um);
//        ss >> CBT2("in1", "out1");

//          c_mmi(CBT.O_PORTS["out2"], 6,3);
//          DEBUG_SHOW(w);
//        CBT.O_PORTS["out2"]
//            >> NEW(EULER_BEND, 60_deg)("out", "in", NOFLIP, FLIP)
//            >> NEW(MMI)("in2", "out2", NOFLIP, FLIP)
//            >> NEW(EULER_BEND, 60_deg)("out", "in", NOFLIP, FLIP)
//            >> NEW(MMI)("in2", "out2", NOFLIP, FLIP)
//            >> NEW(EULER_BEND, 60_deg)("out", "in", NOFLIP, FLIP)
//            >> NEW(MMI)("in2", "out2", NOFLIP, FLIP)
//            >> NEW(EULER_BEND, 60_deg)("out", "in", NOFLIP, FLIP)
//            >> NEW(MMI)("in2", "out2", NOFLIP, FLIP)
//            >> NEW(EULER_BEND, 60_deg)("out", "in", NOFLIP, FLIP)
//            >> NEW(MMI)("in2", "out2", NOFLIP, FLIP)
//            >> NEW(EULER_BEND, 60_deg)("out", "in", NOFLIP, FLIP);
//
//
//        CBT.O_PORTS["out1"].flip_x()
//                >> NEW(EULER_BEND, 60_deg)("out", "in", NOFLIP, FLIP)
//                >> NEW(MMI)("in2", "out2", NOFLIP, FLIP)
//                >> NEW(EULER_BEND, 60_deg)("out", "in", NOFLIP, FLIP)
//                >> NEW(MMI)("in2", "out2", NOFLIP, FLIP)
//                >> NEW(EULER_BEND, 60_deg)("out", "in", NOFLIP, FLIP)
//                >> NEW(MMI)("in2", "out2", NOFLIP, FLIP)
//                >> NEW(EULER_BEND, 60_deg)("out", "in", NOFLIP, FLIP)
//                >> NEW(MMI)("in2", "out2", NOFLIP, FLIP)
//                >> NEW(EULER_BEND, 60_deg)("out", "in", NOFLIP, FLIP)
//                >> NEW(MMI)("in2", "out2", NOFLIP, FLIP)
//                >> NEW(EULER_BEND, 60_deg)("out", "in", NOFLIP, FLIP);

//        CBT.O_PORTS["out1"] >>CBT2("in1", "out1");
//        show_cp(10_um);
//        MMI CBT2 = NEW(MMI(CBT));
//        auto test = NEW(MMI(CBT));
//        show_cp(10_um);
//        CBT.place();
//        CBT.O_PORTS["out1"].flip_x();
//        CBT.O_PORTS["out1"] >> CBT2("in1", "out1") >> test();
//        CBT.O_PORTS["out1"] >> NEW(MMI())() >> NEW(SW(100_um)) >> NEW(SW(100_um)) >> NEW(MMI())()>> NEW(SW(100_um));
//        show_cp(10_um);



//        CBT.O_PORTS["out1"].flip_x()
//        .Connect(NEW(SW,100_um))
//        .Connect(NEW(MMI).O_PORTS["in2"]);
//
//        CBT.O_PORTS["out1"] >> FLIP_X
//        >> NEW(SW, 100_um)
//        >> NEW(MMI).O_PORTS["in2"];

//
// cw(100_um, 45_deg, 1_um);
//        MMI CBT2 = MMI();
//        CBT2.place();
//        SW ss(100_um);

//        CBT.O_PORTS["out1"].Connect(CBT2.O_PORTS["in1"]);

//        CBT.push().O_PORTS["out1"].Connect(CBT2.push().O_PORTS["in1"]).O_PORTS["out2"].Connect(
//                MMI().O_PORTS["in2"].flip_x()).pop().O_PORTS["out1"].Connect(
//                MMI().O_PORTS["in2"]).pop().O_PORTS["out2"].Connect(MMI().O_PORTS["in1"]);

//        CBT.O_PORTS[3].Connect(MMI().O_PORTS[0]);
//          CBT.O_PORTS[2].SetCurrentPosition();
//          show_cp(10_um);
//          cw(100_um, 45_deg, 1_um);
//          CBT.place();
//        cp = CBT.PORTS_IN[0];
//        sw(10_um, 1_um);
//        cp = CBT.PORTS_OUT[0];
//        sw(10_um, 1_um);
    }

//    offset(500_um);
//    HOLD
//        DEBUG_SHOW(euler_curve(100_um, -0_deg, 1_um));
//        DEBUG_SHOW(sw(100_um, 1_um));
//    ENDHOLD

//    offset(500_um);
//    HOLD
//        sine_bend(100_um, 100_um, 1_um);
//        DEBUG_SHOW(sine_bend(0.0008602450078, -0.0009580316277, 1_um));
//        sine_bend(100_um, -100_um, 1_um);
//        DEBUG_SHOW(sw(100_um, 1_um));
//    ENDHOLD


}