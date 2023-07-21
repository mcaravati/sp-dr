import org.bytedeco.javacpp.*;
import org.bytedeco.javacpp.annotation.*;

@Platform(include="spdr_client.h", link="spdr")
@Namespace("spdr")
public class Spdr {
    public static class Client extends Pointer {
        static { Loader.load(); }
        public Client(String host, int port) { allocate(); }
        private native void allocate();

        public native void connect();
        public native void disconnect();
    }

    public static void main(String[] args) {
        Client client = new Client("localhost", 8080);
        client.connect();
        client.disconnect();
    }    
}
