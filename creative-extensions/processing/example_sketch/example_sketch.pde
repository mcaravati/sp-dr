import ergo_junior.*;
import oscP5.OscPacket;

// Example address and port
String oscServerAddress = "127.0.0.1";
int oscServerPort = 9000;

ErgoJuniorController ergoJunior = new ErgoJuniorController(this, oscServerAddress, oscServerPort);
ergoJunior.setLedOn(1);
