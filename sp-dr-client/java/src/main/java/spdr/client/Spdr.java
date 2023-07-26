package spdr.client;

import org.bytedeco.javacpp.*;
import org.bytedeco.javacpp.annotation.*;

@Platform(include="spdr_client.h", link="spdr")
@Namespace("spdr")
public class Spdr {
    public static class Client extends Pointer {
        static { Loader.load(); }
        public Client(String host, int port) { allocate(host, port); }
        private native void allocate(String host, int port);

        public native int connect();
        public native int disconnect();
    }

    public static void main(String[] args) {}    
}
