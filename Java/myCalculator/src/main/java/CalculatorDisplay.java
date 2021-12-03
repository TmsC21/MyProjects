import javax.swing.*;
import java.awt.*;

public class CalculatorDisplay extends JPanel {
    private JLabel display;
    CalculatorDisplay(){
        this.display = new JLabel("0",SwingConstants.RIGHT);
        this.add(this.display);
    }

    public JLabel getDisplay() {
        return display;
    }
    public void setDisplay(JLabel display) {
        this.display = display;
    }
}
