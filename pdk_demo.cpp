//
// Created by Yuan on 2018/11/8.
//

#include "IPL_Extension.h"
#include "pdk_demo.h"

#include "type_traits"




IMPLEMENT_NEW_PDK(PDK_DEMO)


    DEFINE_WG_STRUCTURES
            {"waveguide1", {100_um, TYPE_O_PORT, {
                        {layernr(L_waveguides), 0.55_um},
                        {layernr(L_Waveguides), 10.55_um}
                }
                }
            }
    END_DEFINE_WG_STRUCTURES


    IMPLEMENT_WAVEGUIDES(, waveguide1);


    CONNECTOR_SINE_BEND_EBEAM::CONNECTOR_SINE_BEND_EBEAM() {
        SimpleComponent = true;
        COMPONENT_INIT();
    }


    ComponentBase & CONNECTOR_SINE_BEND_EBEAM::Connector_Component(PortBase &portBase1, PortBase &portBase2) {

        auto dp = portBase2 - portBase1;
        BLOCK{
            layout(2);
            rect(dp.x, dp.y, 1, 1);
        };

        return CONNECTOR_SINE_BEND::Connector_Component(portBase1, portBase2);
    }



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

END_IMPLEMENT_NEW_PDK(PDK_DEMO)