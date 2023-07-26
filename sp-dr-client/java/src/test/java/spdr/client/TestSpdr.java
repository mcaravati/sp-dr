package spdr.client;

import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.assertEquals;

public class TestSpdr {

    @Test
    public void testSample() {
        Spdr.Client instance = new Spdr.Client("localhost", 8080);
        
        assertEquals(0, instance.connect());
        assertEquals(0, instance.disconnect());
    }
}