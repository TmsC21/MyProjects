import javax.swing.*;
import java.awt.*;

public class CalculatorFrame extends JFrame {
    CalculatorButtonsPanel buttonsPanel = new CalculatorButtonsPanel();
    CalculatorDisplay calculatorDisplay = new CalculatorDisplay();
    public CalculatorFrame(){
        this.setSize(300,300);
        this.setVisible(true);
        this.calculatorDisplay.getDisplay().setFont(new Font("Arial", Font.PLAIN, 30));
        this.add(calculatorDisplay,BorderLayout.PAGE_START);
        this.add(buttonsPanel);
        repaint();
    }

    public CalculatorButtonsPanel getButtonsPanel() {
        return buttonsPanel;
    }

    public CalculatorDisplay getCalculatorDisplay() {
        return calculatorDisplay;
    }
}
