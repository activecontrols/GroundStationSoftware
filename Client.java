import com.fazecast.jSerialComm.SerialPort;
import com.MAVLink.Parser;

import java.nio.charset.StandardCharsets;

import com.MAVLink.MAVLinkPacket;
import com.MAVLink.minimal.*;
import com.MAVLink.pscom.*;

public class Client {
    public static void main(String[] args) {
        SerialPort[] ports = SerialPort.getCommPorts();
        if (ports.length == 0) {
            System.out.println("No ports found, exiting!");
            return;
        }
        int i = 0;
        int p = 0;
        for (SerialPort port : ports) {
            System.out.println(port.getSystemPortName());
            if ((port.getSystemPortName().contains("usbmodem")
                    || port.getSystemPortName().contains("usbserial"))
                    && port.getSystemPortName().contains("tty")) {
                p = i;
                break;
            }
            i += 1;
        }
		System.out.println("Using port: " + ports[p].getSystemPortName());
        ports[p].setBaudRate(57600);
        Client client = new Client(ports[p]);

        while (true) {
            client.spin();
        }
    }

    private SerialPort port;
    private Parser parser;
    private String[] statusString = new String[8];
    long last_heartbeat = 0;

    public Client(SerialPort port) {
        this.port = port;
        this.port.openPort();
        this.parser = new Parser(false);
        for (int i = 0; i < 8; i++) {
            this.statusString[i] = "";
        }
    }

    public void spin() {
        // Write heartbeat every second
        long now = System.currentTimeMillis();
        if (now - this.last_heartbeat > 1000) {
            msg_heartbeat heartbeat = new msg_heartbeat(0L, (short)6, (short)8, (short)0, (short)4, (short)0);
            MAVLinkPacket hb_packed = heartbeat.pack();
            byte[] data = hb_packed.encodePacket();
            this.port.writeBytes(data, data.length);
            this.last_heartbeat = now;
            System.out.println("Sent heartbeat");
            this.sendSimpleCommand("GO");
            // this.sendMissionLoadSD(14);
        }
        // Read
        if (this.port.bytesAvailable() <= 0) return;
        byte[] readBuffer = new byte[this.port.bytesAvailable()];
        int numRead = this.port.readBytes(readBuffer, readBuffer.length);
        for (byte c : readBuffer) {
            MAVLinkPacket packet = this.parser.mavlink_parse_char(c);
            if (packet != null) {
                // System.out.printf("Got packet id: %d\n", packet.msgid);
                switch (packet.msgid) {
                    case 0:
                        msg_heartbeat hb = new msg_heartbeat(packet);
                        this.handleHB(hb);
                    case 1:
                        msg_sys_status status = new msg_sys_status(packet);
                        this.handleSysStatus(status);
                    case 253:
                        msg_statustext text = new msg_statustext(packet);
                        this.handleStatusText(text);
                        break;
                    default:
                        // System.out.println("Unhandled message: msgid=" + packet.msgid);
                        break;
                }
            }
        }
    }

    public void handleHB(msg_heartbeat hb) {
        System.out.println("Received heartbeat, sysid=" + hb.sysid);
    }

    public void handleSysStatus(msg_sys_status status) {
        System.out.println("Received system status, voltage=" + status.voltage_battery);
    }

    public void handleStatusText(msg_statustext text) {
        if (text.id == 0) return;
        for (byte b : text.text) {
            if (b == 0) {
                System.out.println(text.id % 8 + ":Status message: " + this.statusString[text.id % 8]);
                this.statusString[text.id % 8] = "";
                break;
            }
            this.statusString[text.id % 8] += new String(new char[]{(char) b});
        }
    }

    public void sendCommand(msg_command_long command) {
        MAVLinkPacket cmd_packed = command.pack();
        byte[] data = cmd_packed.encodePacket();
        this.port.writeBytes(data, data.length);
    }

    public void sendSimpleCommand(String cmdString) {
        msg_command_simple command = new msg_command_simple();
        int i = 0;
        for (byte b : cmdString.getBytes()) {
            command.command[i] = b;
            i += 1;
        }
        System.out.printf("Sending command: %s\r\n", cmdString);
        MAVLinkPacket cmd_packed = command.pack();
        byte[] data = cmd_packed.encodePacket();
        this.port.writeBytes(data, data.length);
    }

    public void sendMissionStart() {
        msg_command_long command = new msg_command_long();
        command.command = 300;// MAV_CMD_MISSION_START;
        this.sendCommand(command);
    }

    public void sendMissionLand() {
        msg_command_long command = new msg_command_long();
        command.command = 21;// MAV_CMD_NAV_LAND;
        this.sendCommand(command);
    }

    public void sendPause(int cont) {
        msg_command_long command = new msg_command_long();
        command.command = 193; //MAV_CMD_DO_PAUSE_CONTINUE;
        command.param1 = (float)cont;
        this.sendCommand(command);
    }

    public void sendMissionLoadSD(int number) {
        msg_command_long command = new msg_command_long();
        command.command = 51801;//MAV_CMD_MISSION_LOAD_SD;
        command.param1 = (float)number;
        this.sendCommand(command);
    }
}
