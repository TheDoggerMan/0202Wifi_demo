
#include "app_controller.h"

using namespace mono::geo;

// Contructor
// Initializes the label object with position and text content
// You should init only data here, since I/O is not setup yet.
AppController::AppController() :

    // Call the TextLabel's constructor, with a Rect and a static text
    helloLabel(Rect(0,100,176,20), "Hi, I'm Mono!"),
    spi(RP_SPI_MOSI, RP_SPI_MISO, RP_SPI_CLK),
    spiComm(spi, NC, RP_nRESET, RP_INTERRUPT)
{

    // the label is the full width of screen, set it to be center aligned
    helloLabel.setAlignment(TextLabelView::ALIGN_CENTER);

    // set another text color
    helloLabel.setTextColor(display::TurquoiseColor);
}

void AppController::monoWakeFromReset()
{
  redpine::Module::initialize(&spiComm);
  redpine::Module::setupWifiOnly("Thomson3968F1", "CBEF40E02F");
  redpine::Module::setNetworkReadyCallback<AppController>(this, &AppController::networkReadyHandler);

    // At this point after reset we can safely expect all peripherals and
    // I/O to be setup & ready.

    // tell the label to show itself on the screen
    helloLabel.show();
}

void AppController::monoWillGotoSleep()
{
    // Do any clean up here, before system goes to sleep and power
    // off peripherals.

}

void AppController::monoWakeFromSleep()
{
    // After sleep, the screen memory has been cleared - tell the label to
    // draw itself again
    helloLabel.scheduleRepaint();
}

void AppController::networkReadyHandler()
{
    helloLabel.setText("Network Ready");
}
