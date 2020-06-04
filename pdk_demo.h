//
// Created by Yuan on 2018/11/8.
//

#ifndef JK_EXTENSION_PDK_DEMO_H
#define JK_EXTENSION_PDK_DEMO_H

#include "IPL_Extension.h"
#include "pdk.h"
#include "technology.h"




DECLARE_NEW_PDK(PDK_DEMO)


    DECLARE_WAVEGUIDES(
            , waveguide1)

    //Declare new component
    DECLARE_NEW_COMPONENT(MMI)

        //Declare component parameters

        //Declare component function
        MMI();
        void layout(int) override;

    END_DECLARE_NEW_COMPONENT(MMI)

    //Declare new component
    DECLARE_NEW_COMPONENT(MZI)

        //Declare component parameters

        //Declare component function
        MZI();
        void layout(int) override;

    END_DECLARE_NEW_COMPONENT(MMI)


    DECLARE_NEW_COMPONENT(CONNECTOR_SINE_BEND_EBEAM, CONNECTOR_SINE_BEND)
        explicit CONNECTOR_SINE_BEND_EBEAM();
        ComponentBase & Connector_Component(PortBase &, PortBase &) override;
    END_DECLARE_NEW_COMPONENT(CONNECTOR_SINE_BEND_EBEAM)


END_DECLARE_NEW_PDK(PDK_DEMO)

#endif //JK_EXTENSION_PDK_DEMO_H
